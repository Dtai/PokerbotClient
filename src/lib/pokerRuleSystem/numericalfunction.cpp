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

#include "numericalfunction.hpp"
#include <ruleSystem/calculatorfactory.hpp>

using namespace ruleSystem;

namespace poker
{
namespace function
{
const Function::InputList AddFunctor::InputTypes()
{
    return Function::InputList::CreateUncountedList(type::numericalType(), 2);
}
const Function::InputList MultiplyFunctor::InputTypes()
{
    return Function::InputList::CreateUncountedList(type::numericalType(), 2);
}
const Function::InputList SubtractFunctor::InputTypes()
{
    return Function::InputList::CreateCountedList(type::numericalType(), 2);
}
const Function::InputList DivideFunctor::InputTypes()
{
    return Function::InputList::CreateCountedList(type::numericalType(), 2);
}
const Function::InputList InvertFunctor::InputTypes()
{
    return Function::InputList::CreateCountedList(type::numericalType(), 1);
}

QVariant AddFunctor::operator()(const QList<Evaluatable*> & vals) const
{
    float value = 0;

    for(int i = 0; i < vals.size(); i++)
        value += vals[i]->calculateValue().toFloat();


    return QVariant::fromValue<float>(value);
}

QVariant SubtractFunctor::operator()(const QList<Evaluatable*> & val) const
{
    return QVariant::fromValue<float>(val[0]->calculateValue().toFloat() - val[1]->calculateValue().toFloat());
}

QVariant MultiplyFunctor::operator()(const QList<Evaluatable*> & val) const
{
    float value = 1;

    for(int i = 0; i < val.size(); i++)
        value *= val[i]->calculateValue().toFloat();

    return QVariant::fromValue<float>(value);
}

QVariant DivideFunctor::operator()(const QList<Evaluatable*> & val) const
{
    return QVariant::fromValue<float>(val[0]->calculateValue().toFloat() / val[1]->calculateValue().toFloat());
}

QVariant InvertFunctor::operator()(const QList<ruleSystem::Evaluatable*> & val) const
{
    return QVariant::fromValue<float>(- val[0]->calculateValue().toFloat());
}
}
}



