/*******************************************************************
* Copyright (c) 2010 Thomas Fannes (thomasfannes@gmail.com)
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

#include "elementgraphicsscene.hpp"
#include "elementgraphicsitem.hpp"
#include "elementfactory.hpp"
#include "../action.hpp"

#include <QGraphicsSceneDragDropEvent>

namespace ruleSystem
{
namespace graphicsView
{
namespace
{
ElementFactory * factory() { return ElementFactory::Instance(); }

}

ElementGraphicsScene::ElementGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{

}

void ElementGraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent * event)
{
	Element * element = mimeDataToElement(event->mimeData());
	if(element == 0)
	{
		QGraphicsScene::dragEnterEvent(event);
		return;
	}

	delete element;
	event->accept();
}

void ElementGraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent * event)
{
	//QGraphicsScene::dragMoveEvent(event);

	// we only accept if there is no one under the current position or it is the same element
	ElementGraphicsItem * item = qgraphicsitem_cast<ElementGraphicsItem*>(itemAt(event->scenePos()));

	if(item == 0)
		event->accept();
	else
		QGraphicsScene::dragMoveEvent(event);

	//event->accept();
}

void ElementGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent * event)
{
	if(itemAt(event->scenePos()) != 0)
	{
		QGraphicsScene::dropEvent(event);
		return;
	}

	Element * element = mimeDataToElement(event->mimeData());
	if(element == 0)
	{
		QGraphicsScene::dropEvent(event);
		return;
	}

	// accept the event
	event->accept();

	// and create a new item for this element
	ElementGraphicsItem * item = factory()->createGraphicsItem(element);
	addItem(item);
	QPoint pos = mimeDataHotSpot(event->mimeData());
	item->setPos(event->scenePos() - pos - item->boundingRect().center());
}

bool ElementGraphicsScene::isCorrect(QString * errorMessage) const
{
	return getCorrectAction(errorMessage) != 0;
}

bool ElementGraphicsScene::isEmpty() const
{
	return items().size() == 0;
}

Action * ElementGraphicsScene::getCorrectAction(QString * errorMessage) const
{
	QList<QGraphicsItem *> allItems = items();
	Action * topLevelAction = 0;
	bool oneFound = false;


	foreach(QGraphicsItem * item, allItems)
	{
		if(item->parentItem() == 0)
		{
			ElementGraphicsItem * it = qgraphicsitem_cast<ElementGraphicsItem*>(item);
			if(it != 0)
			{
				if(it->element() == 0)
				{
					ErrorMsg(errorMessage, tr("This rule contains a top-level element that is empty"));
					return 0;
				}

				if((topLevelAction = element_cast<Action>(it->element())) == 0)
				{
					ErrorMsg(errorMessage, tr("This rule contains a top-level element that is not an action"));
					return 0;
				}

				if(oneFound)
				{
					ErrorMsg(errorMessage, tr("This rule contains multiple actions"));
					return 0;
				}

				oneFound = true;
			}
		}
	}

	if(topLevelAction == 0)
	{
		ErrorMsg(errorMessage, tr("This rule contains no top-level action"));
		return 0;
	}

	if(!topLevelAction->isCorrect(errorMessage))
		return 0;

	return topLevelAction;
}
}
}
