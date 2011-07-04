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

#include "dndifthenelsecontroller.hpp"
#include "ifthenelsegraphicsitem.hpp"
#include "ifthenelserule.hpp"
#include "action.hpp"
#include "evaluatable.hpp"
#include "elementhelper.hpp"

namespace ruleSystem
{
	namespace graphicsView
	{
		DnDIfThenElseController::DnDIfThenElseController(IfThenElseGraphicsItem * item, bool isEmpty)
			: _item(item),
			_isEmpty(isEmpty)
		{
		}

		bool DnDIfThenElseController::canStartDrag() const
		{
			return !isEmpty();
		}

		bool DnDIfThenElseController::acceptsDrag(const QMimeData * data)
		{
			if(!isEmpty())
				return false;

			Element * element = mimeDataToElement(data);
			return checkElement(element);
		}

		Qt::DropAction DnDIfThenElseController::onDrop(const QMimeData * data)
		{
			Element * element = mimeDataToElement(data);
			return droppedElement(element);
		}

		void DnDIfThenElseController::itemDropped(Qt::DropAction /*action*/)
		{
			item()->elementChanged();
		}

		DnDEvaluatableIfThenElseController::DnDEvaluatableIfThenElseController(IfThenElseGraphicsItem * item, bool isEmpty)
			: DnDIfThenElseController(item, isEmpty)
		{
		}

		bool DnDEvaluatableIfThenElseController::checkElement(Element * element)
		{
			Evaluatable * val = element_cast<Evaluatable>(element);

			if(val == 0)
				return false;

			return element->type() == type::booleanType();
		}

		Qt::DropAction DnDEvaluatableIfThenElseController::droppedElement(Element * element)
		{
			Evaluatable * val = element_cast<Evaluatable>(element);

			if(val == 0)
				return Qt::IgnoreAction;

			// try to perform the action
			bool succeeded;
			QString error;
			item()->ifThenElseRule()->setInputVal(val, &succeeded, &error);

			// it failed, send out the error
			if(!succeeded)
			{
				emit errorMessage(error);
				return Qt::IgnoreAction;
			}

			// same tree means the update will come
			item()->elementChanged();

			return Qt::MoveAction;
		}

		DnDActionIfThenElseController::DnDActionIfThenElseController(IfThenElseGraphicsItem * item, bool isEmpty, bool trueAction)
			:DnDIfThenElseController(item, isEmpty),
			_trueAction(trueAction)
		{
		}

		bool DnDActionIfThenElseController::checkElement(Element * element)
		{
			Action * ac = element_cast<Action>(element);

			return ac != 0;
		}

		Qt::DropAction DnDActionIfThenElseController::droppedElement(Element * element)
		{
			Action * ac = element_cast<Action>(element);

			if(ac == 0)
				return Qt::IgnoreAction;

			// try to perform the action
			bool succeeded;
			QString error;

			if(_trueAction)
				item()->ifThenElseRule()->setTrueAction(ac, &succeeded, &error);
			else
				item()->ifThenElseRule()->setFalseAction(ac, &succeeded, &error);

			// it failed, send out the error
			if(!succeeded)
			{
				emit errorMessage(error);
				return Qt::IgnoreAction;
			}

			// same tree means the update will come
			item()->elementChanged();

			return Qt::MoveAction;
		}

	}
}
