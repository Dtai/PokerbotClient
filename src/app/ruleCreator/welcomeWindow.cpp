#include "welcomeWindow.hpp"
#include "ui_welcomeWindow.h"
#include "JSON/helloCreator.hpp"
#include <QNetworkReply>
#include <iostream>

WelcomeWindow::WelcomeWindow(QWidget *parent)
        : QWidget(parent),
		  ui(new Ui::WelcomeWindow)
{
		ui->setupUi(this);
		connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(sendInformation()));
}

WelcomeWindow::~WelcomeWindow()
{
        delete ui;
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
