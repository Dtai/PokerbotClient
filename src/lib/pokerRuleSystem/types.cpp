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

#include "types.hpp"
#include "booleanfunction.hpp"
#include <ruleSystem/calculatorfactory.hpp>
#include <ruleSystem/util/translator.hpp>

using namespace ruleSystem;

namespace type
{
	ruleSystem::Type numericalType()
	{
		return ruleSystem::Type(Translator::AddTranslation("numerical", Translator::tr("numerical")), QVariant::fromValue<float>(1.0f));
	}

	ruleSystem::Type cardListType()
	{
		return ruleSystem::Type(Translator::AddTranslation("cardList", Translator::tr("cardList")), QVariant::fromValue<QList<poker::Card> >(QList<poker::Card>() << poker::Card() ));
	}

	ruleSystem::Type cardEquationType()
	{
		return ruleSystem::Type(Translator::AddTranslation("cardEquation", Translator::tr("cardEquation")), QVariant::fromValue<QList<poker::Card> >(QList<poker::Card>() << poker::Card() ));
	}
}

namespace poker
{
	namespace
	{
		CalculatorRegisterer<function::BoolEqualFunctor> b1();

		CalculatorRegisterer<function::NumEqualFunctor> n1();
		CalculatorRegisterer<function::NumLesserThanFunctor> n3();
		CalculatorRegisterer<function::NumLesserThanOrEqualFunctor> n4();
		CalculatorRegisterer<function::NumGreaterThanFunctor> n5();
		CalculatorRegisterer<function::NumGreaterThanOrEqualFunctor> n6();
	}
}
