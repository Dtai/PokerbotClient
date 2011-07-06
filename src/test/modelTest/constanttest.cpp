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

#include "constanttest.hpp"
#include "ruleSystem/constant.hpp"
#include <ruleSystem/feature.hpp>
#include <pokerRuleSystem/types.hpp>
#include <pokerRuleSystem/card/card.hpp>

using namespace ruleSystem;
using namespace poker;

ConstantTest::ConstantTest(QObject *parent)
	: QObject(parent)
{
}
void ConstantTest::testCreation()
{
	Constant * c1 = new Constant(type::booleanType(), QVariant(true));

	delete c1;
}

void ConstantTest::testDeletion()
{
	Constant * c1 = new Constant(type::booleanType(), QVariant(true));
	delete c1;
}

void ConstantTest::testCasting()
{
	Constant * c1 = new Constant(type::booleanType(), QVariant(true));

	QCOMPARE(element_cast<Evaluatable>(c1), c1);
	QCOMPARE(element_cast<Element>(c1), c1);
	QCOMPARE(element_cast<Feature>(c1), (Feature*)0);
	QCOMPARE(element_castable(c1, Constant::TypeID()), true);
	QCOMPARE(element_castable(c1, Feature::TypeID()), false);

	delete c1;
}

void ConstantTest::testEvaluating()
{
	Constant * c1 = new Constant(type::booleanType(), QVariant(true));
	Constant * c2 = new Constant(type::booleanType(), QVariant(false));
	Constant * c3 = new Constant(type::numericalType(), QVariant(10.0f));

	QCOMPARE(c1->calculateValue().toBool(), true);
	QCOMPARE(c2->calculateValue().toBool(), false);
	QCOMPARE(c3->calculateValue().toFloat(), 10.0f);

	delete c1;
	delete c2;
	delete c3;
}
