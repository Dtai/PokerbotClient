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

#include "action.hpp"
#include "evaluatable.hpp"

namespace ruleSystem
{
    TYPEID_INHERIT_SOURCE("Action", Element, Action)

	const QString Action::InputPosition()
	{
		return QString("input_Action");
	}

	Action::Action(const QString & name, const Type & inputType)
		: Element(type::voidType(), name),
		_canHaveAllTypes(inputType == type::unknownType()),
		_inputType(inputType)
	{
		setInput(InputPosition(), 0);
	}

	bool Action::isCorrect(QString * errorMessage) const
	{
		CleanErrorMsg(errorMessage);

		Evaluatable * val = inputVal();

		if(val == 0)
		{
			ErrorMsg(errorMessage, tr("This action has no input"));
			return false;
		}

		return val->isCorrect(errorMessage);
	}

	const Type & Action::inputType() const
	{
		if(inputVal())
			return inputVal()->type();
		else
			return _inputType;
	}

	Type Action::inputType(const QString & inputPosition, bool & isValid) const
	{
		isValid = false;

		if(inputPosition != InputPosition())
			return Type();

		isValid = true;
		return inputType();
	}

	QList<QString> Action::requiredInputs() const
	{
		return QList<QString>() << Action::InputPosition();
	}

	Evaluatable * Action::inputVal() const
	{
		return element_cast<Evaluatable>(inputAt(InputPosition()));
	}
}
