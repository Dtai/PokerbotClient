#include <QNetworkReply>
#include <QLineEdit>
#include <iostream>

#include "welcomeWindow.hpp"
#include "ui_welcomeWindow.h"
#include "connectiontarget.hpp"
#include "settingsmanager.hpp"

#include "network/helloSender.hpp"

WelcomeWindow::WelcomeWindow(SettingsManager *manager, QWidget *parent1, QWidget *parent2)
		: QMainWindow(parent2),
		  ui(new Ui::WelcomeWindow),
		  _settingsManager(manager)
{
	ui->setupUi(this);
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(onOKClicked()));
	this->parent1 = parent1;

	ui->statusbar->showMessage("Welcome");
}

WelcomeWindow::~WelcomeWindow()
{
	delete ui;
}

void WelcomeWindow::onOKClicked(){
	while(_settingsManager->connections().size() != 0)
		_settingsManager->removeConnection(0);

	ConnectionTarget ct;
	ct.playerName = ui->lePlayerName->text();
	ct.tableName = ui->leTableName->text();
	_settingsManager->addConnection(ct);

	_settingsManager->writeSettings();

	HelloSender *hs = new HelloSender(ct);
	hs->send();
	connect(hs, SIGNAL(finished()), this, SLOT(correctData()));
	connect(hs, SIGNAL(errored()), this, SLOT(incorrectData()));
	ui->statusbar->showMessage("Sending data");
}

void WelcomeWindow::correctData(){
	connect(this, SIGNAL(sendTableName(QString)), parent1, SLOT(addTab(QString)));
	emit sendTableName(ui->leTableName->text());
	deleteLater();
}

void WelcomeWindow::incorrectData(){
	deleteLater();
}
