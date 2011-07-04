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

#include "simpledb.hpp"
#include <ruleSystem/type.hpp>
#include <ruleSystem/feature.hpp>

using namespace ruleSystem;

namespace poker
{

	SimpleDB::SimpleDB(const QString & name)
		: IDB(name)
	{
	}

	void SimpleDB::registerFeature(const QString & name, const Type & type, QVariant initialValue)
	{
		_registeredVariants[name].value = _undefined;
		_registeredVariants[name].type = type;

		setFeatureValue(name, initialValue);
	}

	void SimpleDB::setFeatureValue(const QString & name, const QVariant & value)
	{
		if(!_registeredVariants.contains(name) || _registeredVariants[name].type.variantTypeNumber() != value.userType())
			return;

		_registeredVariants[name].value = value;
	}

	const QVariant & SimpleDB::getFeatureValue(const QString & name) const
	{
		QMap<QString, VariantData>::const_iterator i = _registeredVariants.find(name);

		return (i == _registeredVariants.end() ? _undefined : i.value().value);
	}

	Type SimpleDB::getFeatureType(const QString & name) const
	{
		QMap<QString, VariantData>::const_iterator i = _registeredVariants.find(name);

		return (i == _registeredVariants.end() ? type::unknownType() : i.value().type);
	}

	bool SimpleDB::hasFeature(const QString & name) const
	{
		return _registeredVariants.contains(name);
	}

	QList<QString> SimpleDB::findAllVariantNames(const ruleSystem::Type & type) const
	{
		QMap<QString, VariantData>::const_iterator i;
		QList<QString> foundNames;

		if(type == Type())
		{
			for(i = _registeredVariants.begin(); i != _registeredVariants.end(); ++i)
				foundNames << i.key();
		}
		else
		{
			for(i = _registeredVariants.begin(); i != _registeredVariants.end(); ++i)
				if(i.value().type == type)
					foundNames << i.key();
		}

		return foundNames;
	}

	Feature * SimpleDB::createFeature(const QString & name)
	{
		QMap<QString, VariantData>::const_iterator i = _registeredVariants.find(name);
		Feature * feature = 0;

		if(i == _registeredVariants.end())
			return 0;


		feature = new Feature(i.value().type, i.key());
		feature->setDB(this);

		return feature;
	}

	QList<ruleSystem::Feature *> SimpleDB::createFeatures(const QList<QString> & names)
	{
		QList<ruleSystem::Feature *> lst;
		foreach(const QString & name, names)
		{
			Feature * el = createFeature(name);
			if(el != 0)
				lst << el;
		}

		return lst;
	}
}
