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

#include "elementwriter.hpp"
#include "../action.hpp"
#include "../constant.hpp"
#include "../exception.hpp"
#include "../feature.hpp"

namespace ruleSystem {
namespace prolog {

float BooleanConstantWriter::scoreElement(Element * element) const
{
    Constant * c = element_cast<Constant>(element);
    if(!c)
        return 0;

    if(c->type() == type::booleanType())
        return 1.0f;
    else
        return 0;
}

QString BooleanConstantWriter::writeCode(Element * element, PrologWriter::CodeInformation & /*info*/) const
{
    Constant * c = element_cast<Constant>(element);
    if(!c || c->type() != type::booleanType())
        throw Exception(Exception::tr("The supplied element is not an boolean constant"), "BooleanConstantWriter::writeCode");

    if(c->value().toBool())
        return "true";
    else
        return "false";
}

float FeatureWriter::scoreElement(Element * element) const
{
    Feature * f = element_cast<Feature>(element);
    if(f)
        return 1;
    else
        return 0;
}

QString FeatureWriter::writeCode(Element * element, PrologWriter::CodeInformation & info) const
{
    Feature * f = element_cast<Feature>(element);
    if(!f)
        throw Exception(Exception::tr("The supplied element is not a feature"), "FeatureWriter::writeCode");

    if(f->type() == type::booleanType())
        return f->name();

	QString var = info.getUniqueVariable();
	QString varDef = QString("%1(%2)").arg(f->devName()).arg(var);
    info.addPreDefinition(varDef);

    return var;
}


} // namespace prolog
} // namespace ruleSystem
