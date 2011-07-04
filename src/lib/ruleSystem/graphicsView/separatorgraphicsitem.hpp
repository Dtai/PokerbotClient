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

#ifndef SEPARATORGRAPHICSITEM_HPP
#define SEPARATORGRAPHICSITEM_HPP

#include <QGraphicsLineItem>
#include "util/macro.hpp"
#include <QPen>

namespace ruleSystem
{
	namespace graphicsView
	{
		class DnDController;

		class SeparatorGraphicsItem : public QGraphicsLineItem
		{
		public:
			SeparatorGraphicsItem();

			void setDnDController(DnDController * controller);

			virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

		protected:
			/* Drag and drop functionality */
			virtual void dragEnterEvent(QGraphicsSceneDragDropEvent * event);
			virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);
			virtual void dropEvent(QGraphicsSceneDragDropEvent * event);

			void setHoverStatus(bool isHovered);

		private:
			PtrVarGet(DnDController, dnDController);

			RefVarGetSet(QPen, normalPen, NormalPen);
			RefVarGetSet(QPen, selectedPen, SelectedPen);
			RefVarGet(bool, isHovered);
		};
	}
}

#endif // SEPARATORGRAPHICSITEM_HPP
