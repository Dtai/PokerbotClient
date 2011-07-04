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

#include "predefinedelementview.hpp"
#include <ruleSystem/element.hpp>
#include <ruleSystem/graphicsView/elementgraphicsitem.hpp>
#include <ruleSystem/graphicsView/elementfactory.hpp>

#include <QDrag>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>

using namespace ruleSystem;
using namespace ruleSystem::graphicsView;

PredefinedElementView::PredefinedElementView(QWidget *parent) :
    QListView(parent)
{
	setDragEnabled(true);
	setAcceptDrops(true);
}

void PredefinedElementView::startDrag(Qt::DropActions supportedActions)
{
	// get the item at this position
	QMimeData * mimeData = model()->mimeData(selectedIndexes());
	if(mimeData == 0)
		return;

	// this should contains an element
	Element * element = mimeDataToElement(mimeData);
	if(element == 0)
		return QListView::startDrag(supportedActions);

	// create the pixmap
	ElementGraphicsItem * item = ElementFactory::Instance()->createGraphicsItem(element);
	QPoint hotSpot;
	QPixmap p = elementToPixmap(item, &hotSpot);
	delete item;

	// start the drag
	QDrag * d = new QDrag(this);
	d->setMimeData(mimeData);
	d->setPixmap(p);
	d->setHotSpot(QPoint(p.size().width()/2, p.size().height()/2));

	d->exec(supportedActions);
}

void PredefinedElementView::mousePressEvent(QMouseEvent * event)
{
	QModelIndex i = indexAt(event->pos());

	if(i.isValid() && event->button() == Qt::RightButton)
	{
		// create a popup menu to delete this item
		QMenu * m = new QMenu;
		QAction * delAction = m->addAction("Delete");

		if(m->exec(event->globalPos()) == delAction)
			if(QMessageBox::warning(0, tr("Verwijderen van element"), tr("Bent u zeker dat u dit element uit de lijst wilt verwijderen?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
					model()->removeRow(i.row());

		return;
	}

	QListView::mousePressEvent(event);
}



