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

#include "function.hpp"
#include "calculator.hpp"
#include "calculatorfactory.hpp"

namespace ruleSystem
{
    TYPEID_INHERIT_SOURCE("Function", Evaluatable, Function)

	Function::Function(const Calculator * calculator)
		: Evaluatable(calculator->outputType(), calculator->name()),
		_calculator(calculator)
	{
		checkAndCleanInputs();
	}

	QVariant Function::calculateValue()
	{
		return calculator()->calculateValue(functionInputs());
	}

	bool Function::isCorrect(QString * errorMessage) const
	{
		CleanErrorMsg(errorMessage);

		if(inputList().maxNumberOfElements() == 0)
			return true;

		// get all the inputs
		QList<Evaluatable*> allInputs = functionInputs();

		// check for zero's in the counted piece
		int zeroPos = allInputs.indexOf(0);

		if(zeroPos == -1)
			return true;

		ErrorMsg(errorMessage, QString(tr("This function contains an undefined element at position %1")).arg(zeroPos));
		return false;
	}

	Function * Function::clone() const
	{
		// create the function
		Function * f = new Function(calculator());

		// map the inputs
		for(int i = 0; i < numberOfInputs(); i++)
		{
			QString pos = numberToString(i);
			Element * el = Element::inputAt(pos);
			f->setInput(pos, el == 0 ? 0 : el->clone());
		}

		return f;
	}

	const Function::InputList & Function::inputList() const
	{
		return calculator()->inputTypes();
	}

	QList<QString> Function::requiredInputs() const
	{
		QList<QString> reqInput;

		for(int i = 0; i < inputList().minNumberOfElements(); i++)
			reqInput << numberToString(i);

		return reqInput;
	}

	QList<Evaluatable*> Function::functionInputs() const
	{
		QList<Evaluatable*> lst;
		for(int i = 0; i < numberOfInputs(); i++)
			lst << element_cast<Evaluatable>(functionInputAt(i));

		return lst;
	}

	QList<QString> Function::functionInputPositions() const
	{
		QList<QString> lst;
		for(int i = 0; i < numberOfInputs(); i++)
			lst << numberToString(i);

		return lst;
	}

	Element * Function::functionInputAt(int inputPosition) const
	{
		return Element::inputAt(numberToString(inputPosition));
	}

	Element * Function::setFunctionInput(int inputPosition, Element * element, bool * succeeded, QString * errorMessage)
	{
		return Element::setInput(numberToString(inputPosition), element, succeeded, errorMessage);
	}

	Element * Function::setFunctionInput(int inputPosition, Element * element, QString * errorMessage)
	{
		return setFunctionInput(inputPosition, element, 0, errorMessage);
	}

	Type Function::inputType(const QString & inputPosition, bool & isValid) const
	{
		isValid = false;
		if(inputPosition.size() < 0)
			return Type();

		// convert to the value
		uint pos = inputPosition.toUInt(&isValid);

		// did the conversion go?
		if(!isValid)
			return Type();

		return calculator()->inputTypes().typeAt(pos);
	}

	QString Function::translateInputPosition(const QString & inputPosition) const
	{
		if(inputPosition != "append")
			return inputPosition;

		// find the first zero
		int pos = functionInputs().indexOf(0);
		if(pos != -1)
			return numberToString(pos);

		if(calculator()->inputTypes().isExtendable())
			return numberToString(numberOfInputs());
		else
			return inputPosition;
	}


	void Function::onInputChanged(const QString & inputPosition, Element * oldElement)
	{
		if(oldElement != 0 && Element::inputAt(inputPosition) != 0)
			return;

		checkAndCleanInputs();
	}

	void Function::checkAndCleanInputs()
	{
		int pos = 0;

		for(int i = 0; i < inputList().inputElements().size(); i++)
		{
			const InputList::Element & el = inputList().inputElements()[i];
			if(el.numberOfInputs() == -1)
				checkUncountedInputZone(pos, el);
			else
				checkCountedInputZone(pos, el);

			pos += el.minNumberOfInputs();
		}
	}

	void Function::checkCountedInputZone(int startPos, const InputList::Element & zone)
	{
		// very easy, just make sure each input is a zero
		for(int i = 0; i< zone.numberOfInputs(); i++)
		{
			QString pos = numberToString(i + startPos);
			if(!hasInputAt(pos))
				setInput(pos, 0);
		}
	}

	void Function::checkUncountedInputZone(int startPos, const InputList::Element & zone)
	{
		QList<QString> inp = inputPositions();

		// find the max position we should go to
		int maxPos = 0;
		foreach(const QString & s, inp)
			maxPos = qMax(maxPos, stringToNumber(s));


		// we will start from the current pos
		for(int pos = startPos; pos <= maxPos; pos++)
		{
			QString sPos = numberToString(pos);

			// if the current position is empty
			if(inputAt(sPos) == 0)
			{
				// loop over the next elements
				for(int curPos = pos+1; curPos <= maxPos; curPos++)
				{
					// to find the first not-empty one
					QString sCurPos = numberToString(curPos);
					if(hasInputAt(sCurPos))
					{
						// if found, swap them
						if(inputAt(sCurPos) != 0)
							swapInputs(sPos, sCurPos);

						// by now this position is zero (swapping or was zero), so delete it
						removeInputAt(sCurPos);
					}
				}
			}
		}

		for(int i = 0; i< zone.minNumberOfInputs(); i++)
		{
			QString sPos = numberToString(i + startPos);
			if(!hasInputAt(sPos))
				setInput(sPos, 0);
		}
	}

	void Function::removeZeroPosition(int position)
	{
		QString curPos = numberToString(position);

		for(int i = position; i < numberOfInputs()-1; i++)
		{
			QString nextPos = numberToString(i+1);
			swapInputs(curPos, nextPos);
			curPos = nextPos;
		}
	}


	QString Function::numberToString(int number)
	{
		return QString("%1").arg(number);
	}

	int Function::stringToNumber(const QString & str)
	{
		bool ok;
		int val = str.toInt(&ok);

		if(ok)
			return val;
		else
			return -1;
	}

	Function::InputList::InputList(const QList<InputList::Element> & inputElements)
	{
		for(int i = 0; i < inputElements.size(); i++)
		{
			if(inputElements[i].numberOfInputs() == 0)
				continue;

			_inputElements << inputElements[i];
			if(inputElements[i].numberOfInputs() == -1)
				break;
		}
	}

	Function::InputList::InputList(const InputList::Element & inputElement)
	{
		if(inputElement.numberOfInputs() != 0)
			_inputElements << inputElement;
	}

	const Function::InputList::Element * Function::InputList::findInputElement(int position) const
	{
		if(position < 0)
			return 0;

		foreach(const InputList::Element & p, inputElements())
		{
			// endless amount of this type?
			if(p.numberOfInputs() == -1)
				return &p;

			position -= p.numberOfInputs();
			if(position < 0)
				return &p;
		}

		return 0;
	}

	Type Function::InputList::typeAt(int position) const
	{
		const InputList::Element * el = findInputElement(position);
		if(el == 0)
			return Type();
		else
			return el->type();
	}

	bool Function::InputList::isExtendable() const
	{
		if(inputElements().size() == 0)
			return false;

		return inputElements().last().numberOfInputs() == -1;
	}

	int Function::InputList::maxNumberOfElements() const
	{
		if(inputElements().size() == 0)
			return 0;

		if(inputElements().last().numberOfInputs() == -1)
			return -1;

		int maxNumber = 0;
		for(int i =0 ; i < inputElements().size(); i++)
			maxNumber += inputElements()[i].numberOfInputs();

		return maxNumber;

	}

	int Function::InputList::minNumberOfElements() const
	{
		int minNumber = 0;
		for(int i = 0; i < inputElements().size(); i++)
			minNumber += inputElements()[i].minNumberOfInputs();

		return minNumber;
	}

	int Function::InputList::calculateStartPos(int typesPosition) const
	{
		if(typesPosition < 0 || typesPosition >= inputElements().size())
			return -1;

		int startPos = 0;
		for(int i = 0; i < typesPosition; i++)
			startPos += inputElements()[i].numberOfInputs();

		return startPos;
	}

	Function::InputList Function::InputList::CreateUncountedList(const Type & type, int minNumberOfElements)
	{
		return InputList(InputList::Element::CreateUncountedElement(minNumberOfElements, type));
	}

	Function::InputList Function::InputList::CreateCountedList(const Type & type, int numberOfElements)
	{
		return InputList(InputList::Element::CreateCountedElement(numberOfElements, type));
	}

	Function::InputList::Element::Element(int numberOfInputs, int minNumberOfInputs, const Type & type)
		: _numberOfInputs(numberOfInputs),
		_minNumberOfInputs(minNumberOfInputs),
		_type(type)
	{
	}

	Function::InputList::Element Function::InputList::Element::CreateCountedElement(int numberOfInputs, const Type & type)
	{
		return Function::InputList::Element(numberOfInputs, numberOfInputs, type);
	}
	Function::InputList::Element Function::InputList::Element::CreateUncountedElement(int minNumberOfInputs, const Type & type)
	{
		return Function::InputList::Element(-1, minNumberOfInputs, type);
	}
}
