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

#include "settingsdialog.hpp"
#include "ui_settingsdialog.h"
#include "settingsmanager.hpp"
#include "JSON/helloCreator.hpp"
#include "network/helloSender.hpp"

#include <QListWidgetItem>
#include <QListWidget>
#include <QKeyEvent>

SettingsDialog::SettingsDialog(SettingsManager * manager, QWidget *parent1, QWidget *parent2)
	: QMainWindow(parent2),
		ui(new Ui::SettingsDialog),
		_curSelected(0),
		_settingsManager(manager)
{
	Q_ASSERT(manager);
	ui->setupUi(this);

	foreach(const ConnectionTarget & d, _settingsManager->connections())
	{
		QListWidgetItem * i = new QListWidgetItem(d.format());
		i->setData(Qt::UserRole, QVariant::fromValue<ConnectionTarget>(d));
		ui->connectionsWidget->addItem(i);
	}

	connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(onDeleteConnection()));
	connect(ui->connectionsWidget, SIGNAL(activated(QModelIndex)), this, SLOT(onItemSelectionChanged()));
	connect(ui->newButton, SIGNAL(clicked()), this, SLOT(onNewConnection()));
	connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onOKClicked()));
	connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));

	connect(ui->playerName, SIGNAL(textChanged(QString)), this, SLOT(onConnectionChanged()));
	connect(ui->tableName, SIGNAL(textChanged(QString)), this, SLOT(onConnectionChanged()));

	connect(ui->emptyRuleSetExporter, SIGNAL(stateChanged(int)), this, SLOT(onConnectionChanged()));	

	this->parent1 = parent1;
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::onDeleteConnection()
{
	QListWidgetItem * i = _curSelected;
	ui->connectionsWidget->removeItemWidget(i);
	delete i;
	_curSelected = 0;

	ui->playerName->setText("");
	ui->tableName->setText("");
	ui->emptyRuleSetExporter->setCheckState(Qt::Unchecked);
}

void SettingsDialog::onNewConnection()
{
	if(_curSelected != 0)
	{
		_curSelected = 0;
		ui->playerName->setText("");
		ui->tableName->setText("");
		ui->emptyRuleSetExporter->setCheckState(Qt::Unchecked);

		onNewConnection();
		return;
	}

	// add the new connection
	ConnectionTarget d;

	d.playerName = ui->playerName->text();
	d.tableName = ui->tableName->text();
	d.emptyRuleSetExporter = (ui->emptyRuleSetExporter->checkState() == Qt::Checked);

	_curSelected = new QListWidgetItem(d.format());
	_curSelected->setData(Qt::UserRole, QVariant::fromValue<ConnectionTarget>(d));
	ui->connectionsWidget->addItem(_curSelected);

	// and select this item
	ui->connectionsWidget->setCurrentItem(_curSelected);
}

void SettingsDialog::onItemSelectionChanged()
{
	_curSelected = ui->connectionsWidget->currentItem();
	ui->deleteButton->setEnabled(_curSelected != 0);

	ConnectionTarget d;

	// update the connection detail
	if(_curSelected)
		d = _curSelected->data(Qt::UserRole).value<ConnectionTarget>();

	// update the fields
	ui->playerName->setText(d.playerName);
	ui->tableName->setText(d.tableName);
	ui->emptyRuleSetExporter->setCheckState(d.emptyRuleSetExporter ? Qt::Checked : Qt::Unchecked);
}

void SettingsDialog::onConnectionChanged()
{
	if(!_curSelected)
		return;

	ConnectionTarget d = _curSelected->data(Qt::UserRole).value<ConnectionTarget>();
	d.playerName = ui->playerName->text();
	d.tableName = ui->tableName->text();
	d.emptyRuleSetExporter = ui->emptyRuleSetExporter->checkState() == Qt::Checked;

	_curSelected->setData(Qt::UserRole, QVariant::fromValue<ConnectionTarget>(d));
	_curSelected->setText(d.format());
}

void SettingsDialog::onCancelClicked()
{
	deleteLater();
}

void SettingsDialog::onOKClicked()
{

	ui->statusbar->showMessage("Sending data");
	// write the settings
	while(_settingsManager->connections().size() != 0)
		_settingsManager->removeConnection(0);

	for(int i = 0; i < ui->connectionsWidget->count(); i++)
		_settingsManager->addConnection(ui->connectionsWidget->item(i)->data(Qt::UserRole).value<ConnectionTarget>());

	_settingsManager->writeSettings();

	QVector<HelloSender*> *hellos = new QVector<HelloSender*>();
	QVector<QString> *tables = new QVector<QString>();

	for(int i=0; i<_settingsManager->connections().size(); ++i){
		hellos->push_back(new HelloSender(_settingsManager->connections().at(i)));
		tables->push_back(ui->tableName->text());

		if(hellos->last()->alreadySent(_settingsManager->connections().at(i))){
			hellos->last()->send();

		}
		connect(hellos->last(), SIGNAL(finished()), this, SLOT(correctData()));
		connect(hellos->last(), SIGNAL(errored()), this, SLOT(incorrectData()));
	}

	if(hellos->isEmpty()){
		deleteLater();
	}
}

void SettingsDialog::incorrectData(){
	QObject *o = this->sender();


	//Hier de helloSender uit de vector verwijderen.
	//Hier de naam van de tafel uit de vector verwijderen.
	deleteLater();
}

void SettingsDialog::correctData(){
	QObject *o = this->sender();

	connect(this, SIGNAL(sendTableName(QString)), parent1, SLOT(addTab(QString)));
//	emit sendTableName(ui->leTableName->text());
	//Hier de helloSender uit de vector verwijderen
	//Hier de naam van de  tafel doorsturen naar parent1
	//Hier de naam van de tafel uit de vector verwijderen
	deleteLater();
}
