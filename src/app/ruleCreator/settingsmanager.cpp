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

#include "settingsmanager.hpp"
#include <ruleSystem/element.hpp>
#include <ruleSystem/serialization/qt/elementserializer.hpp>
#include <QDataStream>
#include <QByteArray>

namespace {

QByteArray predefinedElementsToByteArray(const QList<PredefinedElement> & elements);
QList<PredefinedElement> byteArrayToPredefinedElements(QByteArray ar);

}


SettingsManager::SettingsManager(QObject * parent)
	: QObject(parent)
{
}

void SettingsManager::reloadSettings()
{
	QSettings s(SettingsManager::CompanyName(), SettingsManager::ApplicationName());
	_connections = s.value(SettingsManager::Connections()).value<QList<ConnectionTarget> >();
	_name = s.value(SettingsManager::Name()).toString();
	_predefinedElements = byteArrayToPredefinedElements(s.value(SettingsManager::PredefinedElements()).toByteArray());

	emit settingsChanged();
}

void SettingsManager::addConnection(const ConnectionTarget & conTar)
{
	_connections << conTar;
}

void SettingsManager::updateConnection(int pos, const ConnectionTarget & conTar)
{
	Q_ASSERT(pos >= 0 || pos < _connections.size());
	_connections[pos] = conTar;
}

void SettingsManager::removeConnection(int pos)
{
	Q_ASSERT(pos >= 0 || pos < _connections.size());
	_connections.removeAt(pos);
}

void SettingsManager::writeSettings()
{
	QSettings s(SettingsManager::CompanyName(), SettingsManager::ApplicationName());
	s.setValue(SettingsManager::Connections(), QVariant::fromValue<QList<ConnectionTarget> >(connections()));
	s.setValue(SettingsManager::Name(), name());
	s.setValue(SettingsManager::PredefinedElements(), predefinedElementsToByteArray(predefinedElements()));

	emit settingsChanged();
}

namespace {

QByteArray predefinedElementsToByteArray(const QList<PredefinedElement> & elements)
{
	QByteArray ar;
	QDataStream s(&ar, QIODevice::WriteOnly);

	s << elements.size();

	for(int i = 0; i < elements.size(); i++)
		s << elements.at(i).name << elements.at(i).description << elements.at(i).predefinedElement;

	return ar;
}

QList<PredefinedElement> byteArrayToPredefinedElements(QByteArray ar)
{
	QList<PredefinedElement> retVal;

	QDataStream s(&ar, QIODevice::ReadOnly);

	int size;
	s >> size;

	for(int i =0 ;i < size; i++)
	{
		PredefinedElement e;
		s >> e.name >> e.description >> e.predefinedElement;
		retVal << e;
	}

	return retVal;
}

}
