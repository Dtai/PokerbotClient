#include "welcomeWindow.hpp"
#include "ui_welcomeWindow.h"
#include "settingsmanager.hpp"

#include "network/helloSender.hpp"

WelcomeWindow::WelcomeWindow(SettingsManager *manager, QWidget *parent1, QWidget *parent2)
		: QMainWindow(parent2),
		  ui(new Ui::WelcomeWindow),
		  _settingsManager(manager)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(onOKClicked()));
	this->parent1 = parent1;

	ui->statusbar->showMessage("Welcome");

	while(_settingsManager->connections().size() != 0)
		_settingsManager->removeConnection(0);
	_settingsManager->writeSettings();
}

WelcomeWindow::~WelcomeWindow()
{
	delete ui;
}

void WelcomeWindow::onOKClicked(){
	ui->statusbar->showMessage("Sending data");
	ConnectionTarget ct;
	ct.playerName = ui->lePlayerName->text();
	ct.tableName = ui->leTableName->text();

	HelloSender *hs = new HelloSender(ct);
	HelloSender::setCounter(1);
	HelloSender::initConnected();
	connect(hs, SIGNAL(connected(ConnectionTarget, QString)), this, SLOT(correctData(ConnectionTarget, QString)));
	connect(hs, SIGNAL(errored()), this, SLOT(incorrectData()));
	hs->send();
}

void WelcomeWindow::correctData(ConnectionTarget target, QString testTable){
	ui->statusbar->showMessage("Successfully connected");
	ConnectionTarget testTarget;
	testTarget.playerName = target.playerName;
	testTarget.tableName = testTable;
	HelloSender::add(target);
	HelloSender::add(testTarget);

	_settingsManager->addConnection(target);
	_settingsManager->addConnection(testTarget);
	_settingsManager->writeSettings();

	connect(this, SIGNAL(sendTableName(QString)), parent1, SLOT(addTab(QString)));
	emit sendTableName(ui->leTableName->text());
	emit sendTableName(testTable);
	close();
}

void WelcomeWindow::incorrectData(){
	ui->statusbar->showMessage("An error occured");
	close();
}
