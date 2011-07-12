#include "welcomeWindow.hpp"
#include "ui_welcomeWindow.h"
#include "JSON/helloCreator.hpp"
#include <QNetworkReply>
#include <iostream>
#include "connectiontarget.hpp"

WelcomeWindow::WelcomeWindow(QWidget *parent)
        : QWidget(parent),
		  ui(new Ui::WelcomeWindow)
{
		ui->setupUi(this);
		connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(saveAndSend()));
}

WelcomeWindow::~WelcomeWindow()
{
        delete ui;
}

void WelcomeWindow::saveAndSend(){
	saveInformation();
	sendInformation();
}

void WelcomeWindow::saveInformation(){
	// add the new connection
	ConnectionTarget d;
	d.ipAddress = ui->address->text();
	d.portNumber = 20000;
	d.playerName = ui->lePlayerName->text();
	d.tableName = ui->leTableName->text();
	d.emptyRuleSetExporter = (ui->emptyRuleSetExporter->checkState() == Qt::Checked);

	_curSelected = new QListWidgetItem(d.format());
	_curSelected->setData(Qt::UserRole, QVariant::fromValue<ConnectionTarget>(d));
	ui->connectionsWidget->addItem(_curSelected);

	// and select this item
	ui->connectionsWidget->setCurrentItem(_curSelected);
}

void WelcomeWindow::sendInformation(){
	QString playerName = ui->lePlayerName->text();
	QString tableName = ui->leTableName->text();

	HelloCreator hc;
	hc.setPlayerName(playerName);
	hc.setTableName(tableName);

	QByteArray data;
	data.append(hc.toJSONString());

	QNetworkAccessManager * m = new QNetworkAccessManager(this);
	QNetworkRequest request;
	request.setUrl(QUrl("http://posttestserver.com/post.php"));
	request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
	QNetworkReply *reply;

	//connect(reply, SIGNAL(readyRead()), this, SLOT(close()));
	//reply = m->post(request, data);

	std::cout << hc.toJSONString().toStdString() << std::endl;

	close();
}
