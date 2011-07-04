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

#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <QVariant>
#include <QList>
#include <QString>
#include "util/macro.hpp"
#include "type.hpp"
#include "evaluatable.hpp"
#include <typeinfo>
#include "function.hpp"
#include <boost/shared_ptr.hpp>

namespace ruleSystem
{
	template<class> class CalculatorCreator;

	class Calculator
	{
		template<class> friend class CalculatorCreator;

	private:
		Calculator(const Type & outputType, const Function::InputList & inputTypes, const QString & name);

	protected:
		~Calculator() {}

	public:
		virtual QVariant calculateValue(const QList<Evaluatable *> & evaluatables) const = 0;
		virtual const QString uniqueName() const  = 0;

	private:
		RefVarGet(Type, outputType);
		RefVarGet(Function::InputList, inputTypes);
		RefVarGet(QString, name);
	};

	template <class T> class CalculatorCreator : public Calculator
	{
	private:
		CalculatorCreator(const Type & outputType, const Function::InputList & inputTypes, const QString & name)
			: Calculator(outputType, inputTypes, name) {}

	private:
		~CalculatorCreator() {}

	public:
		static const QString UniqueName();
		static const Calculator * Create()
		{
			if(_instance().get() == 0)
				_instance() = boost::shared_ptr<Calculator>(new CalculatorCreator( T::OutputType(), Function::InputList(T::InputTypes()), T::VisibleName()), deleter());

			return _instance().get();
		}

		virtual QVariant calculateValue(const QList<Evaluatable *> & evaluatables) const
		{
			QList<Evaluatable*> tmp = evaluatables;
			tmp.removeAll(0);

			T op;
			return op(tmp);
		}
		virtual const QString uniqueName() const { return UniqueName(); }

	private:
		class deleter
		{
		public:
			void operator()(CalculatorCreator * c) { delete c; }
		};

		static boost::shared_ptr<Calculator> & _instance();
	};

	template <class T> const QString CalculatorCreator<T>::UniqueName(){ return T::UniqueName(); }
	template <class T> boost::shared_ptr<Calculator> & CalculatorCreator<T>::_instance()
	{
		static boost::shared_ptr<Calculator> cal;
		return cal;
	}
}

#endif // CALCULATOR_HPP
