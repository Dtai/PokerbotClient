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

#include "elementmodel.hpp"
#include <QStringList>
#include <ruleSystem/rule_defaults.hpp>
#include <ruleSystem/graphicsView/elementgraphicsitem.hpp>
#include <ruleSystem/feature.hpp>
#include <ruleSystem/action.hpp>
#include <ruleSystem/constant.hpp>
#include <ruleSystem/function.hpp>
#include <ruleSystem/util/translator.hpp>

using namespace ruleSystem;

namespace
{
	QString translateInputs(const Function::InputList & inputList)
	{
		QStringList lst;

		foreach(const Function::InputList::Element & el, inputList.inputElements())
			lst << QString("%1: %2%3").arg(Translator::TranslationFor(el.type().typeName())).arg(el.minNumberOfInputs()).arg(el.minNumberOfInputs() != el.numberOfInputs() ? "+" : "" );

		return lst.join("; ");
	}
}

ElementModel::ElementModel(ElementModel::ElementDescriber * describer, const QList<ruleSystem::Element*> & elements, QObject * parent)
	: QAbstractTableModel(parent),
	_describer(describer)
{
	renewModel(elements);
}

ElementModel::~ElementModel()
{
        delete _describer;
	qDeleteAll(_elements);
}

void ElementModel::renewModel(const QList<ruleSystem::Element*> & elements)
{
	beginResetModel();
	qDeleteAll(_elements);
	_elements = elements;
	endResetModel();
}

Qt::ItemFlags ElementModel::flags(const QModelIndex & index) const
{
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
}

QStringList ElementModel::mimeTypes() const
{
	QStringList l;
	l << ruleSystem::defaults::elementGraphicsItem::mimeType();

	return l;
}

QMimeData * ElementModel::mimeData(const QModelIndexList & indexes) const
{
	if(indexes.size() == 0)
		return 0;

	int row = indexes.at(0).row();

	return ruleSystem::graphicsView::elementToMimeData(_elements.at(row));
}

QVariant ElementModel::data(const QModelIndex & index, int role) const
{
	switch(role)

	{
	case Qt::DisplayRole:
            //return _elements.at(index.row())->name();
            return _describer->data(_elements.at(index.row()), index.column());
            break;

	case Qt::ToolTipRole:
		return _elements.at(index.row())->description();
		break;

	default:
		return QVariant();
	}
}

QVariant ElementModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(orientation != Qt::Horizontal || role != Qt::DisplayRole)
		return QVariant();

	return _describer->headers(section);
}

int ElementModel::rowCount(const QModelIndex & /*parent*/) const
{
	return _elements.size();
}

int ElementModel::columnCount(const QModelIndex & /*parent*/) const
{
	return _describer->numberOfColumns();
}

bool ElementModel::setData(const QModelIndex & /*index*/, const QVariant & /*value*/, int /*role*/)
{
	return false;
}

QString UniversalDescriber::headers(int column) const {
	switch(column) {
		case 0:
			return ElementModel::tr("name");
		case 1:
			return ElementModel::tr("type");
		default:
			return QString();
	}
}

QString UniversalDescriber::data(ruleSystem::Element *element, int column) const {
	if(column == 0){
		return Translator::TranslationFor(element->name());
	} else if (column == 1){
		return Translator::TranslationFor(element->type().typeName());
	}
	return QString();
}

int UniversalDescriber::numberOfColumns() const{
	return 2;
}

QString FeatureDescriber::headers(int column) const
{
	switch(column)
	{
	case 0:
		return ElementModel::tr("name");

	case 1:
		return ElementModel::tr("type");

	default:
		return QString();
	}
}

QString FeatureDescriber::data(ruleSystem::Element * element, int column) const
{
	Feature * f = element_cast<Feature>(element);
	if(f == 0)
		return QString();

	switch(column)
	{
	case 0:
		return Translator::TranslationFor(f->name());

	case 1:
		return Translator::TranslationFor(f->type().typeName());

	default:
		return QString();
	}
}

int FeatureDescriber::numberOfColumns() const
{
	return 2;
}


QString FunctionDescriber::headers(int column) const
{
	switch(column)
	{
	case 0:
		return ElementModel::tr("name");

	case 1:
		return ElementModel::tr("output type");

	case 2:
		return ElementModel::tr("input types");

	default:
		return QString();
	}
}

QString FunctionDescriber::data(ruleSystem::Element * element, int column) const
{
	Function * f = element_cast<Function>(element);
	if(f == 0)
		return QString();

	switch(column)
	{
	case 0:
		return Translator::TranslationFor(f->name());

	case 1:
		return Translator::TranslationFor(f->type().typeName());

	case 2:
		return translateInputs(f->inputList());

	default:
		return QString();
	}
}

int FunctionDescriber::numberOfColumns() const
{
	return 3;
}

QString ActionDescriber::headers(int column) const
{
	switch(column)
	{
	case 0:
		return ElementModel::tr("name");

	default:
		return QString();
	}
}

QString ActionDescriber::data(ruleSystem::Element * element, int column) const
{
	Action * a = element_cast<Action>(element);
	if(a == 0)
		return QString();

	switch(column)
	{
	case 0:
		return a->name();

	default:
		return QString();
	}
}

int ActionDescriber::numberOfColumns() const
{
	return 1;
}

QString ConstantDescriber::headers(int column) const
{
	switch(column)
	{
	case 0:
		return ElementModel::tr("name");

	case 1:
		return ElementModel::tr("output type");

	case 2:
		return ElementModel::tr("default value");

	default:
		return QString();
	}
}

QString ConstantDescriber::data(ruleSystem::Element * element, int column) const
{
	Constant * c = element_cast<Constant>(element);
	if(c == 0)
		return QString();

	switch(column)
	{
	case 0:
		return Translator::TranslationFor(c->name());

	case 1:
		return Translator::TranslationFor(c->type().typeName());

	case 2:
		return Translator::TranslationFor(c->value().toString());

	default:
		return QString();
	}
}

int ConstantDescriber::numberOfColumns() const
{
	return 3;
}


