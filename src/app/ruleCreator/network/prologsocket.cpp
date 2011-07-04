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

#include "prologsocket.hpp"
#include <QtNetwork/QTcpSocket>
#include "WW10_protocol.pb.h"
#include "../settingsmanager.hpp"

PrologSocket::PrologSocket(const ConnectionTarget & target, QObject * parent)
  : QObject(parent),
     _target(target),
    _socket(new QTcpSocket(this))
{
}

QString PrologSocket::sendPrologCode(const QString & code)
{
	connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError()));
	_socket->connectToHost(_target.ipAddress, _target.portNumber, QIODevice::WriteOnly);

	if(!_socket->waitForConnected(1000) || !_socket->isWritable() || !_socket->isValid())
		return QString(tr("invalid socket: %1")).arg(_socket->errorString());

	ww10::PrologBotDescription d;
	d.set_id(_target.id-1);
	d.set_name(qPrintable(SettingsManager::Instance()->name()));
	d.set_prolog(qPrintable(code));

	std::string data = d.SerializeAsString();
	_socket->write(data.c_str(), data.size());

	if(!_socket->waitForBytesWritten(3000))
		return _socket->errorString();
	else
		return QString();
}

void PrologSocket::onSocketError()
{
		emit error(_socket->errorString());
}
