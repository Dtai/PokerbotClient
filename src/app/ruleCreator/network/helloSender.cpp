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
#include <iostream>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include "qjson/src/json_parser.hh"
#include "config/reader.hpp"

HelloSender::HelloSender(const ConnectionTarget & target, QObject * parent)
  : QObject(parent),
	 _target(target)
{
}

QUrl getURL(){
	Reader r;
	return r.getHelloURL();
}

void HelloSender::send(){
	QNetworkAccessManager *m = new QNetworkAccessManager(this);

	QNetworkRequest request(getURL());
	request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

	QByteArray data;
	QUrl params;

	params.addQueryItem("playerName", _target.playerName);
	params.addQueryItem("tableName", _target.tableName);
	data = params.encodedQuery();

	targets->push_back(_target);

	QString s = request.url().toString();
	QString ss = params.toString();


	reply = m->post(request, data);
	connect(reply, SIGNAL(finished()), this, SLOT(finish()));
}

bool HelloSender::alreadySent(const ConnectionTarget &target){
	return targets->contains(target);
}

void HelloSender::finish(){
	if(reply->error() == QNetworkReply::NoError){
		QByteArray ba = reply->readAll();

		QJson::Parser parser;
		bool ok;
		QVariantMap result = parser.parse(ba, &ok).toMap();
		QVariant type = result.value("type");
		QVariant message = result.value("message");

		if(type.toString() == "InvalidInput"){
			QMessageBox *qmb = new QMessageBox(QMessageBox::Critical, "Invalid input", message.toString());
			qmb->show();
			emit errored();
		} else if(type.toString() == "Acknowledge"){
			QMessageBox *qmb = new QMessageBox(QMessageBox::Information, "Information", "Successfully connected to the table.");
			qmb->show();
			emit finished();
		}

	} else {
		QMessageBox *qmb = new QMessageBox(QMessageBox::Critical, "Connection error", reply->errorString());
		qmb->show();
		emit errored();
	}
}
