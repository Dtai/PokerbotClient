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

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

HelloSender::HelloSender(const ConnectionTarget & target, QObject * parent)
  : QObject(parent),
	 _target(target)
{
}

void HelloSender::send(){
	QNetworkAccessManager *m = new QNetworkAccessManager(this);

	//QNetworkRequest request(QUrl("http://tias.pagekite.me/hello.php"));
	QNetworkRequest request(QUrl("http://posttestserver.com/post.php"));
	request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

	QByteArray data;
	QUrl params;

	params.addQueryItem("playerName", _target.playerName);
	params.addQueryItem("tableName", _target.tableName);
	data = params.encodedQuery();

	QNetworkReply *reply = m->post(request, data);

	connect(reply, SIGNAL(finished()), this, SLOT(finish()));
}

void HelloSender::finish(){
	emit finished();
}
