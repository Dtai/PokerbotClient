/*******************************************************************
* Copyright (c) 2009 Thomas Fannes (thomasfannes@gmail.com)
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

#include "functiontest.hpp"

#include <ruleSystem/function.hpp>
#include <ruleSystem/constant.hpp>

#include <pokerRuleSystem/booleanfunction.hpp>

using namespace ruleSystem;
using namespace poker;

namespace
{
	Constant * createBoolConstant()
	{
		return new Constant(type::booleanType(), QVariant(true));
	}
	Constant * createNumConstant()
	{
		return new Constant(type::numericalType(), QVariant(12.0f));
	}
}

FunctionTest::FunctionTest(QObject *parent) :
		QObject(parent)
{
}

void FunctionTest::cfunc_create()
{
	Function * f = new Function(CalculatorCreator<function::BoolEqualFunctor>::Create());

	QCOMPARE(f->isCorrect(), false);
	QCOMPARE(f->numberOfInputs(), 2);
	QCOMPARE(f->hasInputAt("1"), true);
	QCOMPARE(f->hasInputAt("0"), true);
	QCOMPARE(f->hasInputAt("2"), false);
	QCOMPARE(f->hasInputAt("1f"), false);
	QCOMPARE(f->inputAt("1"), (Element*)0);
	QCOMPARE(f->inputAt("2"), (Element*)0);
	QCOMPARE(f->inputAt("0"), (Element*)0);

	delete f;
}

void FunctionTest::cfunc_setandremoveTest()
{
	Function * f = new Function(CalculatorCreator<function::BoolEqualFunctor>::Create());

	Constant * cb1 = createBoolConstant();
	Constant * cb2 = createBoolConstant();
	Constant * cn = createNumConstant();

	bool accepted;
	f->setInput("1", cn, &accepted);
	QCOMPARE(accepted, false);
	QCOMPARE(f->inputAt("1"), (Element*)0);
	QCOMPARE(f->numberOfInputs(), 2);

	f->setInput("2", cb1, &accepted);
	QCOMPARE(accepted, false);
	QCOMPARE(f->inputAt("2"), (Element*)0);
	QCOMPARE(f->numberOfInputs(), 2);

	f->setInput("0", cb1, &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(f->inputAt("0"), cb1);
	QCOMPARE(cb1->parent(), f);
	QCOMPARE(f->numberOfInputs(), 2);

	Element * kickOut = f->setInput("0", cb2, &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(f->inputAt("0"), cb2);
	QCOMPARE(kickOut, cb1);
	QCOMPARE(cb1->parent(), (Element*)0);
	QCOMPARE(f->numberOfInputs(), 2);

	f->setInput("1", cb2, &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(f->inputAt("0"), (Element*)0);
	QCOMPARE(f->inputAt("1"), cb2);
	QCOMPARE(cb2->parent(), f);
	QCOMPARE(f->numberOfInputs(), 2);

	f->setInput("append", cb1, &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(f->numberOfInputs(), 2);

	f->setInput("0", cb1, &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(f->numberOfInputs(), 2);

	Element * k2 = f->removeInputAt("0", &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(k2, cb1);
	QCOMPARE(cb1->parent(), (Element*)0);
	QCOMPARE(f->numberOfInputs(), 2);

	delete f;
	delete cb1;
	delete cn;
}

void FunctionTest::ufunc_create()
{
	Function * f = new Function(CalculatorCreator<function::AddFunctor>::Create());

	QCOMPARE(f->isCorrect(), false);
	QCOMPARE(f->numberOfInputs(), 2);
	QCOMPARE(f->hasInputAt("1"), true);
	QCOMPARE(f->hasInputAt("0"), true);
	QCOMPARE(f->hasInputAt("2"), false);
	QCOMPARE(f->hasInputAt("1f"), false);
	QCOMPARE(f->inputAt("1"), (Element*)0);
	QCOMPARE(f->inputAt("2"), (Element*)0);
	QCOMPARE(f->inputAt("0"), (Element*)0);

	delete f;
}

void FunctionTest::ufunc_setremoveandappendTest()
{
	Function * f = new Function(CalculatorCreator<function::AddFunctor>::Create());

	bool accepted;
	Constant * c1 = createNumConstant();
	Constant * c2 = createNumConstant();
	Constant * c3 = createNumConstant();
	Constant * c4 = createNumConstant();

	for(int i = 0;i < 10; i++)
	{
		f->setInput("append", c1, &accepted);
		QCOMPARE(accepted, true);
		QCOMPARE(f->numberOfInputs(), 2);
		QCOMPARE(f->inputAt("0"),c1);
		QCOMPARE(f->inputAt("1"), (Element*)0);
		QCOMPARE(f, c1->parent());
	}

	f->setInput("append", c2, &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(f->numberOfInputs(), 2);
	QCOMPARE(f->inputAt("0"), c1);
	QCOMPARE(f->inputAt("1"), c2);

	f->setInput("append", c3, &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(f->numberOfInputs(), 3);
	QCOMPARE(f->inputAt("0"),c1);
	QCOMPARE(f->inputAt("2"), c3);

	f->setInput("9", c4, &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(f->numberOfInputs(), 4);
	QCOMPARE(f->inputAt("0"),c1);
	QCOMPARE(f->inputAt("3"), c4);

	Element * k1 = f->removeInputAt("2", &accepted);
	QCOMPARE(accepted, true);
	QCOMPARE(k1, c3);
	QCOMPARE(f->inputAt("0"), c1);
	QCOMPARE(f->inputAt("1"), c2);
	QCOMPARE(f->inputAt("2"), c4);

	Element * k2 = f->removeInputAt("9", &accepted);
	QCOMPARE(accepted, false);
	QCOMPARE(k2, (Element*)0);


	delete f;
	delete c3;
}

