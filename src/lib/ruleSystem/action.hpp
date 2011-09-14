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

#ifndef ACTION_HPP
#define ACTION_HPP

#include "type.hpp"
#include "element.hpp"

namespace ruleSystem
{
	class Evaluatable;

	class Action : public Element
	{
	public:
                TYPEID_INHERIT_HEADER("Action", Element)

		static const QString InputPosition();

		Action(const QString & name, const Type & inputType = type::unknownType());

		/* abstract functions to implement in base class */
		virtual void execute() = 0;
		virtual Action * clone() const = 0;

		/* implemented abstract functions */
		virtual bool isCorrect(QString * errorMessage = 0) const;
		virtual Type inputType(const QString & inputPosition, bool & isValid) const;
		virtual QList<QString> requiredInputs() const;

		Evaluatable * inputVal() const;
		const Type & inputType() const;
	private:
		SimpleVarGet(bool, canHaveAllTypes);
		Type _inputType;
	};
}

#endif // ACTION_HPP
