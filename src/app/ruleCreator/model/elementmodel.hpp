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

#ifndef ELEMENTMODEL_HPP
#define ELEMENTMODEL_HPP

#include <QAbstractTableModel>
#include <ruleSystem/element.hpp>

class ElementModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	class ElementDescriber
	{
	public:
		virtual QString headers(int column) const = 0;
		virtual QString data(ruleSystem::Element * element, int column) const = 0;
		virtual int numberOfColumns() const = 0;
	};

	ElementModel(ElementModel::ElementDescriber * describer, const QList<ruleSystem::Element*> & elements, QObject * parent = 0);
	~ElementModel();

	void renewModel(const QList<ruleSystem::Element*> & elements);

	/* abstract item functions */
	virtual Qt::ItemFlags flags(const QModelIndex & index) const;
	virtual QStringList mimeTypes() const;
	virtual QMimeData * mimeData(const QModelIndexList & indexes) const;
	virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
	virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

private:
	ElementDescriber * _describer;
	QList<ruleSystem::Element*> _elements;
};

class FeatureDescriber : public ElementModel::ElementDescriber
{
public:
	virtual QString headers(int column) const;
	virtual QString data(ruleSystem::Element * element, int column) const;
	virtual int numberOfColumns() const;
};

class FunctionDescriber : public ElementModel::ElementDescriber
{
public:
	virtual QString headers(int column) const;
	virtual QString data(ruleSystem::Element * element, int column) const;
	virtual int numberOfColumns() const;
};

class ActionDescriber : public ElementModel::ElementDescriber
{
public:
	virtual QString headers(int column) const;
	virtual QString data(ruleSystem::Element * element, int column) const;
	virtual int numberOfColumns() const;
};

class ConstantDescriber : public ElementModel::ElementDescriber
{
public:
	virtual QString headers(int column) const;
	virtual QString data(ruleSystem::Element * element, int column) const;
	virtual int numberOfColumns() const;
};

#endif // ELEMENTMODEL_HPP
