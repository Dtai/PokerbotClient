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

#include "functiongraphicsitem.hpp"
#include "elementfactory.hpp"
#include "elementlayout.hpp"
#include "../rule_defaults.hpp"

namespace ruleSystem
{
	namespace graphicsView
	{
		namespace
		{
			ElementFactory * factory() { return ElementFactory::Instance(); }
		}

		FunctionGraphicsItem::FunctionGraphicsItem(Function * function)
			: ElementGraphicsItem(function, factory()->findLayout(function))
		{
			setAcceptDrops(true);
		}

		FunctionGraphicsItem::~FunctionGraphicsItem()
		{
		}

		Function * FunctionGraphicsItem::function() const
		{
			return static_cast<Function*>(element());
		}

		void FunctionGraphicsItem::calculateLayout()
		{
			if(elementLayout() == 0)
				return;

			const ElementLayout & el = *elementLayout();

			QSizeF childrenSize(0,0);
			QSize connectorSize = el.connector().size();

			qreal minLeftPos = 0;

			QList<QString> inputPositions = function()->functionInputPositions();
			foreach(const QString & inputPos, inputPositions)
			{
				ElementGraphicsItem * child = childAt(inputPos);
				if(child == 0)
					continue;

				QSizeF size = child->boundingRect().size();

				// find the inner size of this element
				childrenSize.rwidth() = qMax(childrenSize.width(), size.width());
				childrenSize.rheight() += size.height();
				minLeftPos = qMin(minLeftPos, child->boundingRect().left());
			}

			// add the spacing except with the last element
			childrenSize.rheight() += (el.inputItemSpacing()*(function()->numberOfInputs() - 1));

			// calculate the size of the text
			QSizeF labelSize = calculateLabelSize();

			// find the new width & height
			float height = qMax(labelSize.height(), childrenSize.height()) + 2*el.yMargin();
			float width = labelSize.width() + 2*el.xMargin();
			if(childrenSize.width() != 0)
				width += el.xMargin() + childrenSize.width() + connectorSize.width();

			if(width < el.minSize().width()) width = el.minSize().width();
			if(height < el.minSize().height()) height = el.minSize().height();

			// update the bounding rect & position where text should start
			setInnerRect(QRectF(-width, -height/2.0f, width, height));
			setLabelStart(QPointF(-labelSize.width() - el.xMargin(), -labelSize.height()/2.0f));
			setBoundingRect(innerRect().adjusted(0, 0, connectorSize.width(),0));

			// update all the children position
			float xPos = -labelSize.width() - 2*el.xMargin() - connectorSize.width();
			float yStart = -height/2.0f + el.yMargin();
			float curHeight = 0;

			QPointF curLockPoint(xPos, yStart);

			foreach(const QString & inputPos, inputPositions)
			{
				// find half the height of this element
				ElementGraphicsItem * child = childAt(inputPos);
				if(child == 0)
					continue;

				// set the position to half this height + half previous height
				float height_2 = child->innerRect().height()/2.0f;
				curLockPoint.ry() += (curHeight + height_2);

				// update the lock point
				child->setPos(curLockPoint);

				// update bounding & innerr rect (to extend to the left)
				QRectF b = child->boundingRect();
				QRectF i = child->innerRect();
				b.setLeft(minLeftPos);
				i.setLeft(minLeftPos);
				SetBoundingRect(child, b);
				SetInnerRect(child, i);

				// add this half for the next run + the spacing in between
				curHeight = height_2 + el.inputItemSpacing();
			}
		}

		bool FunctionGraphicsItem::acceptsDragEnter(Element * element)
		{
			if(!function())
				return ElementGraphicsItem::acceptsDragEnter(element);

			return function()->checkInputType("append", element);
		}

		bool FunctionGraphicsItem::onDropped(Element * element)
		{
			if(!function())
				return ElementGraphicsItem::onDropped(element);

			function()->setInput("append", element);
			return true;

		}
	}
}
