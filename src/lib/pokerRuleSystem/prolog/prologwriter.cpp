/*******************************************************************
* Copyright (c) 2010 Thomas Fannes (thomasfannes@gmail.com)
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following
* conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************/

#include "prologwriter.hpp"
#include <ruleSystem/prolog/elementwriter.hpp>
#include <ruleSystem/prolog/prologwriter.hpp>
#include "../pokerrulesystem.hpp"
#include "../raiseaction.hpp"
#include <ruleSystem/constant.hpp>
#include <ruleSystem/exception.hpp>
#include <ruleSystem/function.hpp>
#include "../card/rankparser.hpp"
#include "../card/suitparser.hpp"

using namespace poker::card;

namespace poker {
namespace prolog {

namespace
{
void removeEmptyItems(QStringList & lst)
{
    lst.removeAll(QString());
    lst.removeAll(QString(""));
}
}

PokerCodeInformation::PokerCodeInformation(int ruleNumber)
    : ruleSystem::PrologWriter::CodeInformation(ruleNumber),
      _suitValidator(card::CardExpressionValidator::createSuitParser()),
      _rankValidator(card::CardExpressionValidator::createRankParser())
{
}

PokerCodeInformation::~PokerCodeInformation()
{
    delete _suitValidator;
    delete _rankValidator;
}

using namespace ruleSystem;
using namespace ruleSystem::prolog;

struct NumericalConstantWriter : public ElementWriter
{
    virtual float scoreElement(Element * element) const
    {
        Constant * c = element_cast<Constant>(element);
        if(!c)
            return 0;

        if(c->type() == type::numericalType())
            return 1.0f;
        else
            return 0;
    }

    virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const
	{
        Constant * c = element_cast<Constant>(element);
        if(!c || c->type() != type::numericalType())
            throw Exception("The supplied element is not an numerical constant", "NumericalConstantWriter::writeCode");

        QString var = info.getUniqueVariable();
        info.addPreDefinition(QString("%1 is %2").arg(var).arg(c->value().toString()));

        return var;
    }
};
struct CardEquationConstantWriter : public ElementWriter
{
    virtual float scoreElement(Element * element) const
    {
        Constant * c = element_cast<Constant>(element);
        if(!c)
            return 0;

        if(c->type() == type::cardEquationType())
            return 1.0f;
        else
            return 0;
    }

    QString translateVariables(const QString & expression, const QString & prefix, const QString & varDef, PrologWriter::CodeInformation & info) const
    {
        QRegExp regex = poker::card::CardExpressionValidator::varRegex();
        QString output = expression;

        int pos = 0;

        while((pos = regex.indexIn(output, pos)) != -1)
        {
            QString newVar = prefix + output.mid(pos, regex.matchedLength());
            info.addPreDefinition(varDef.arg(newVar));

            output.insert(pos, prefix);
            pos += regex.matchedLength()+prefix.length();
        }

        return output;
    }

    QString translateSuitExpression(const Card & card, PrologWriter::CodeInformation & info) const
    {
        SuitParser p;
        SuitObject o;

        if(card.suitExpression() == Card::Unknown())
            return "_";

        if(p.parse(card.suitExpression(), o) != -1)
            throw Exception("The suit expression in card is not valid", "CardEquationConstantWriter::translateSuitExpression");


        if(o.constant == Card::Clubs())					return "c";
        else if(o.constant == Card::Diamonds())	return "d";
        else if(o.constant == Card::Hearts())		return "h";
        else if(o.constant == Card::Spades())		return "s";
        else
        {
            QString varName = info.getUniqueVariable();
            QString expr = translateVariables(o.variableName, PokerCodeInformation::suitVarPrefix(), QString("suit(%1)"), info);
            //expr.replace("==", "=:=");
            info.addPreDefinition(QString("%1 = %2").arg(varName).arg(expr));

            return varName;
        }
    }

    void translateSpecialRankSymbolsForProlog(QString & expression) const
    {
        expression.replace("<=", "=< ");
        expression.replace("J", "11");
        expression.replace("Q", "12");
        expression.replace("K", "13");
        expression.replace("A", "14");
    }

    QString translateRankExpression(const Card & card, PrologWriter::CodeInformation & info) const
    {
        if(card.rankExpressions().isEmpty())
            return "_";

        RankParser p;
        QString varName = info.getUniqueVariable();

        foreach(QString expr, card.rankExpressions())
        {
            RankObject o;
            if(p.parse(expr, o) != -1)
                throw Exception("The rank expression in card is not valid", "CardEquationConstantWriter::translateRankExpression");

            expr = translateVariables(expr, PokerCodeInformation::rankVarPrefix(), QString("rank(%1)"), info);

            translateSpecialRankSymbolsForProlog(expr);
            if(!o.hasNumericalOperation && o.comparator == "=")
                info.addPreDefinition(QString("%1 %2").arg(varName).arg(expr));
            else
            {
                if(o.comparator == "=") expr.replace("=", "=:=");
                info.addPostDefinition(QString("%1 %2").arg(varName).arg(expr));
            }
        }

        return varName;
    }


    QString writeCardCode(const Card & card, PrologWriter::CodeInformation & info) const
    {
        return QString("card(%1, %2)").arg(translateRankExpression(card, info)).arg(translateSuitExpression(card, info));
    }

    virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const
	{
        Constant * c = element_cast<Constant>(element);
        if(!c || c->type() != type::cardEquationType())
            throw Exception("The supplied element is not an card equation constant", "CardEquationConstantWriter::writeCode");

        QStringList lst;
        QList<Card> cards = c->value().value<QList<Card> >();
        for(int i = 0; i < cards.size(); i++)
            lst << writeCardCode(cards.at(i), info);

        removeEmptyItems(lst);

        return lst.join(", ");
    }
};
struct BoolEqualFunctionWriter : public ElementWriter
{
    virtual float scoreElement(Element * element) const
    {
        Function * f = element_cast<Function>(element);
        if(!f)
            return 0;

        if(f->calculator()->uniqueName() != function::BoolEqualFunctor::UniqueName())
            return 0;
        else
            return 2.0f;
    }

    virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const
	{
        Function * f = element_cast<Function>(element);
        if(!f || f->calculator()->uniqueName() != function::BoolEqualFunctor::UniqueName())
            throw Exception(QString("The supplied calculator is not named %1").arg(function::BoolEqualFunctor::UniqueName()), "BoolEqualFunctionWriter::writeCode");

        QList<Evaluatable*> lst = f->functionInputs();
        return QString("%1 == %2").arg(PrologWriter::FindWriter(lst[0]).writeCode(lst[0], info)).arg(PrologWriter::FindWriter(lst[1]).writeCode(lst[1], info));
    }
};

template <class T> struct NAryFunctionWriter : public ElementWriter
{
public:
    NAryFunctionWriter(const QString & symbol)
        : _symbol(symbol) {}

    virtual float scoreElement(Element * element) const
    {
        Function * f = element_cast<Function>(element);
        if(!f)
            return 0;

        if(f->calculator()->uniqueName() != T::UniqueName())
            return 0;
        else
            return 2.0f;
    }

    virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const
	{
        Function * f = element_cast<Function>(element);
        if(!f || f->calculator()->uniqueName() != T::UniqueName())
            throw Exception(QString("The supplied calculator is not of name %1").arg(f->calculator()->uniqueName()), "NAryFunctionWriter::writeCode");

        QList<Evaluatable*> lst = f->functionInputs();
        QStringList strLst;

        for(int i = 0; i < lst.size(); i++)
        {
            Element * curElement = lst[i];
            strLst << PrologWriter::FindWriter(curElement).writeCode(curElement, info);
        }

        removeEmptyItems(strLst);

        QString s = QString("(%1)").arg(strLst.join(_symbol));

        // numerical type, store in variable
        if(element->type() == type::numericalType())
        {
            QString varName = info.getUniqueVariable();
            QString varDef = QString("%1 is %2").arg(varName).arg(s);
            info.addPreDefinition(varDef);

            s = varName;
        }

        return s;
    }
private:
    QString _symbol;
};

struct OrFunctionWriter : public ElementWriter
{
    virtual float scoreElement(Element * element) const
    {
        Function * f = element_cast<Function>(element);
        if(!f)
            return 0;

        if(f->calculator()->uniqueName() != function::ORFunctor::UniqueName())
            return 0;
        else
            return 2.0f;
    }

    virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const
	{
        Function * f = element_cast<Function>(element);
        if(!f || f->calculator()->uniqueName() != function::ORFunctor::UniqueName())
            throw Exception(QString("The supplied calculator is not of name %1").arg(f->calculator()->uniqueName()), "NAryFunctionWriter::writeCode");

        // save all variable definitions
        QString preDef = info.allPreDefinitions();
        QString postDef = info.allPostDefinitions();
        info.clearAllPreDefinitions();
        info.clearAllPostDefinitions();

        QList<Evaluatable*> lst = f->functionInputs();

        QStringList strlst;

        for(int i = 0; i < lst.size(); i++)
        {
            QStringList tmplst;

            // find the element and write the code
            Element * curElement = lst[i];
            QString curCode = PrologWriter::FindWriter(curElement).writeCode(curElement, info);

            // prepend the predefs and postpend the postdefs
            tmplst << info.allPreDefinitions() << curCode << info.allPostDefinitions();

            // clear the list of empty items and add to the variables
            removeEmptyItems(tmplst);
            strlst << tmplst.join(", ");

            // clear the definitions in the codeinfo-object
            info.clearAllPreDefinitions();
            info.clearAllPostDefinitions();
        }

        removeEmptyItems(strlst);

        // restore the old definitions in the codeinfo-object
        info.addPostDefinition(postDef);
        info.addPreDefinition(preDef);

        QString s = QString("(%1)").arg(strlst.join(";"));

        // numerical type, store in variable
        if(element->type() == type::numericalType())
        {
            QString varName = info.getUniqueVariable();
            QString varDef = QString("%1 is %2").arg(varName).arg(s);
            info.addPreDefinition(varDef);

            s = varName;
        }

        return s;
    }
};

struct NotFunctionWriter : public prolog::ElementWriter
{
    virtual float scoreElement(Element * element) const
    {
        Function * f = element_cast<Function>(element);
        if(!f)
            return 0;

        if(f->calculator()->uniqueName() != function::NOTFunctor::UniqueName())
            return 0;
        else
            return 2.0f;
    }

    virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const
	{
        Function * f = element_cast<Function>(element);
        if(!f || f->calculator()->uniqueName() != function::NOTFunctor::UniqueName())
            throw Exception("The supplied element is not a NOT-function", "NotFunctionWriter::writeCode");

        Element * e = f->functionInputs().first();
        const ElementWriter & w = PrologWriter::FindWriter(e);

        QString preDef = info.allPreDefinitions();
        QString postDef = info.allPostDefinitions();
        info.clearAllPreDefinitions();
        info.clearAllPostDefinitions();

        QString code = w.writeCode(e, info);

        QStringList lst = QStringList() << info.allPreDefinitions() << code << info.allPostDefinitions();
        // clear the list of empty items and add to the variables
        removeEmptyItems(lst);
        QString output = QString("\\+( %1 )").arg(lst.join(", "));


        info.clearAllPostDefinitions();
        info.clearAllPreDefinitions();
        info.addPostDefinition(postDef);
        info.addPreDefinition(preDef);

        return output;
    }
};



class ActionWriter : public ElementWriter
{
    virtual float scoreElement(Element * element) const
    {
        return element_castable<Action>(element) ? 1.0f : 0.0f;
    }

    virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const
	{
        Action * action  = element_cast<Action>(element);
        if(!action)
            throw Exception("The supplied element is not an action", "ActionWriter::writeCode");

        Evaluatable * inputVal = action->inputVal();
        QString valCode = PrologWriter::FindWriter(inputVal).writeCode(inputVal, info);

        QStringList lst =  QStringList() << info.allPreDefinitions() << valCode << info.allPostDefinitions();
        removeEmptyItems(lst);
        return QString("do(%1, %3) :- %2.").arg(action->name()).arg(lst.join(", ")).arg(info.ruleNumber());
    }
};

struct RaiseActionWriter : public ElementWriter
{
    virtual float scoreElement(Element * element) const
    {
        RaiseAction * a = element_cast<RaiseAction>(element);
        if(a)
            return 2.0;
        else
            return 0;
    }

    virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const
	{
        RaiseAction * a = element_cast<RaiseAction>(element);
        if(!a)
            throw Exception("The supplied element is not a RaiseAction", "RaiseActionWriter::writeCode");

        Evaluatable * betSize = a->inputBetSize();
        Evaluatable * inputVal = a->inputVal();

        QString betStr = PrologWriter::FindWriter(betSize).writeCode(betSize, info);
        QString valCode = PrologWriter::FindWriter(inputVal).writeCode(inputVal, info);

        QStringList lst  = QStringList() << info.allPreDefinitions() << valCode << info.allPostDefinitions();
        removeEmptyItems(lst);
        return QString("do(raise(%1), %3) :- %2.").arg(betStr).arg(lst.join(", ")).arg(info.ruleNumber());
    }
};

struct ContainsFunctionWriter : public ElementWriter
{
    virtual float scoreElement(Element * element) const
    {
        Function * f = element_cast<Function>(element);
        if(!f)
            return 0;

        if(f->calculator()->uniqueName() != function::ContainsFunctor::UniqueName())
            return 0;
        else
            return 2.0f;
    }

    virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const
	{
        Function * f = element_cast<Function>(element);
        if(!f || f->calculator()->uniqueName() != function::ContainsFunctor::UniqueName())
            throw Exception("The supplied element is not a contains-function", "ContainsFunctionWriter::writeCode");

        Element * cardLst = f->functionInputs().at(0);
		Element * cardEq = f->functionInputs().at(1);

        const ElementWriter & wLst = PrologWriter::FindWriter(cardLst);
        const ElementWriter & wEq = PrologWriter::FindWriter(cardEq);

        return QString("members([%2],%1)").arg(wLst.writeCode(cardLst, info)).arg(wEq.writeCode(cardEq, info));
    }

};

void initializePrologWriter()
{
    PrologWriter::RegisterWriter(new BooleanConstantWriter);
    PrologWriter::RegisterWriter(new FeatureWriter);

    PrologWriter::RegisterWriter(new NumericalConstantWriter);
    PrologWriter::RegisterWriter(new NotFunctionWriter);

    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::ANDFunctor>(", "));
    PrologWriter::RegisterWriter(new OrFunctionWriter);


    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::AddFunctor>(" + "));
    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::MultiplyFunctor>(" * "));
    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::DivideFunctor>(" / "));
    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::SubtractFunctor>(" - "));
    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::BoolEqualFunctor>(" == "));
    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::NumLesserThanOrEqualFunctor>(" =< "));
    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::NumLesserThanFunctor>(" < "));
    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::NumEqualFunctor>(" == "));
    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::NumGreaterThanFunctor>(" > "));
    PrologWriter::RegisterWriter(new NAryFunctionWriter<function::NumGreaterThanOrEqualFunctor>(" >= "));

    PrologWriter::RegisterWriter(new ActionWriter);
    PrologWriter::RegisterWriter(new RaiseActionWriter);
    PrologWriter::RegisterWriter(new CardEquationConstantWriter);
    PrologWriter::RegisterWriter(new ContainsFunctionWriter);
}



} // namespace prolog
} // namespace poker
