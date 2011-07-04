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

#include "ifthenelsegraphicsitem.hpp"
#include "ifthenelserule.hpp"
#include "elementfactory.hpp"
#include "elementlayout.hpp"
#include "rule_defaults.hpp"
#include "action.hpp"
#include "evaluatable.hpp"
#include "dndifthenelsecontroller.hpp"
#include <QFontMetricsF>
#include <QPainter>

namespace ruleSystem
{
	namespace graphicsView
	{
		namespace
		{
			ElementFactory * factory() { return ElementFactory::Instance(); }

			const QString strIF = "als: ";
			const QString strTRUE = "waar: ";
			const QString strFALSE = "onwaar: ";
		}

		IfThenElseGraphicsItem::IfThenElseGraphicsItem(IfThenElseRule * rule)
			: ElementGraphicsItem(rule, factory()->findLayout(rule)),
			_inputItem(0),
			_trueItem(0),
			_falseItem(0)
		{
		}

		IfThenElseRule * IfThenElseGraphicsItem::ifThenElseRule() const
		{
			return static_cast<IfThenElseRule*>(element());
		}

		void IfThenElseGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
		{
			if(elementLayout() == 0) return;
			const ElementLayout & el = *elementLayout();

			painter->save();

			// use the right brush & pen
			painter->setPen(isHovered() ? el.selectedStrokePen() : el.strokePen());
			painter->setBrush(isHovered() ? el.selectedBackgroundBrush() : el.backgroundBrush());

			// draw the shape
			painter->drawRoundedRect(innerRect(), el.roundness(), el.roundness());

			// draw the text
			painter->setFont(el.font());
			painter->setPen(el.textPen());

			painter->drawText(_ifPoint, strIF);
			painter->drawText(_truePoint, strTRUE);
			painter->drawText(_falsePoint, strFALSE);

			painter->restore();
		}

		void IfThenElseGraphicsItem::calculateLayout()
		{
			if(elementLayout() == 0)
				return;

			const ElementLayout & el = *elementLayout();
			QFontMetricsF f(el.font());

			// find all the necessary information
			float wA = f.width(strIF);
			float wB = inputItem()->boundingRect().width();
			float wC1 = f.width(strTRUE);
			float wC2 = f.width(strFALSE);
			float wC = qMax(wC1, wC2);
			float wD = qMax(trueItem()->boundingRect().width(), falseItem()->boundingRect().width());
			float wT = wA + wB + wC + wD + el.xMargin()*4;

			float hB = inputItem()->boundingRect().height();
			float hD = trueItem()->boundingRect().height() + el.inputItemSpacing() + falseItem()->boundingRect().height();
			float hT = qMax(hB, hD) + el.yMargin()*2;

			// set the positions
			// the if point
			float xPos = el.xMargin();
			_ifPoint = QPointF(xPos, 0);

			// the input
			xPos += wA;
			inputItem()->setPos(xPos + inputItem()->innerRect().width(), 0);

			// the right block
			xPos += wB + 2*el.xMargin() + wC;
			float yUpC = -hD/2.0f + trueItem()->boundingRect().height()/2.0f;
			float yDownC = hD/2.0f - falseItem()->boundingRect().height()/2.0f;

			_truePoint = QPointF(xPos - wC1, yUpC);
			_falsePoint = QPointF(xPos - wC2, yDownC);

			xPos += wD;
			trueItem()->setPos(xPos - trueItem()->boundingRect().right(), yUpC);
			falseItem()->setPos(xPos - falseItem()->boundingRect().right(), yDownC);


			setInnerRect(QRectF(0, -hT/2.0f, wT, hT));
			setLabelStart(QPointF());
			setBoundingRect(innerRect());
		}

		void IfThenElseGraphicsItem::onElementChanged()
		{
			createInputItem();
			createTrueItem();
			createFalseItem();
		}

		void IfThenElseGraphicsItem::createInputItem()
		{
			// remove the inputElement
			delete _inputItem;

			Evaluatable * val = ifThenElseRule()->inputVal();

			if(val)
				_inputItem = factory()->createGraphicsItem(val);
			else
				_inputItem = factory()->createGraphicsItem(type::booleanType(), Category_Action);

			_inputItem->setAcceptDrops(true);
			_inputItem->setParentItem(this);
			_inputItem->setDnDController(new DnDEvaluatableIfThenElseController(this, val == 0));
		}

		void IfThenElseGraphicsItem::createTrueItem()
		{
			// remove the inputElement
			delete _trueItem;

			Action * act = ifThenElseRule()->trueAction();

			if(act)
				_trueItem = factory()->createGraphicsItem(act);
			else
				_trueItem = factory()->createGraphicsItem(type::voidType(), Category_Undefined);

			_trueItem->setAcceptDrops(true);
			_trueItem->setParentItem(this);
			_trueItem->setDnDController(new DnDActionIfThenElseController(this, act == 0, true));
		}

		void IfThenElseGraphicsItem::createFalseItem()
		{
			// remove the inputElement
			delete _falseItem;

			Action * act = ifThenElseRule()->falseAction();

			if(act)
				_falseItem = factory()->createGraphicsItem(act);
			else
				_falseItem = factory()->createGraphicsItem(type::voidType(), Category_Undefined);

			_falseItem->setParentItem(this);
			_falseItem->setAcceptDrops(true);
			_falseItem->setDnDController(new DnDActionIfThenElseController(this, act == 0, false));
		}
	}
}
