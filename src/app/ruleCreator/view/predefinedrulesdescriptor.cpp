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


#include "predefinedrulesdescriptor.hpp"
#include "ui_predefinedrulesdescriptor.h"
#include <QPushButton>
#include <QDebug>

PredefinedRulesDescriptor::PredefinedRulesDescriptor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PredefinedRulesDescriptor)
{
    ui->setupUi(this);

		connect(ui->name, SIGNAL(textChanged(QString)), this, SLOT(updateButtonStates(QString)));
		connect(ui->name, SIGNAL(textEdited(QString)), this, SLOT(nameChanged(QString)));
		connect(ui->description, SIGNAL(textEdited(QString)), this, SLOT(descriptionChanged(QString)));

		setElement(PredefinedElement());
}

PredefinedRulesDescriptor::~PredefinedRulesDescriptor()
{
    delete ui;
}

void PredefinedRulesDescriptor::updateButtonStates(const QString & str)
{
	ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!str.isEmpty());
}

void PredefinedRulesDescriptor::nameChanged(const QString & str)
{
	_element.name = str;
}

void PredefinedRulesDescriptor::descriptionChanged(const QString & str)
{
	_element.description = str;
}

void PredefinedRulesDescriptor::setElement(const PredefinedElement & element)
{
	_element = element;

	ui->name->setText(element.name);
	ui->description->setText(element.description);

	updateButtonStates(element.name);
}
