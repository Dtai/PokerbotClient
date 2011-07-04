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

#include "dndfunctioncontroller.hpp"
#include "elementgraphicsitem.hpp"
#include "functiongraphicsitem.hpp"
#include "elementhelper.hpp"
#include "function.hpp"

namespace ruleSystem
{
	namespace graphicsView
	{
		DnDFunctionController::DnDFunctionController(FunctionGraphicsItem * functionItem, int pos, bool isEmpty, bool canOverwrite)
			: _functionItem(functionItem),
			_pos(pos),
			_isEmpty(isEmpty),
			_canOverwrite(canOverwrite)
		{
		}

		bool DnDFunctionController::canStartDrag() const
		{
			return !isEmpty();
		}
		bool DnDFunctionController::acceptsDrag(const QMimeData * data)
		{
			if(!isEmpty() && !canOverwrite())
				return false;

			Element * element = mimeDataToElement(data);
			Evaluatable * val = element_cast<Evaluatable>(element);

			if(val == 0)
				return false;

			return functionItem()->function()->checkInputType(pos(), val, 0);


		}
		Qt::DropAction DnDFunctionController::onDrop(const QMimeData * data)
		{
			Element * element = mimeDataToElement(data);
			Evaluatable * val = element_cast<Evaluatable>(element);

			if(val == 0)
				return Qt::IgnoreAction;

			bool sameTree = functionItem()->function()->hasElementTree(val);

			// try to perform the action
			bool succeeded;
			QString error;
			functionItem()->function()->setInputElement(pos(), val, &succeeded, &error);

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

		void DnDFunctionController::itemDropped(Qt::DropAction /*action*/)
		{
			functionItem()->elementChanged();
		}
	}
}
