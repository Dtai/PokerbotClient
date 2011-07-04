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

#include "booleanfunction.hpp"
#include <ruleSystem/calculatorfactory.hpp>

using namespace ruleSystem;

namespace poker
{
	namespace function
	{
		namespace
		{
			CalculatorRegisterer<ORFunctor> orR;
			CalculatorRegisterer<ANDFunctor> andR;
			CalculatorRegisterer<NOTFunctor> notR;
			CalculatorRegisterer<XORFunctor> xorR;
		}

		const Function::InputList ORFunctor::InputTypes()
		{
			return Function::InputList::CreateUncountedList(type::booleanType(), 2);
		}
		const Function::InputList ANDFunctor::InputTypes()
		{
			return Function::InputList::CreateUncountedList(type::booleanType(), 2);
		}
		const Function::InputList NOTFunctor::InputTypes()
		{
			return Function::InputList::CreateCountedList(type::booleanType(), 1);
		}
		const Function::InputList XORFunctor::InputTypes()
		{
			return Function::InputList::CreateCountedList(type::booleanType(), 2);
		}
		const Function::InputList ContainsFunctor::InputTypes()
		{
			Function::InputList::Element e1 = Function::InputList::Element::CreateCountedElement(1, type::cardListType());
			Function::InputList::Element e2 = Function::InputList::Element::CreateCountedElement(1, type::cardEquationType());

			return Function::InputList(QList<Function::InputList::Element>() << e1 << e2);
		}

		QVariant ORFunctor::operator()(const QList<ruleSystem::Evaluatable*> & vals) const
		{
			for(int i = 0; i < vals.size(); i++)
				if(vals[i]->calculateValue().toBool() == true)
					return QVariant::fromValue<bool>(true);

			return QVariant::fromValue<bool>(false);
		}

		QVariant ANDFunctor::operator()(const QList<ruleSystem::Evaluatable*> & vals) const
		{
			for(int i = 0; i < vals.size(); i++)
				if(vals[i]->calculateValue().toBool() == false)
					return QVariant::fromValue<bool>(false);

			return QVariant::fromValue<bool>(true);
		}
		QVariant NOTFunctor::operator()(const QList<ruleSystem::Evaluatable*> & vals) const
		{
			return QVariant::fromValue<bool>(!vals[0]->calculateValue().toBool());
		}
		QVariant XORFunctor::operator()(const QList<ruleSystem::Evaluatable*> & vals) const
		{
			return QVariant::fromValue<bool>(vals[0]->calculateValue().toBool() != vals[1]->calculateValue().toBool());
		}



		QVariant ContainsFunctor::operator()(const QList<ruleSystem::Evaluatable*> & /*vals*/) const
		{
			return true;
		}
	}
}



