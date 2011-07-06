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

#include "serializationtest.hpp"

#include <ruleSystem/function.hpp>
#include <ruleSystem/constant.hpp>
#include <ruleSystem/dbwrapper.hpp>
#include <ruleSystem/serialization/qt/elementserializer.hpp>

#include <pokerRuleSystem/pokerrulesystem.hpp>
#include <pokerRuleSystem/simpledb.hpp>
#include <cassert>

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

	Constant * createCardListConstant()
	{
		QList<Card> lst = QList<Card>() << Card(Card::Diamonds(), "== 8");
		QVariant v = QVariant::fromValue(lst);
		return new Constant(type::cardListType(), v);
	}

	void compareTwoConstants(Constant * c1, Constant * c2)
	{
		QVERIFY(c1 != 0);
		QVERIFY(c2 != 0);
		QCOMPARE(c1->name(), c2->name());
		QCOMPARE(c1->type(), c2->type());

		if(c1->value().userType() == qMetaTypeId<QList<poker::Card> >())
			QCOMPARE(c1->value().value<QList<poker::Card> >(), c2->value().value<QList<poker::Card> >());
		else
			QCOMPARE(c1->value(), c2->value());
		QCOMPARE(c1->description(), c2->description());
	}

	void compareTwoFeatures(Feature * f1, Feature * f2)
	{
		QVERIFY(f1 != 0);
		QVERIFY(f2 != 0);
		QCOMPARE(f1->db(), f2->db());
		QCOMPARE(f1->description(), f2->description());
		QCOMPARE(f1->name(), f2->name());
		QCOMPARE(f1->calculateValue(), f2->calculateValue());
	}

	void compareTwoFunctions(Function * f1, Function * f2)
	{
		QVERIFY(f1 != 0);
		QVERIFY(f2 != 0);

		QCOMPARE(f1->name(), f2->name());
		QCOMPARE(f1->calculator(), f2->calculator());
	}

	void compareTwoElements(Element * e1, Element * e2)
	{
		QVERIFY(e1 != 0);
		QVERIFY(e2 != 0);

		QCOMPARE(e1->type(), e2->type());

		if(e1->typeID() == Constant::TypeID())
			compareTwoConstants(element_cast<Constant>(e1), element_cast<Constant>(e2));
		else if(e1->typeID() == Feature::TypeID())
			compareTwoFeatures(element_cast<Feature>(e1), element_cast<Feature>(e2));
		else if(e1->typeID() == Function::TypeID())
			compareTwoFunctions(element_cast<Function>(e1), element_cast<Function>(e2));

		QCOMPARE(e1->inputPositions().size(), e2->inputPositions().size());

		QList<QString> inputs = e1->inputPositions();
		foreach(const QString & s, inputs)
			compareTwoElements(e1->inputAt(s), e2->inputAt(s));
	}
}


SerializationTest::SerializationTest(QObject *parent)
	: QObject(parent)
{
}

void SerializationTest::testConstant()
{
	poker::initialise();

	Constant * src_c1 = createBoolConstant();
	Constant * src_c2 = createNumConstant();
	Constant * src_c3 = createCardListConstant();
	src_c1->setDescription("testPomschrijving");
	src_c2->setDescription("balahlblsha ");
	src_c3->setDescription("testke");

	QByteArray ar;
	QDataStream s1(&ar, QIODevice::WriteOnly);

	s1 << src_c1 << src_c2 << src_c3;

	Element * dst_c1;
	Element * dst_c2;
	Element * dst_c3;

	QDataStream s2(&ar, QIODevice::ReadOnly);
	s2 >> dst_c1 >> dst_c2 >> dst_c3;

	compareTwoElements(dst_c1, src_c1);
	compareTwoElements(dst_c2, src_c2);
	compareTwoElements(dst_c3, src_c3);

	delete src_c1;
	delete src_c2;
	delete src_c3;
	delete dst_c1;
	delete dst_c2;
	delete dst_c3;
}

void SerializationTest::testFeature()
{
	SimpleDB db("testDB");
	db.registerFeature("feature1", type::numericalType(), QVariant(2.04f));
	DBWrapper::RegisterDB(&db);

	Feature * src_f = db.createFeature("feature1");
	src_f->setDescription("asd;j asldkj asldkj");

	QByteArray ar;
	QDataStream s1(&ar, QIODevice::WriteOnly);

	s1 << src_f;

	Element * dst_f;

	QDataStream s2(&ar, QIODevice::ReadOnly);
	s2 >> dst_f;

	compareTwoElements(dst_f, src_f);

	delete dst_f;
	delete src_f;
}

void SerializationTest::testFunction()
{
	Function * f1 = new Function(CalculatorCreator<function::ORFunctor>::Create());
	Function * f2 = new Function(CalculatorCreator<function::NumEqualFunctor>::Create());
	f1->setFunctionInput(0, f2);
	f1->setFunctionInput(1, createBoolConstant());
	f1->setFunctionInput(2, createBoolConstant());

	f2->setFunctionInput(0, createNumConstant());
	f2->setFunctionInput(1, createNumConstant());

	QByteArray ar;
	QDataStream s1(&ar, QIODevice::WriteOnly);

	s1 << f1;

	Element * dst_f1;

	QDataStream s2(&ar, QIODevice::ReadOnly);
	s2 >> dst_f1;

	compareTwoElements(f1, dst_f1);

	delete f1;
	delete dst_f1;
}
