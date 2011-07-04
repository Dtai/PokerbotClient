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

#include "editnumericaldialog.hpp"
#include "ui_editconstantdialog.h"
#include <QDoubleValidator>
#include <QCompleter>
#include <QLineEdit>

namespace poker
{
	namespace view
	{
		QList<float> EditNumericalDialog::_AllValues = QList<float>();

		EditNumericalDialog::EditNumericalDialog(float value)
			:QDialog(),
			ui(new Ui::EditConstantDialog)
		{
			ui->setupUi(this);
			ui->waardeBox->setEditable(true);
			ui->waardeBox->setValidator(new QDoubleValidator(this));
			ui->waardeBox->setDuplicatesEnabled(false);
			ui->waardeBox->setInsertPolicy(QComboBox::InsertAlphabetically);
			ui->waardeBox->setCompleter(new QCompleter(ui->waardeBox->model(), this));

			fillWaardeBox();

			connect(this, SIGNAL(accepted()), this, SLOT(updateWaarde()));

			setValue(value);

			ui->waardeBox->model()->sort(0);
		}

		void EditNumericalDialog::setValue(float value)
		{
			QString val = QString("%1").arg(value);

			_value = value;

			if(!_AllValues.contains(value))
			{
				_AllValues << value;
				ui->waardeBox->addItem(val);
			}


			ui->waardeBox->lineEdit()->setText(val);
			ui->waardeBox->lineEdit()->selectAll();
		}

		void EditNumericalDialog::updateWaarde()
		{
			float value = ui->waardeBox->currentText().toFloat();
			_AllValues << value;

			_value = value;
		}

		EditNumericalDialog::~EditNumericalDialog()
		{
			delete ui;
		}

		void EditNumericalDialog::fillWaardeBox()
		{
			foreach(float val, _AllValues)
				ui->waardeBox->addItem(QString("%1").arg(val));
		}
	}
}
