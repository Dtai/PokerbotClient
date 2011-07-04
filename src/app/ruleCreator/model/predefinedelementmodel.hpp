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


#ifndef PREDEFINEDELEMENTMODEL_HPP
#define PREDEFINEDELEMENTMODEL_HPP

#include <QAbstractListModel>
#include <ruleSystem/util/macro.hpp>

namespace ruleSystem {
class Element;
}

struct PredefinedElement
{
	PredefinedElement() : predefinedElement(0) {}

	QString name;
	QString description;
	ruleSystem::Element * predefinedElement;
};

class PredefinedElementModel : public QAbstractListModel
{
	Q_OBJECT
public:
	PredefinedElementModel(const QList<PredefinedElement> & elements = QList<PredefinedElement>(), QObject * parent = 0);
	virtual ~PredefinedElementModel();

	void renewModel(const QList<PredefinedElement> & elements);

	virtual int rowCount(const QModelIndex &parent) const;
	virtual QVariant data(const QModelIndex &index, int role) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	virtual QStringList mimeTypes() const;
	virtual QMimeData * mimeData(const QModelIndexList & indexes) const;
	virtual Qt::ItemFlags	flags(const QModelIndex & index) const;
	virtual Qt::DropActions supportedDropActions() const;
	virtual bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent);
	virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

	void appendElement(const PredefinedElement & element);
	void removeElement(int pos);

private:
	void deleteAllElements();

	RefVarGet(QList<PredefinedElement>, elements);

};

#endif // PREDEFINEDELEMENTMODEL_HPP
