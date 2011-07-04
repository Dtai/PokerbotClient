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

#ifndef CALCULATORFACTORY_HPP
#define CALCULATORFACTORY_HPP

#include <QDataStream>
#include "calculator.hpp"


namespace ruleSystem
{
	template <class T> class CalculatorCreator;

	class CalculatorFactory
	{
		Q_DECLARE_TR_FUNCTIONS(CalculatorFactory);

	public:
		template <class T> static void RegisterCalculator();

		const Calculator * deserialize(QDataStream & stream);
		void serialize(const Calculator * calculator, QDataStream & stream);

	private:
		static void RegisterCalculator(const Calculator * (*creator)(), const QString & uniqueName);
	};

	template <class T> void CalculatorFactory::RegisterCalculator()
	{
		RegisterCalculator(&(CalculatorCreator<T>::Create), CalculatorCreator<T>::UniqueName());
	}

	template <class T> class CalculatorRegisterer
	{
	public:
		CalculatorRegisterer()
		{
			CalculatorFactory::RegisterCalculator<T>();
		}
	};
}

QDataStream & operator<<(QDataStream & s, const ruleSystem::Calculator * calc);
QDataStream & operator>>(QDataStream & s, const ruleSystem::Calculator *& calc);

#endif // CALCULATORFACTORY_HPP
