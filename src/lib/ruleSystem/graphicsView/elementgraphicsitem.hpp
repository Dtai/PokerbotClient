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

#ifndef FORMULAGRAPHICSITEM_HPP
#define FORMULAGRAPHICSITEM_HPP

#include <QGraphicsItem>
#include "../element.hpp"
#include "../util/macro.hpp"
#include "../ielementlistener.hpp"

class QMimeData;

namespace ruleSystem
{
	namespace graphicsView
	{
		class ElementLayout;
		class DnDController;
		class ElementItemDelegate;

		class ElementGraphicsItem : public QGraphicsItem
		{
			class ElementListener : public IElementListener
			{
			public:
				ElementListener(ElementGraphicsItem * item);
				~ElementListener();

				virtual void onChildElementChanged(Element * parentElement);
				virtual void onElementDestroyed();

			private:
				ElementGraphicsItem * _elementItem;
			};


			friend class ElementLayout;

		public:
			enum { Type = UserType + 1 };

			/* Options enum */
			enum OptionFlag
			{
				NoOptions = 0x00,
				IsEditable = 0x01,
				IsDeletable = 0x02,
				IsDraggable = 0x04,
				AllOptions = 0xff
			};
			Q_DECLARE_FLAGS(Options, OptionFlag)


			/* Constructor & destructor */
			ElementGraphicsItem(ruleSystem::Element * element, const ElementLayout * layout);
			~ElementGraphicsItem();
			ruleSystem::Element * detachElement();

			/* update state functions */
			void createInputElement(const QString & inputPosition);
			void elementChanged();
			void updateElementItem();

			/* Overloaded members from QGraphicsItem */
			virtual QRectF boundingRect() const;
			virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
			virtual int type() const { return Type; }

			/* Parent / child function */
			ElementGraphicsItem * parent() const;
			ElementGraphicsItem * childAt(const QString & position) const;

			/* flag functions */
			void setOption(OptionFlag optionFlag, bool isEnabled);
			bool isEmpty() const { return !element(); }

		protected:
			QSizeF calculateLabelSize() const;

			/* start drag functionality */
			void mousePressEvent(QGraphicsSceneMouseEvent *event);
			void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
			void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
			void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

			/* Drag and drop functionality */
			virtual bool acceptsDragEnter(Element * element);
			virtual bool onDropped(Element * element);
			virtual void dragEnterEvent(QGraphicsSceneDragDropEvent * event);
			virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);
			virtual void dropEvent(QGraphicsSceneDragDropEvent * event);

			bool isHovered() const { return _isHovered; }
			void setBoundingRect(const QRectF & boundingRect) { _boundingRect = boundingRect; }

			static void SetBoundingRect(ElementGraphicsItem * element, const QRectF & boundingRect);
			static void SetInnerRect(ElementGraphicsItem * element, const QRectF & innerRect);

		private:
			void createAllChildren();
			virtual void onElementChanged();
			virtual void calculateLayout();

			PtrVarGet(Element, element);
			PtrVarGetSet(const ElementLayout, elementLayout, ElementLayout);
			RefVarGetSet(Options, options, Options);
			PtrVarGetSet(const ElementItemDelegate, delegate, Delegate);
			RefVarGetProtectedSet(QRectF, innerRect, InnerRect);
			RefVarGetProtectedSet(QPointF, labelStart, LabelStart);
			RefVarGet(QString, inputPositionAtParent);

			QRectF _boundingRect;
			bool _isHovered;
			QMap<QString, ElementGraphicsItem*> _inputElementItems;
			ElementListener * _listener;
		};

		QPixmap elementToPixmap(ElementGraphicsItem * item, QPoint * hotSpot = 0);
		QMimeData * elementToMimeData(ruleSystem::Element * element);
		Element * mimeDataToElement(const QMimeData * mimeData);
		void setMimeDataHotSpot(QMimeData * mimeData, const QPoint & hotSpot);
		QPoint mimeDataHotSpot(const QMimeData * mimeData);
		void drawConnector(const ElementLayout * layout, const QPointF & centerPosition, QPainter * painter, bool isHovered);
	}
}

Q_DECLARE_OPERATORS_FOR_FLAGS(ruleSystem::graphicsView::ElementGraphicsItem::Options)

#endif // FORMULAGRAPHICSITEM_HPP
