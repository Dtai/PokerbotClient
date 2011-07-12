#include <QNetworkReply>
#include <QLineEdit>

#include "welcomeWindow.hpp"
#include "ui_welcomeWindow.h"
#include "connectiontarget.hpp"
#include "settingsmanager.hpp"

#include "network/helloSender.hpp"

WelcomeWindow::WelcomeWindow(SettingsManager *manager, QWidget *parent)
        : QWidget(parent),
		  ui(new Ui::WelcomeWindow),
		  _settingsManager(manager)
{
	statusBar = new QStatusBar(this);
	statusBar->setGeometry(0, this->heightMM(), 100, 20);

	statusBar->setSizeGripEnabled(false);
	statusBar->showMessage("Welcome");
	qApp->processEvents();

	ui->setupUi(this);
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(onOKClicked()));
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
	connect(hs, SIGNAL(finished()), this, SLOT(deleteLater()));
	statusBar->showMessage("Sending data");
}

void WelcomeWindow::onCancelClicked(){
	deleteLater();
}
