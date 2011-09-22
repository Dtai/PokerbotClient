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

#include "predefinedelementmodel.hpp"
#include <QStringList>
#include <ruleSystem/graphicsView/elementgraphicsitem.hpp>
#include <ruleSystem/rule_defaults.hpp>

#include "../view/predefinedrulesdescriptor.hpp"

PredefinedElementModel::PredefinedElementModel(const QList<PredefinedElement> & elements, QObject * parent)
	: QAbstractListModel(parent)
	, _elements(elements)
{
}

PredefinedElementModel::~PredefinedElementModel()
{
	deleteAllElements();
}

void PredefinedElementModel::renewModel(const QList<PredefinedElement> & elements)
{
	beginResetModel();
	deleteAllElements();
	_elements = elements;
	endResetModel();
}

void PredefinedElementModel::deleteAllElements()
{
	for(int i =0 ;i < _elements.size(); i++)
	{
		delete _elements.at(i).predefinedElement;
		_elements[i].predefinedElement = 0;
	}

	_elements.clear();
}

int PredefinedElementModel::rowCount(const QModelIndex & /*parent*/) const
{
	return _elements.size();
}

QVariant PredefinedElementModel::data(const QModelIndex &index, int role) const
{
	switch(role)
	{
	case Qt::DisplayRole:
		return _elements.at(index.row()).name;
		break;

	case Qt::UserRole:
		return qVariantFromValue(static_cast<void*>(_elements.at(index.row()).predefinedElement));

	default:
		return QVariant();
	}
}

QVariant PredefinedElementModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
	return "name";
}

QStringList PredefinedElementModel::mimeTypes() const
{
	QStringList l;
	l << ruleSystem::defaults::elementGraphicsItem::mimeType();

	return l;
}

QMimeData * PredefinedElementModel::mimeData(const QModelIndexList & indexes) const
{
	if(indexes.size() == 0)
		return 0;

	int row = indexes.at(0).row();

	return ruleSystem::graphicsView::elementToMimeData(_elements.at(row).predefinedElement);
}

Qt::ItemFlags	PredefinedElementModel::flags(const QModelIndex & /*index*/) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void PredefinedElementModel::appendElement(const PredefinedElement & element)
{
	beginInsertRows(QModelIndex(), _elements.size(), _elements.size());
	_elements << element;
	endInsertRows();
}

void PredefinedElementModel::removeElement(int pos)
{
	beginRemoveRows(QModelIndex(), pos, pos);
	_elements.removeAt(pos);
	endRemoveRows();
}

Qt::DropActions PredefinedElementModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

bool PredefinedElementModel::dropMimeData(const QMimeData * data, Qt::DropAction /*action*/, int /*row*/, int /*column*/, const QModelIndex & /*parent*/)
{
	PredefinedRulesDescriptor d;
	if(d.exec() == QDialog::Rejected)
		return false;

	PredefinedElement e = d.element();
	e.predefinedElement = ruleSystem::graphicsView::mimeDataToElement(data);

	appendElement(e);
	return true;
}

bool PredefinedElementModel::removeRows(int row, int /*count*/, const QModelIndex & /*parent*/)
{
	if(row < 0 || row >= _elements.size())
		return false;

	removeElement(row);
	return true;
}
