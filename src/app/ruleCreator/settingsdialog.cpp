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

SettingsDialog::SettingsDialog(SettingsManager * manager, QWidget *parent)
	: QWidget(parent),
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
	// write the settings
	while(_settingsManager->connections().size() != 0)
		_settingsManager->removeConnection(0);

	for(int i = 0; i < ui->connectionsWidget->count(); i++)
		_settingsManager->addConnection(ui->connectionsWidget->item(i)->data(Qt::UserRole).value<ConnectionTarget>());

	_settingsManager->writeSettings();

	HelloSender *hs;
	bool sending = false;

	for(int i=0; i<_settingsManager->connections().size(); ++i){
		hs = new HelloSender(_settingsManager->connections().at(i));
		if(!hs->alreadySent(_settingsManager->connections().at(i))){
			hs->send();
			sending = true;
		}
	}

	// and close this widget
	if(sending){
		connect(hs, SIGNAL(finished()), this, SLOT(deleteLater()));
	} else {
		deleteLater();
	}


}
