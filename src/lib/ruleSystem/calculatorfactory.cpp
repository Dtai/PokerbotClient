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

#include "calculatorfactory.hpp"
#include "calculator.hpp"
#include "exception.hpp"

namespace ruleSystem
{
	typedef const Calculator * (*Creator)();

	namespace
	{
		QMap<QString, Creator> & creatorMap()
		{
			static QMap<QString, Creator> m;
			return m;
		}
	}

	const Calculator * CalculatorFactory::deserialize(QDataStream & stream)
	{
		QString name;
		stream >> name;

		if(name.isEmpty())
			return 0;

		QMap<QString, Creator>::iterator i = creatorMap().find(name);
		if(i == creatorMap().end())
			throw Exception(QString(tr("name %1 not found")).arg(name), "CalculatorFactory");
		else
			return i.value()();
	}

	void CalculatorFactory::serialize(const Calculator * calculator, QDataStream & stream)
	{
		if(calculator == 0)
		{
			stream << QString();
			return;
		}

		stream << calculator->uniqueName();
	}

	void CalculatorFactory::RegisterCalculator(Creator creator, const QString & uniqueName)
	{
		creatorMap()[uniqueName] = creator;
	}
}

QDataStream & operator<<(QDataStream & s, const ruleSystem::Calculator * calc)
{
	ruleSystem::CalculatorFactory f;
	f.serialize(calc, s);

	return s;
}

QDataStream & operator>>(QDataStream & s, const ruleSystem::Calculator *& calc)
{
	ruleSystem::CalculatorFactory f;
	calc = f.deserialize(s);

	return s;
}
