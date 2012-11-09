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


#ifndef SETTINGSDIALOG_HPP
#define SETTINGSDIALOG_HPP

#include <QMainWindow>

#include "connectiontarget.hpp"
#include "network/helloSender.hpp"

class SettingsManager;
class QListWidgetItem;

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QMainWindow
{
	Q_OBJECT

public:
	explicit SettingsDialog(SettingsManager * manager, QWidget *parent1, QWidget *parent2 = 0);
	~SettingsDialog();

signals:
	void sendTableName(QString tabName, QString tableName);
	void removeTest();

private slots:
	void onDeleteConnection();
	void onItemSelectionChanged();

	void onConnectionChanged();
	void onNewConnection();
	void onCancelClicked();
	void onOKClicked();

	void incorrectData();
	void correctData(ConnectionTarget target, QString testTable);

private:
	Ui::SettingsDialog *ui;
	QListWidgetItem * _curSelected;
	SettingsManager * _settingsManager;
	QWidget *parent1;
	QVector<HelloSender*> *hellos;

	void checkForDeletion(QString senderName);
};

#endif // SETTINGSDIALOG_HPP
