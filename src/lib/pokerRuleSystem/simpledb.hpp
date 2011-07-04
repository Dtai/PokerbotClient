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

#ifndef SIMPLEDB_HPP
#define SIMPLEDB_HPP

#include <ruleSystem/idb.hpp>
#include <ruleSystem/feature.hpp>

namespace poker
{
	class SimpleDB : public ruleSystem::IDB
	{
		struct VariantData
		{
			QVariant value;
			ruleSystem::Type type;
		};

	public:
		SimpleDB(const QString & name = QString());

		// overloaded DB functions
		void registerFeature(const QString & name, const ruleSystem::Type & type, QVariant initialValue = QVariant());
		virtual void setFeatureValue(const QString & name, const QVariant & value);
		virtual const QVariant & getFeatureValue(const QString & name) const;
		virtual ruleSystem::Type getFeatureType(const QString & name) const;
		virtual bool hasFeature(const QString & name) const;

		/* Accessor functions */
		QList<QString> findAllVariantNames(const ruleSystem::Type & type = ruleSystem::Type()) const;

		// simple helper functions
		ruleSystem::Feature * createFeature(const QString & name);
		QList<ruleSystem::Feature *> createFeatures(const QList<QString> & names);

	private:
		QMap<QString, VariantData> _registeredVariants;
		QVariant _undefined;
	};
}

#endif // SIMPLEDB_HPP
