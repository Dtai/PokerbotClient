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

#include "raiseactiongraphicsitem.hpp"
#include <ruleSystem/graphicsView/elementfactory.hpp>
#include <ruleSystem/graphicsView/elementlayout.hpp>
#include <ruleSystem/rule_defaults.hpp>

using namespace ruleSystem;
using namespace ruleSystem::graphicsView;

namespace poker
{
	namespace graphicsView
	{
		namespace
		{
			ElementFactory * factory() { return ElementFactory::Instance(); }
		}

		RaiseActionGraphicsItem::RaiseActionGraphicsItem(RaiseAction * action)
			: ActionGraphicsItem(action)
		{
			setAcceptDrops(true);
		}

		RaiseAction * RaiseActionGraphicsItem::raiseAction() const
		{
			return static_cast<RaiseAction*>(element());
		}

		void RaiseActionGraphicsItem::calculateLayout()
		{
			if(elementLayout() == 0)
				return;

			const ElementLayout & el = *elementLayout();

			// calculate the size of the label
			QSizeF labelSize = calculateLabelSize();
			QSizeF betSizeVal = calculateBetsizeVal();
			QSize connectorSize = inputLayout()->connector().size();

			// find the new width & height
			float height = labelSize.height() + 3*el.yMargin() + betSizeVal.height();
			float width = qMax(labelSize.width(), betSizeVal.width()) + 2*el.xMargin() + connectorSize.width();

			// the height should be bigger or the same as the attached elements
			if(inputItem() && height < inputItem()->boundingRect().height())
				height = inputItem()->boundingRect().height();

			// update the bounding rect & position where text should start
			setInnerRect(QRectF(0, -height/2.0f, width, height));
			setBoundingRect(innerRect().adjusted(-inputItem()->innerRect().width(), 0, 0, 0));

			float attachedCenter = (connectorSize.width() + width)/2.0f;

			// set the text position
			setLabelStart(QPointF(attachedCenter - labelSize.width()/2.0f, -height/2.0f + el.yMargin()));

			// set the input position
			ElementGraphicsItem * item = childAt(RaiseAction::BetSizePosition());
			item->setPos(attachedCenter -item->boundingRect().width()/2.0f -item->boundingRect().left(), height/2.0f - el.yMargin() - item->boundingRect().bottom());
		}

		QSizeF RaiseActionGraphicsItem::calculateBetsizeVal() const
		{
			ElementGraphicsItem * item = childAt(RaiseAction::BetSizePosition());
			return item->boundingRect().size();
		}
	}
}
