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

#include "elementgraphicsitem.hpp"
#include "elementlayout.hpp"
#include "dndcontroller.hpp"
#include "elementitemdelegate.hpp"
#include "../element.hpp"
#include <QPainter>
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QApplication>
#include <QMenu>
#include "../rule_defaults.hpp"
#include "elementfactory.hpp"
#include "../serialization/qt/elementserializer.hpp"
#include <QGraphicsScene>

namespace ruleSystem
{
	namespace graphicsView
	{
		namespace
		{
			void drawElementToPixmapHelper(QGraphicsItem * item, QPainter * painter);

			ElementFactory * factory() { return ElementFactory::Instance(); }
		}


		ElementGraphicsItem::ElementListener::ElementListener(ElementGraphicsItem * item)
			: _elementItem(item)
		{
			if(_elementItem->element() != 0)
				_elementItem->element()->attachListener(this);

		}

		ElementGraphicsItem::ElementListener::~ElementListener()
		{
			if(_elementItem->element())
				_elementItem->element()->removeListener(this);
		}

		ruleSystem::Element * ElementGraphicsItem::detachElement()
		{
			Element * el = element();
			_element = 0;

			// remove the listener
			if(_listener)
			{
				el->removeListener(_listener);
				delete _listener;
				_listener = 0;
			}

			// do the same for all the children
			QMap<QString, ElementGraphicsItem*>::iterator i;
			for(i = _inputElementItems.begin(); i != _inputElementItems.end(); i++)
				i.value()->detachElement();

			return el;
		}

		void ElementGraphicsItem::ElementListener::onChildElementChanged(Element * /*parentElement*/)
		{
			_elementItem->elementChanged();
		}

		void ElementGraphicsItem::ElementListener::onElementDestroyed()
		{
			if(_elementItem)
			{
				ElementGraphicsItem * item = _elementItem;
				item->detachElement();
				delete item;
			}
		}

		ElementGraphicsItem::ElementGraphicsItem(ruleSystem::Element * element, const ElementLayout * layout)
			:_element(element),
			_elementLayout(layout),
			_options(ElementGraphicsItem::AllOptions),
			_delegate(0),
			_isHovered(false),
			_listener(0)
		{
			if(isEmpty())
				setAcceptDrops(true);
			else
				_listener = new ElementListener(this);
		}


		ElementGraphicsItem::~ElementGraphicsItem()
		{
			delete _listener;
			delete _delegate;
			delete _element;
		}

		void ElementGraphicsItem::createInputElement(const QString & inputPosition)
		{
			if(element() == 0)
				return;

			if(!element()->hasInputAt(inputPosition))
				return;

			Element * inputElement = element()->inputAt(inputPosition);
			ElementGraphicsItem * item = 0;

			if(inputElement == 0)
			{
				// find the type for the element
				bool val;
				ruleSystem::Type t = element()->inputType(inputPosition, val);
				if(!val)
					return;

				// create an element
				item = factory()->createGraphicsItem(t, Element::TypeID());
			}
			else
			{
				// create the element
				item = factory()->createGraphicsItem(inputElement);
			}

			if(item == 0)
				return;

			// attach this element
			item->setParentItem(this);
			item->_inputPositionAtParent = inputPosition;
			delete _inputElementItems[inputPosition];
			_inputElementItems[inputPosition] = item;
		}

		void ElementGraphicsItem::elementChanged()
		{
			// recreate all the children
			createAllChildren();

			onElementChanged();
			updateElementItem();
		}

		void ElementGraphicsItem::updateElementItem()
		{
			prepareGeometryChange();

			//recalculate the layout for all the children
			for(QMap<QString, ElementGraphicsItem*>::const_iterator i = _inputElementItems.begin(); i != _inputElementItems.end(); i++)
				if(i.value())
					i.value()->calculateLayout();

			calculateLayout();

			if(parent()) parent()->updateElementItem();
			update();
		}

		QRectF ElementGraphicsItem::boundingRect() const
		{
			return _boundingRect;
		}

		void ElementGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
		{
			if(elementLayout() == 0)
				return;

			const ElementLayout & el = *elementLayout();

			painter->save();

			// use the right brush & pen
			painter->setPen(isHovered() ? el.selectedStrokePen() : el.strokePen());
			painter->setBrush(isHovered() ? el.selectedBackgroundBrush() : el.backgroundBrush());

			// draw the shape
			painter->drawRoundedRect(_innerRect, el.roundness(), el.roundness());
			drawConnector(elementLayout(), QPointF(0,0), painter, isHovered());

			// draw the label
			if(delegate())
			{
				QTransform transform  = QTransform::fromTranslate(labelStart().x(), labelStart().y());
				painter->setTransform(transform, true);
				delegate()->paint(painter, element());
			}

			painter->restore();
		}

		ElementGraphicsItem * ElementGraphicsItem::parent() const
		{
			return dynamic_cast<ElementGraphicsItem*>(parentItem());
		}

		ElementGraphicsItem * ElementGraphicsItem::childAt(const QString & position) const
		{
			QMap<QString, ElementGraphicsItem*>::const_iterator i = _inputElementItems.find(position);
			return i == _inputElementItems.end() ? 0 : i .value();
		}


		void ElementGraphicsItem::setOption(OptionFlag optionFlag, bool isEnabled)
		{
			if(isEnabled)
				_options |= optionFlag;
			else
				_options &= ~optionFlag;
		}

		void ElementGraphicsItem::onElementChanged()
		{
		}

		void ElementGraphicsItem::calculateLayout()
		{
			if(elementLayout() == 0)
				return;

			const ElementLayout & el = *elementLayout();

			QSize connectorSize = el.connector().size();

			// calculate the size of the label
			QSizeF labelSize = calculateLabelSize();

			// find the new width & height
			float height = labelSize.height() + 2*el.yMargin();
			float width = labelSize.width() + 2*el.xMargin();

			if(width < el.minSize().width()) width = el.minSize().width();
			if(height < el.minSize().height()) height = el.minSize().height();

			// update the bounding rect & position where text should start
			setInnerRect(QRectF(-width, -height/2.0f, width, height));
			setLabelStart(QPointF(-labelSize.width() - el.xMargin(), -labelSize.height()/2.0f));
			setBoundingRect(innerRect().adjusted(0, 0, connectorSize.width(),0));
		}

		QSizeF ElementGraphicsItem::calculateLabelSize() const
		{
			if(delegate())
				return delegate()->sizeHint(element());
			else if(elementLayout())
				return elementLayout()->minSize();
			else
				return QSizeF();
		}


		void ElementGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
		{
			if(event->button() != Qt::RightButton || !event->buttons().testFlag(Qt::RightButton))
				return;

			if(!isEmpty() && options().testFlag(IsDeletable))
			{
				QMenu * m = new QMenu;
				QAction * delAction = m->addAction("Delete");

				if(m->exec(event->screenPos()) == delAction)
				{
					delete m;
					delete element();
				}
			}
		}

		void ElementGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
		{
			// we can drag if draggable and element is set
			if (!options().testFlag(IsDraggable) || isEmpty() || element() == 0)
				return;

			if(QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance())
				return;

			QPoint hotSpot = (event->pos()- boundingRect().topLeft()).toPoint();

			// create the drag
			QDrag * drag = new QDrag(event->widget());
			QMimeData *mime = elementToMimeData(this->element());
			setMimeDataHotSpot(mime, hotSpot);

			//Save the mime data of the element. This done via a clone so the variable mime can be safely deleted (this happens on Windows).
			QMimeData *mimeData = new QMimeData();
			for(int i=0; i<mime->formats().count(); ++i){
				mimeData->setData(mime->formats().at(i), mime->data(mime->formats().at(i)));
			}

			drag->setMimeData(mime);

			// create a picture for the drag
			drag->setPixmap(elementToPixmap(this));
			drag->setHotSpot(hotSpot);

			// we will remove this item for now, the rest will be done afterwards by the listeners
			QGraphicsScene * s = scene();
			QPointF op = this->pos();
			Element * e = element();
			Element * p = element()->parent();

			QString pos = inputPositionAtParent();
			delete e;

			Qt::DropAction a = drag->exec(Qt::CopyAction | Qt::MoveAction);
			// it was cancelled
			if(a != Qt::MoveAction)
			{
				e = mimeDataToElement(mimeData);

				// did we have a parent? so we should re-add the item
				if(p)
				{
					p->setInput(pos, e);
				}
				else
				{
					ElementGraphicsItem * it = factory()->createGraphicsItem(e);
					s->addItem(it);
					it->setPos(op);
				}
			}
		}

		void ElementGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * /*event*/)
		{
		}

		void ElementGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
		{
			if(!options().testFlag(IsEditable) || !delegate())
				return;

			if(delegate()->edit(element(), event->pos()))
				elementChanged();
		}

		bool ElementGraphicsItem::acceptsDragEnter(Element * element)
		{
			// we should be empty and have parent with a valid element
			if(!isEmpty() || parent() == 0 || parent()->element() == 0)
				return false;

			// our parent can accept this element at that position
			return parent()->element()->checkInputType(inputPositionAtParent(), element);
		}


		bool ElementGraphicsItem::onDropped(Element * element)
		{
			bool succeeded;

			// update the parent (copy the position because we can be deleted before the pos is used)
			QString pos = inputPositionAtParent();
			parent()->element()->setInput(pos, element, &succeeded);

			return succeeded;
		}

		void ElementGraphicsItem::dragEnterEvent(QGraphicsSceneDragDropEvent * event)
		{
			Element * element = mimeDataToElement(event->mimeData());

			if(acceptsDragEnter(element))
			{
				event->accept();
				_isHovered = true;
				update();
			}
			else
			{
				event->ignore();
			}

			delete element;
		}

		void ElementGraphicsItem::dragLeaveEvent(QGraphicsSceneDragDropEvent * event)
		{
			if(_isHovered)
			{
				_isHovered = false;
				update();
				event->ignore();
			}
		}

		void ElementGraphicsItem::dropEvent(QGraphicsSceneDragDropEvent * event)
		{
			Element * element = mimeDataToElement(event->mimeData());

			_isHovered = false;
			update();


			if(onDropped(element))
			{
				event->accept();
			}
			else
			{
				event->ignore();
			}
		}

		void ElementGraphicsItem::SetBoundingRect(ElementGraphicsItem * element, const QRectF & boundingRect)
		{
			if(element == 0)
				return;
			element->_boundingRect = boundingRect;
		}

		void ElementGraphicsItem::SetInnerRect(ElementGraphicsItem * element, const QRectF & innerRect)
		{
			if(element == 0)
				return;

			element->_innerRect = innerRect;
		}

		void ElementGraphicsItem::createAllChildren()
		{
			if(element() == 0)
				return;

			// start by removing all the children and detaching there element
			while(!_inputElementItems.isEmpty())
			{
				// detach and delete it
				_inputElementItems.begin().value()->detachElement();
				delete _inputElementItems.begin().value();

				// and clear the space
				_inputElementItems.erase(_inputElementItems.begin());
			}


			QList<QString> positions = element()->inputPositions();
			foreach(const QString & position, positions)
				createInputElement(position);
		}

		void drawConnector(const ElementLayout * layout, const QPointF & centerPosition, QPainter * painter, bool isHovered)
		{
			if(painter == 0 || layout == 0)
				return;

			painter->drawPixmap(
					centerPosition + layout->connectorLeftCenter(),
					isHovered ? layout->selectedConnector() : layout->connector(),
					QRect());
		}

		namespace
		{
			void drawElementToPixmapHelper(QGraphicsItem * item, QPainter * painter)
			{
				float xMove = item->pos().x();
				float yMove = item->pos().y();

				painter->setWorldTransform(QTransform::fromTranslate(xMove, yMove), true);
				item->paint(painter, 0, 0);

				foreach(QGraphicsItem * child, item->children())
					drawElementToPixmapHelper(child, painter);

				painter->setWorldTransform(QTransform::fromTranslate(-xMove, -yMove), true);
			}
		}

		QPixmap elementToPixmap(ruleSystem::graphicsView::ElementGraphicsItem * item, QPoint * hotSpot)
		{
                        QPixmap pixmap(item->boundingRect().size().toSize() + QSize(1, 1));
			pixmap.fill(QColor(0, 0, 0, 0));

			QPainter painter(&pixmap);
			painter.setWorldTransform(QTransform::fromTranslate(-item->pos().x()-item->boundingRect().left(), -item->boundingRect().top()-item->pos().y()), false);
                        drawElementToPixmapHelper(item, &painter);

			if(hotSpot)
				(*hotSpot) = -item->boundingRect().topLeft().toPoint();

			return pixmap;
		}

		QMimeData * elementToMimeData(Element * element)
		{
			if(!element)
				return 0;

			QMimeData * data = new QMimeData;

			QByteArray ar;
			QDataStream s(&ar, QIODevice::WriteOnly);
			s << element;

			data->setData(defaults::elementGraphicsItem::mimeType(), ar);

			return data;
		}

		void setMimeDataHotSpot(QMimeData * mimeData, const QPoint & hotSpot)
		{
			if(mimeData == 0)
				return;

			QByteArray ar;
			QDataStream s(&ar, QIODevice::WriteOnly);
			s << hotSpot;
			mimeData->setData(defaults::elementGraphicsItem::hotSpotMimeType(), ar);
		}

		Element * mimeDataToElement(const QMimeData * mimeData)
		{
			if(mimeData == 0)
				return 0;

			QByteArray ar = mimeData->data(defaults::elementGraphicsItem::mimeType());

			if(ar.isEmpty())
				return 0;
			QDataStream s(&ar, QIODevice::ReadOnly);
			Element * element = 0;
			s >> element;
			return element;
		}

		QPoint mimeDataHotSpot(const QMimeData * mimeData)
		{
			if(mimeData == 0)
				return QPoint();

			QByteArray ar = mimeData->data(defaults::elementGraphicsItem::hotSpotMimeType());

			if(ar.isEmpty())
				return QPoint();

			QDataStream s(&ar, QIODevice::ReadOnly);
			QPoint pos;
			s >> pos;

			return pos;
		}
	}
}
