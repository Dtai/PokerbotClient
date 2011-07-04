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

#include "constant.hpp"

namespace ruleSystem
{

	Constant::Constant(const Type & type, const QVariant & value)
		: Evaluatable(type, "")
	{
		setValue(value);
	}

	bool Constant::isCorrect(QString * errorMessage) const
	{
		if(_value.isNull() || !_value.isValid())
		{
			ErrorMsg(errorMessage, tr("The constant has no valid value"));
			return false;
		}

		return true;
	}

	QVariant Constant::calculateValue()
	{
		return _value;
	}

	Constant * Constant::clone() const
	{
		Constant * f = new Constant(type(), name());
		f->setValue(_value);

		return f;
	}

	void Constant::setValue(const QVariant & value)
	{
		if(!type().checkVariant(value))
			_value = QVariant();
		else
			_value = value;

		if(value.isNull() || !value.isValid())
			setName("invalid");
		else if(value.canConvert(QVariant::String))
			setName(value.toString());
		else
			setName("object");
	}

	Type Constant::inputType(const QString & /*inputPosition*/, bool & isValid) const
	{
		isValid = false;
		return Type();
	}
}
