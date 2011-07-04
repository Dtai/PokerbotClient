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

#include "dndseparatorcontroller.hpp"
#include "functiongraphicsitem.hpp"
#include "function.hpp"
#include "elementhelper.hpp"


namespace ruleSystem
{
	namespace graphicsView
	{
		DnDSeparatorController::DnDSeparatorController(FunctionGraphicsItem * functionItem, int pos)
			: _functionItem(functionItem),
			_pos(pos)
		{
		}

		bool DnDSeparatorController::canStartDrag() const
		{
			return false;
		}

		bool DnDSeparatorController::acceptsDrag(const QMimeData * data)
		{
			Element * element = mimeDataToElement(data);
			Evaluatable * val = element_cast<Evaluatable>(element);

			if(val == 0)
				return Qt::IgnoreAction;

			return functionItem()->function()->checkInputType(pos(), val, 0);
		}

		Qt::DropAction DnDSeparatorController::onDrop(const QMimeData * data)
		{
			Evaluatable * val = element_cast<Evaluatable>(mimeDataToElement(data));

			if(val == 0)
				return Qt::IgnoreAction;

			// dirty check for placing in the same position
			if(val == functionItem()->function()->inputEvaluatables()[pos()])
				return Qt::IgnoreAction;


			bool sameTree = functionItem()->function()->hasElementTree(val);

			// try to perform the action
			bool succeeded;
			QString error;
			functionItem()->function()->insertInputElement(pos(), val, &succeeded, &error);

			// it failed, send out the error
			if(!succeeded)
			{
				emit errorMessage(error);
				return Qt::IgnoreAction;
			}

			// same tree means the update will come
			if(sameTree)
				functionItem()->createItemAt(pos());
			else
				functionItem()->elementChanged();

			return Qt::MoveAction;
		}

		void DnDSeparatorController::itemDropped(Qt::DropAction /*action*/)
		{
		}
	}
}
