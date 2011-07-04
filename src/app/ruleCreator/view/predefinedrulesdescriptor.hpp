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


#ifndef PREDEFINEDRULESDESCRIPTOR_HPP
#define PREDEFINEDRULESDESCRIPTOR_HPP

#include <QDialog>
#include <ruleSystem/util/macro.hpp>
#include "../model/predefinedelementmodel.hpp"

namespace Ui {
class PredefinedRulesDescriptor;
}

class PredefinedRulesDescriptor : public QDialog
{
	Q_OBJECT

public:
	explicit PredefinedRulesDescriptor(QWidget *parent = 0);
	~PredefinedRulesDescriptor();

	void setElement(const PredefinedElement & element);

private slots:
	void updateButtonStates(const QString & str);
	void nameChanged(const QString & str);
	void descriptionChanged(const QString & str);

private:
	RefVarGet(PredefinedElement, element);

	Ui::PredefinedRulesDescriptor *ui;
};

#endif // PREDEFINEDRULESDESCRIPTOR_HPP
