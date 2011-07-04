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

#include "type.hpp"
#include "util/translator.hpp"
#include <QDebug>

namespace ruleSystem
{
	namespace
	{
		QMap<QString, const char *> & map() { static QMap<QString, const char *> map; return map; }
	}

	Type::Type(const QString & typeName, int variantTypeNumber)
		: _typeName(typeName),
		_variantTypeNumber(variantTypeNumber)
	{
		map()[typeName] = QMetaType::typeName(variantTypeNumber);
	}

	Type::Type(const QString & typeName, const QVariant & demoValue)
		: _typeName(typeName),
		_variantTypeNumber(demoValue.userType())
	{
		map()[typeName] = demoValue.typeName();
	}

	bool Type::checkVariant(const QVariant & variant) const
	{
		return (variant.isValid() && !variant.isNull() && variant.userType() == variantTypeNumber());
	}

	bool Type::operator==(const Type & rhs) const
	{
		return rhs.typeName() == typeName() && rhs.variantTypeNumber() == variantTypeNumber();
	}

	bool Type::operator!=(const Type & rhs) const
	{
		return !operator==(rhs);
	}

	bool Type::operator<(const Type & rhs) const
	{
		if(typeName() == rhs.typeName())
			return variantTypeNumber() < rhs.variantTypeNumber();
		else
			return typeName() < rhs.typeName();
	}
	bool Type::operator>(const Type & rhs) const
	{
		return rhs.operator <(*this);
	}

	bool Type::isValid() const
	{
		return _variantTypeNumber != -1 && typeName().isNull();
	}

	QDataStream & operator>>(QDataStream & stream, Type & type)
	{
		QString typeName;
		qint32 variantTypeNumber;

		stream >> typeName >> variantTypeNumber;

		type.setTypename(typeName);
	  type.setVariantTypeNumber(QMetaType::type(map()[typeName]));

		return stream;
	}

	QDataStream & operator<<(QDataStream & stream, const Type & type)
	{
		QString typeName = type.typeName();
		qint32 variantTypeNumber = type.variantTypeNumber();

		stream << typeName << variantTypeNumber;

		return stream;
	}
}

ruleSystem::Type type::unknownType()
{
	return ruleSystem::Type(Translator::AddTranslation("unknownType", Translator::tr("unknownType")), QVariant::fromValue<void*>(0));
}

ruleSystem::Type type::booleanType()
{
	return ruleSystem::Type(Translator::AddTranslation("boolean", Translator::tr("boolean")), QVariant::fromValue<bool>(true));
}

ruleSystem::Type type::voidType()
{
	return ruleSystem::Type(Translator::AddTranslation("void", Translator::tr("void")), -1);
}
