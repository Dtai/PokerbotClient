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

#include "helloSender.hpp"

#include <QMessageBox>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include "qjson/src/json_parser.hh"
#include "config/reader.hpp"

HelloSender::HelloSender(const ConnectionTarget & target, QObject * parent)
  : QObject(parent),
	 _target(target)
{}

void HelloSender::setCounter(int newCounter){
	counter = newCounter;
}

void HelloSender::initConnected(){
	good = new QStringList();
	bad = new QStringList();
	error = new QStringList();
}

QUrl HelloSender::getURL(){
	Reader r;
	connect(&r, SIGNAL(noConfigFile()), this, SLOT(showNoConfigFile()));
	connect(&r, SIGNAL(wrongConfigFile()), this, SLOT(showWrongConfigFile()));
	return r.getHelloURL();
}

void HelloSender::showNoConfigFile(){
	QMessageBox *qmb = new QMessageBox(QMessageBox::Critical, "Error", "Can't open config file");
	qmb->show();
	emit errored();
}

void HelloSender::showWrongConfigFile(){
	QMessageBox *qmb = new QMessageBox(QMessageBox::Critical, "Error", "Can't parse config file");
	qmb->show();
	emit errored();
}

void HelloSender::send(){
	QNetworkAccessManager *m = new QNetworkAccessManager(this);

	QNetworkRequest request(getURL());
	if(request.url().toString() == "/"){
		emit errored();
		return;
	}

	request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

	QByteArray data;
	QUrl params;

	params.addQueryItem("playerName", _target.playerName);
	params.addQueryItem("tableName", _target.tableName);
	data = params.encodedQuery();

	reply = m->post(request, data);
	connect(reply, SIGNAL(finished()), this, SLOT(finish()));
}

bool HelloSender::alreadySent(const ConnectionTarget &target){
	return targets->contains(target);
}

void HelloSender::add(ConnectionTarget target){
	targets->push_back(target);
}

void HelloSender::handleFinish(){
	if(reply->error() == QNetworkReply::NoError){
		QByteArray ba = reply->readAll();

		QJson::Parser parser;
		bool ok;
		QVariantMap result = parser.parse(ba, &ok).toMap();
		QVariant type = result.value("type");
		QVariant message = result.value("message");
		QVariant testTable = result.value("testTable");

		if(type.toString() == "InvalidInput"){
			error->append(message.toString());
			bad->append(_target.tableName);
			emit errored();
		} else if(type.toString() == "Acknowledge"){
			good->append(_target.tableName);
			good->append(testTable.toString());
			emit connected(_target, testTable.toString());
		}

	} else {
		error->append(reply->errorString());
		bad->append(_target.tableName);
		emit errored();
	}
}

void HelloSender::showDialog(){
	QString message = "";
	if(good->size() > 0){
		message.append("Connected to: ");
		for(int i=0; i<good->size(); ++i){
			message.append(good->at(i));
			if(i != good->size()-1){
				message.append( ", ");
			}
		}
		message.append("\n");
	}

	if(bad->size() > 0){
		message.append("Failed to connect to: ");
		for(int i=0; i<bad->size(); ++i){
			message.append(bad->at(i));
			if(i != bad->size()-1){
				message.append( ", ");
			}
		}
		message.append("\n");
	}

	if(error->size() > 0){
		message.append("Errors: ");
		for(int i=0; i<error->size(); ++i){
			message.append(error->at(i));
			if(i != error->size()-1){
				message.append( ", ");
			}
		}
	}

	QMessageBox *qmb = new QMessageBox(QMessageBox::Information, "Information", message);
	qmb->setModal(false);
	qmb->show();
}

void HelloSender::test(){
	std::cout << "Test" << std::endl;
}

void HelloSender::finish(){
	--counter;
	if(counter == 0){
		handleFinish();
		showDialog();
	} else {
		handleFinish();
	}
}
