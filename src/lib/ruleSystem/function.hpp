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

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "evaluatable.hpp"

namespace ruleSystem
{
	class Calculator;

	class Function : public Evaluatable
	{
	public:
		class InputList
		{
		public:
			class Element
			{
			private:
				Element(int numberOfInputs, int minNumberOfInputs, const Type & type);

			public:
				static InputList::Element CreateCountedElement(int numberOfInputs, const Type & type);
				static InputList::Element CreateUncountedElement(int minNumberOfInputs, const Type & type);

			private:
				SimpleVarGet(int, numberOfInputs);
				SimpleVarGet(int, minNumberOfInputs);
				RefVarGet(Type, type);
			};

			InputList(const QList<InputList::Element> & inputElements);
			InputList(const InputList::Element & inputElement);

			const InputList::Element * findInputElement(int position) const;
			Type typeAt(int position) const;
			bool isExtendable() const;
			int calculateStartPos(int typesPosition) const;
			int maxNumberOfElements() const;
			int minNumberOfElements() const;


			static InputList CreateUncountedList(const Type & type, int minNumberOfElements);
			static InputList CreateCountedList(const Type & type, int numberOfElements);

		private:
			RefVarGet(QList<InputList::Element>, inputElements);
		};

		TYPEID_INHERIT("Function", Evaluatable);

		Function(const Calculator * calculator);

		/* Implementation of virtual functions */
		virtual QVariant calculateValue();
		virtual bool isCorrect(QString * errorMessage = 0) const;
		virtual Function * clone() const;
		virtual QList<QString> requiredInputs() const;

		/* input type management functions */
		const InputList & inputList() const;
		QList<Evaluatable*> functionInputs() const;
		QList<QString> functionInputPositions() const;
		Element * functionInputAt(int inputPosition) const;
		Element * setFunctionInput(int inputPosition, Element * element, bool * succeeded = 0, QString * errorMessage = 0);
		Element * setFunctionInput(int inputPosition, Element * element, QString * errorMessage);
		virtual Type inputType(const QString & inputPosition, bool & isValid) const;


	protected:
		virtual QString translateInputPosition(const QString & inputPosition) const;
		virtual void onInputChanged(const QString & inputPosition, Element * oldElement);

	private:
		static QString numberToString(int number);
		static int stringToNumber(const QString & str);

		void checkAndCleanInputs();
		void checkCountedInputZone(int startPos, const InputList::Element & zone);
		void checkUncountedInputZone(int startPos, const InputList::Element & zone);
		void removeZeroPosition(int position);

		PtrVarGet(const Calculator, calculator);
	};
}

#endif // FUNCTION_HPP
