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

#include "elementview.hpp"
#include <ruleSystem/graphicsView/elementgraphicsitem.hpp>
#include <ruleSystem/graphicsView/elementfactory.hpp>
#include <QDrag>

using namespace ruleSystem;
using namespace ruleSystem::graphicsView;

ElementView::ElementView(QWidget * parent)
	: QTreeView(parent)
{
	setItemsExpandable(false);
	setRootIsDecorated(false);
	setDragEnabled(true);
}

void ElementView::startDrag(Qt::DropActions supportedActions)
{
	// get the item at this position
	QMimeData * mimeData = model()->mimeData(selectedIndexes());
	if(mimeData == 0)
		return;

	// this should contains an element
	Element * element = mimeDataToElement(mimeData);
	if(element == 0)
		return QTreeView::startDrag(supportedActions);

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

void ElementView::dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	QTreeView::dataChanged(topLeft, bottomRight);
	rescaleAllColumns();
}

void ElementView::setModel(QAbstractItemModel *model)
{
	QTreeView::setModel(model);
	rescaleAllColumns();
}

void ElementView::rescaleAllColumns()
{
	for(int i = 0; i < model()->columnCount(); i++)
		resizeColumnToContents(i);
}
