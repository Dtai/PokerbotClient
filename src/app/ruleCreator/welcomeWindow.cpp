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

	ui->statusbar->showMessage(tr("Welcome"));

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
	ui->statusbar->showMessage(tr("Sending data"));
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
	ui->statusbar->showMessage(tr("Successfully connected"));
	HelloSender::add(target);

	_settingsManager->addConnection(target);
	_settingsManager->writeSettings();

	connect(this, SIGNAL(sendTableName(QString, QString, bool)), parent1, SLOT(addTab(QString, QString, bool)));
	emit sendTableName(target.playerName, target.tableName, false);
	close();
}

void WelcomeWindow::incorrectData(){
	ui->statusbar->showMessage(tr("An error occured"));
	close();
}

void WelcomeWindow::closeEvent(QCloseEvent *event) {
	event->accept();
}
