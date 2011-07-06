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

#include "featuretest.hpp"
#include <ruleSystem/feature.hpp>
#include <pokerRuleSystem/simpledb.hpp>
#include <pokerRuleSystem/types.hpp>

using namespace ruleSystem;
using namespace poker;

FeatureTest::FeatureTest(QObject *parent)
	: QObject(parent)
{
}

void FeatureTest::testCreation()
{
	SimpleDB db;
	Feature * f1 = new Feature(type::numericalType(), "test1");
	f1->setDB(&db);

	delete f1;
}

void FeatureTest::testDB()
{
	SimpleDB db;
	db.registerFeature("test1", type::numericalType(), QVariant(12.0f));
	QCOMPARE(db.hasFeature("test1"), true);
	QCOMPARE(db.getFeatureType("test1"), type::numericalType());
	QCOMPARE(db.getFeatureValue("test1"), QVariant(12.0f));

	QCOMPARE(db.hasFeature("test2"), false);
	QCOMPARE(db.getFeatureType("test2"), type::unknownType());
	QCOMPARE(db.getFeatureValue("test2"), QVariant());

}

void FeatureTest::testEvaluating()
{
	SimpleDB db;
	db.registerFeature("test1", type::numericalType(), QVariant(12.0f));
	Feature * f1 = db.createFeature("test1");
	Feature * f2 = db.createFeature("test2");

	QVERIFY(f1 != 0);
	QVERIFY(f2 == 0);
	QCOMPARE(f1->db(), &db);
	QCOMPARE(f1->calculateValue(), QVariant(12.0f));

	delete f1;
	delete f2;
}

