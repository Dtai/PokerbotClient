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

#ifndef HELLOSENDER_HPP
#define HELLOSENDER_HPP

#include <QObject>
#include <QNetworkReply>
#include <QVector>
#include "../connectiontarget.hpp"

class HelloSender : public QObject
{
	Q_OBJECT

public:
	explicit HelloSender(const ConnectionTarget & target, QObject * parent = 0);
	void send();
	static bool alreadySent(const ConnectionTarget &target);
	static void add(ConnectionTarget target);
	static void setCounter(int newCounter);
	static void initConnected();
signals:
	void connected(ConnectionTarget target, QString testTable);
	void errored();

private slots:
	void finish();
	void showNoConfigFile();
	void showWrongConfigFile();
	void test();

private:
	ConnectionTarget _target;
	QNetworkReply *reply;

	QUrl getURL();
	void showDialog();
	void handleFinish();
};

static QVector<ConnectionTarget> *targets = new QVector<ConnectionTarget>();
static int counter;
static QStringList *good;
static QStringList *bad;
static QStringList *error;

#endif // HELLOSENDER_HPP
