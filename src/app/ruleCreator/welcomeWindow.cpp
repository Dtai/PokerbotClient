#include "welcomeWindow.hpp"
#include "ui_welcomeWindow.h"
#include "settingsmanager.hpp"

#include "network/helloSender.hpp"

#include <QCloseEvent>
#include <QFileInfo>
#include <QHelpEngineCore>

WelcomeWindow::WelcomeWindow(SettingsManager *manager, QWidget *parent1, QWidget *parent2)
		: QMainWindow(parent2),
		  ui(new Ui::WelcomeWindow),
		  _settingsManager(manager)
{
	ui->setupUi(this);
	ui->help->setVisible(false);
	setAttribute(Qt::WA_DeleteOnClose);
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(onOKClicked()));
	connect(ui->btnHelp, SIGNAL(clicked()), this, SLOT(showHelp()));
	this->parent1 = parent1;

	ui->statusbar->showMessage("Welcome");

	while(_settingsManager->connections().size() != 0)
		_settingsManager->removeConnection(0);
	_settingsManager->writeSettings();

	OKClicked = false;
}

WelcomeWindow::~WelcomeWindow()
{
	delete ui;
}

void WelcomeWindow::showHelp(){
	if(ui->help->isVisible()){
		ui->help->hide();
		resize(265, height());
	} else {
		ui->help->show();
		resize(400, height());

		QFileInfo fileInfo("doc.qhc");
		QHelpEngineCore helpEngine(fileInfo.absoluteFilePath());
		QMap<QString, QUrl> links = helpEngine.linksForIdentifier("welcomeWindow");

		if (!links.isEmpty()) {
			QByteArray helpData = helpEngine.fileData(links.constBegin().value());
			if (!helpData.isEmpty()){
				ui->help->setText(helpData);
			}
		}
	}
}

void WelcomeWindow::onOKClicked(){
	OKClicked = true;
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

	connect(this, SIGNAL(sendTableName(QString, QString)), parent1, SLOT(addTab(QString, QString)));
	emit sendTableName(target.format(), target.tableName);
	emit sendTableName(testTarget.format(), testTarget.tableName);
	close();
}

void WelcomeWindow::incorrectData(){
	connect(this, SIGNAL(sendTableName(QString, QString)), parent1, SLOT(addRuleTab(QString)));
	emit sendTableName("Test", "Test");
	ui->statusbar->showMessage("An error occured");
	close();
}

void WelcomeWindow::closeEvent(QCloseEvent *event) {
	if(!OKClicked){
		connect(this, SIGNAL(sendTableName(QString, QString)), parent1, SLOT(addRuleTab(QString)));
		emit sendTableName("Test", "Test");
	}
	event->accept();
}
