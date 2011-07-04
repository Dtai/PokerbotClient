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

#include "connectiontarget.hpp"

ConnectionTarget::ConnectionTarget()
	: ipAddress(QString()), portNumber(DefaultPort()), id(1), emptyRuleSetExporter(false)
{
}

QString ConnectionTarget::format() const
{
	return QString("%4 [%1@%2:%3]").arg(id).arg(ipAddress).arg(portNumber).arg(name);
}

QString ConnectionTarget::extendedFormat() const
{
	return QString("%1@%2").arg(QObject::tr("empty")).arg(format());
}

bool ConnectionTarget::operator==(const ConnectionTarget & rhs) const
{
	return rhs.name == name && rhs.id == id && rhs.ipAddress == ipAddress && rhs.portNumber == portNumber;
}

QDataStream & operator<<(QDataStream & out, const ConnectionTarget & cd)
{
	out << cd.ipAddress << cd.portNumber << cd.id << cd.name << cd.emptyRuleSetExporter;
	return out;
}

QDataStream & operator>>(QDataStream & in, ConnectionTarget & cd)
{
	in >> cd.ipAddress >> cd.portNumber >> cd.id >> cd.name >> cd.emptyRuleSetExporter;
	return in;
}
