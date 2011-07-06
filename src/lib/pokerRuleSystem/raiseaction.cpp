/*******************************************************************
* Copyright (c) 2010 Thomas Fannes (thomasfannes@gmail.com)
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

#include "raiseaction.hpp"
#include "types.hpp"

#include <ruleSystem/evaluatable.hpp>
#include "ruleSystem/util/translator.hpp"

using namespace ruleSystem;

namespace poker
{
        TYPEID_INHERIT_SOURCE("RaiseAction", PokerAction, RaiseAction)

	RaiseAction::RaiseAction()
		: PokerAction(Translator::AddTranslation("raise", Translator::tr("raise")))
	{
	}

	const QString RaiseAction::BetSizePosition()
	{
		return "RaiseAction_BetSize";
	}

	Evaluatable * RaiseAction::inputBetSize() const
	{
		return element_cast<Evaluatable>(inputAt(BetSizePosition()));
	}

	RaiseAction * RaiseAction::clone() const
	{
		RaiseAction * a = new RaiseAction;
		a->setInput(Action::InputPosition(), inputVal()->clone());
		a->setInput(RaiseAction::BetSizePosition(), inputBetSize()->clone());

		return a;
	}

	QList<QString> RaiseAction::requiredInputs() const
	{
		return PokerAction::requiredInputs() << RaiseAction::BetSizePosition();
	}

	Type RaiseAction::inputType(const QString & inputPosition, bool & isValid) const
	{
		if(inputPosition == BetSizePosition())
		{
			isValid = true;
			return type::numericalType();
		}

		return PokerAction::inputType(inputPosition, isValid);
	}

}
