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

#include "dndactioncontroller.hpp"
#include "evaluatable.hpp"
#include "graphicsView/actiongraphicsitem.hpp"
#include "action.hpp"
#include "elementhelper.hpp"

namespace ruleSystem
{
	namespace graphicsView
	{
		DnDActionController::DnDActionController(ActionGraphicsItem * actionItem, bool isEmpty)
			: _actionItem(actionItem),
			_isEmpty(isEmpty)
		{
		}

		bool DnDActionController::canStartDrag() const
		{
			return !isEmpty();
		}

		bool DnDActionController::acceptsDrag(const QMimeData * data)
		{
			if(!isEmpty())
				return false;

			Element * element = mimeDataToElement(data);
			Evaluatable * val = element_cast<Evaluatable>(element);

			if(val == 0)
				return false;

			return actionItem()->action()->canHaveInputElement(val);
		}

		Qt::DropAction DnDActionController::onDrop(const QMimeData * data)
		{
			Element * element = mimeDataToElement(data);
			Evaluatable * val = element_cast<Evaluatable>(element);

			if(val == 0)
				return Qt::IgnoreAction;

			// try to perform the action
			bool succeeded;
			QString error;
			actionItem()->action()->setInputElement(val, &succeeded, &error);

			// it failed, send out the error
			if(!succeeded)
			{
				emit errorMessage(error);
				return Qt::IgnoreAction;
			}

			// same tree means the update will come
			actionItem()->elementChanged();

			return Qt::MoveAction;
		}

		void DnDActionController::itemDropped(Qt::DropAction /*action*/)
		{
			actionItem()->elementChanged();
		}
	}
}
