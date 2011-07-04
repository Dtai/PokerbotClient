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

#include "documentcontroller.hpp"
#include "rulelistwidget.hpp"
#include "serialization/qt/ruleserialization.hpp"
#include "network/prologsocket.hpp"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <ruleSystem/exception.hpp>
#include <QDir>

using namespace ruleSystem::graphicsView;

DocumentController::DocumentController(RuleListWidget * w, QObject * parent)
	: QObject(parent),
    _ruleList(w),
    _isChanged(false)
{
	connect(_ruleList, SIGNAL(numberOfRulesChanged(int)), this, SIGNAL(numberOfRulesChanged(int)));
	connect(_ruleList, SIGNAL(rulesChanged()), this, SLOT(onRuleChanged()));
}

void DocumentController::save()
{
	if(!_isChanged)
		return;

	if(!QFile::exists(filename()))
	{
		saveAs();
		return;
	}

	writeToFile(filename());
}

void DocumentController::saveAs()
{
	if(filename().isEmpty())
		setFilename(QDir::homePath() + "/untitled");

	QString tmpFile = QFileDialog::getSaveFileName(0, tr("Save file"), filename(), DocumentController::Filter());
	if(tmpFile.isEmpty())
		return;

	setFilename(tmpFile);
	writeToFile(filename());
}

void DocumentController::askForSave()
{
	// if document is changed, ask for saving first
	if(isChanged())
	{
		if(QMessageBox::warning(0, tr("Unsaved data"), tr("The current document has unsaved data. Save first?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
			save();
	}
}

void DocumentController::open()
{
	askForSave();

	if(filename().isEmpty())
		setFilename(QDir::homePath());

	QString tmpFile = QFileDialog::getOpenFileName(0, tr("Open file"), filename(), DocumentController::Filter());
	if(tmpFile.isEmpty())
		return;

	setFilename(tmpFile);
	readFromFile(tmpFile);
}

void DocumentController::newFile()
{
	askForSave();
	_ruleList->clearAll();

	setFilename(QString());
	_isChanged = false;
}

QList<ruleSystem::Action*> DocumentController::checkAllRules()
{
	QList<ruleSystem::Action*> lst;

	for(int i = 0; i < _ruleList->numberOfRules()-1; i++)
	{
		ElementGraphicsScene * scene = _ruleList->sceneForRule(i);
		if(scene == 0)
		{
			emit error(tr("No rule defined"), QString(tr("There are no rules defined at position %1")).arg(i));
			return QList<ruleSystem::Action*>();
		}

		QString errorMsg;
		ruleSystem::Action * a = scene->getCorrectAction(&errorMsg);
		if(a == 0)
		{
			emit error(QString(tr("Error for rule %1")).arg(i), QString("Rule %1: %2").arg(i).arg(errorMsg));
			return QList<ruleSystem::Action*>();
		}

		lst << a;
	}

	return lst;
}

void DocumentController::onRuleChanged()
{
	_isChanged = true;
}

void DocumentController::writeToFile(const QString & fileName)
{
	QFile f(fileName);
	if(!f.open(QIODevice::WriteOnly))
	{
		emit error(tr("Error opening file"), QString(tr("Unable to open file '%1': %2")).arg(fileName, f.errorString()));
		return;
	}

	// create the data stream
	QDataStream s(&f);
	int numberOfRules = _ruleList->numberOfRules()-1;

	s << numberOfRules;

	try
	{
		for(int i = 0; i < numberOfRules; i++)
		{
			ElementGraphicsScene * curScene = _ruleList->sceneForRule(i);
			serialization::qt::serializeScene(curScene, s);
		}
	}
	catch(ruleSystem::Exception e)
	{
		emit error(tr("Error serializing to file"), QString(tr("Unable to serialize to file: %1")).arg(e.message()));
		return;
	}

	f.close();
	_isChanged = false;
}

void DocumentController::readFromFile(const QString & fileName)
{
	QFile f(fileName);
	if(!f.open(QIODevice::ReadOnly))
	{
		emit error(tr("Error opening file"), QString(tr("Unable to open file '%1': %2")).arg(fileName, f.errorString()));
		return;
	}

	_ruleList->clearAll();

	// create the data stream
	QDataStream s(&f);
	int numberOfRules;
	s >> numberOfRules;

	try
	{
		for(int i = 0; i < numberOfRules; i++)
		{
			_ruleList->insertRule(i);
			serialization::qt::deserializeScene(_ruleList->sceneForRule(i), s);
		}
	}
	catch(ruleSystem::Exception e)
	{
		emit error(tr("Error deserializing from file"), QString(tr("Unable to deserialize from file; %1")).arg(e.message()));
		return;
	}

	_isChanged = false;
}
