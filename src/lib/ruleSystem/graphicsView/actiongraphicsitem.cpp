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

#include "actiongraphicsitem.hpp"
#include "elementlayout.hpp"
#include "action.hpp"
#include "elementfactory.hpp"
#include "evaluatable.hpp"
#include "dndactioncontroller.hpp"
#include "elementitemdelegate.hpp"
#include <QPainter>

namespace ruleSystem
{
	namespace graphicsView
	{
		namespace
		{
			ElementFactory * factory() { return ElementFactory::Instance(); }
		}


		ActionGraphicsItem::ActionGraphicsItem(Action * action)
			: ElementGraphicsItem(action, factory()->findLayout(action))
		{
			setAcceptDrops(true);
		}

		void ActionGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
		{
			if(elementLayout() == 0)
				return;

			const ElementLayout & el = *elementLayout();

			painter->save();

			// use the right brush & pen
			painter->setPen(isHovered() ? el.selectedStrokePen() : el.strokePen());
			painter->setBrush(isHovered() ? el.selectedBackgroundBrush() : el.backgroundBrush());

			// draw the shape
			painter->drawRoundedRect(innerRect(), el.roundness(), el.roundness());
			drawConnector(inputLayout(), QPointF(0,0), painter, isHovered());

			// draw the label
			if(delegate())
			{
				QTransform transform  = QTransform::fromTranslate(labelStart().x(), labelStart().y());
				painter->setTransform(transform, true);
				delegate()->paint(painter, element());
			}

			painter->restore();
		}

		void ActionGraphicsItem::calculateLayout()
		{
			if(elementLayout() == 0)
				return;

			const ElementLayout & el = *elementLayout();

			// calculate the size of the label
			QSizeF labelSize = calculateLabelSize();
			QSize connectorSize = inputLayout()->connector().size();

			// find the new width & height
			float height = labelSize.height() + 2*el.yMargin();
			float width = labelSize.width() + 2*el.xMargin() + connectorSize.width();

			if(width < el.minSize().width()) width = el.minSize().width();
			if(height < el.minSize().height()) height = el.minSize().height();

			// the height should be bigger or the same as the attached elements
			if(inputItem() && height < inputItem()->boundingRect().height())
				height = inputItem()->boundingRect().height();

			// update the bounding rect & position where text should start
			setInnerRect(QRectF(0, -height/2.0f, width, height));
			setLabelStart(QPointF(connectorSize.width() + el.xMargin(), -labelSize.height()/2.0f));
			setBoundingRect(innerRect().adjusted(-inputItem()->innerRect().width(), 0, 0, 0));
		}

		Action * ActionGraphicsItem::action() const
		{
			return static_cast<Action*>(element());
		}

		const ElementLayout * ActionGraphicsItem::inputLayout() const
		{
			if(action()->inputVal())
				return factory()->findLayout(action()->inputVal());
			else
				return factory()->findLayout(action()->inputType(), Element::TypeID());
		}

		ElementGraphicsItem * ActionGraphicsItem::inputItem() const
		{
			return childAt(Action::InputPosition());

		}

		bool ActionGraphicsItem::acceptsDragEnter(Element * element)
		{
			if(!action() || action()->inputVal())
				return ElementGraphicsItem::acceptsDragEnter(element);

			// if the action is empty, it is possible (we don't want overwriting)
			return action()->checkInputType(Action::InputPosition(), element);
		}

		bool ActionGraphicsItem::onDropped(Element * element)
		{
			if(!action() || action()->inputVal())
				return ElementGraphicsItem::onDropped(element);

			action()->setInput(Action::InputPosition(), element);
			return true;

		}
	}
}
