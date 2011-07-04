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

#ifndef DNDIFTHENELSECONTROLLER_HPP
#define DNDIFTHENELSECONTROLLER_HPP

#include "dndcontroller.hpp"
#include "util/macro.hpp"

namespace ruleSystem
{
	namespace graphicsView
	{
		class IfThenElseGraphicsItem;

		class DnDIfThenElseController : public DnDController
		{
		public:
			DnDIfThenElseController(IfThenElseGraphicsItem * item, bool isEmpty);

			virtual bool canStartDrag() const;
			virtual bool acceptsDrag(const QMimeData * data);
			virtual Qt::DropAction onDrop(const QMimeData * data);
			virtual void itemDropped(Qt::DropAction action);

		protected:
			virtual bool checkElement(Element * element) = 0;
			virtual Qt::DropAction droppedElement(Element * element) = 0;

			PtrVarGetSet(IfThenElseGraphicsItem, item, Item);
			SimpleVarGetSet(bool, isEmpty, IsEmpty);
		};

		class DnDEvaluatableIfThenElseController : public DnDIfThenElseController
		{
		public:
			DnDEvaluatableIfThenElseController(IfThenElseGraphicsItem * item, bool isEmpty);

		protected:
			virtual bool checkElement(Element * element);
			virtual Qt::DropAction droppedElement(Element * element);
		};

		class DnDActionIfThenElseController : public DnDIfThenElseController
		{
		public:
			DnDActionIfThenElseController(IfThenElseGraphicsItem * item, bool isEmpty, bool trueAction);

		protected:
			virtual bool checkElement(Element * element);
			virtual Qt::DropAction droppedElement(Element * element);

		private:
			bool _trueAction;
		};

	}
}

#endif // DNDIFTHENELSECONTROLLER_HPP
