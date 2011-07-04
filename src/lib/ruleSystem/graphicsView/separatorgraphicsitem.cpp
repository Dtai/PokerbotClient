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

#include <QGraphicsSceneDragDropEvent>
#include "separatorgraphicsitem.hpp"
#include "dndcontroller.hpp"
#include "rule_defaults.hpp"

#include <QDebug>
#include <QPainter>


namespace ruleSystem
{
	namespace graphicsView
	{
		SeparatorGraphicsItem::SeparatorGraphicsItem()
			: QGraphicsLineItem(),
			_dnDController(0),
			_normalPen(QBrush(Qt::black), defaults::separatorGraphicsItem::separatorWidth()),
			_selectedPen(QBrush(Qt::white), defaults::separatorGraphicsItem::separatorWidth()),
			_isHovered(false)
		{
		}

		void SeparatorGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
		{
			painter->setPen((isHovered() ? selectedPen() : normalPen()));
			painter->drawLine(line());
		}

		void SeparatorGraphicsItem::setHoverStatus(bool isHovered)
		{
			if(isHovered == _isHovered)
					return;

			_isHovered = isHovered;
			setPen(_isHovered ? selectedPen() : normalPen());
		}

		void SeparatorGraphicsItem::setDnDController(DnDController * controller)
		{
			if(controller == dnDController())
				return;

			delete _dnDController;
			_dnDController = controller;
		}

		void SeparatorGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent * event)
		{
			if(!dnDController() || !dnDController()->acceptsDrag(event->mimeData()))
				return;

			// accept the event
			event->accept();

			setHoverStatus(true);
		}

		void SeparatorGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent * /*event*/)
		{
			setHoverStatus(false);
		}

		void SeparatorGraphicsItem::dropEvent(QGraphicsSceneDragDropEvent * event)
		{
			if(!dnDController())
				return;

			setHoverStatus(false);

			Qt::DropAction a = dnDController()->onDrop(event->mimeData());
			event->setDropAction(a);
			event->accept();
		}
	}
}
