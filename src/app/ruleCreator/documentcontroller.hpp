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


#ifndef DOCUMENTCONTROLLER_HPP
#define DOCUMENTCONTROLLER_HPP

#include <QObject>
#include <ruleSystem/util/macro.hpp>

namespace ruleSystem
{
class Action;
}

class RuleListWidget;

class DocumentController : public QObject
{
	Q_OBJECT

public:
	static const QString Filter() { return "rule sets (*.rbs *.*)"; }

	DocumentController(RuleListWidget * w, QObject * parent = 0);

	QList<ruleSystem::Action*> checkAllRules();

public slots:
	void save();
	void saveAs();
	void open();
	void newFile();
	void askForSave();

signals:
	void error(const QString & title, const QString & errorMessage);
	void numberOfRulesChanged(int numberOfValidRules);

private slots:
	void onRuleChanged();

private:
	void writeToFile(const QString & fileName);
	void readFromFile(const QString & fileName);


	RefVarGetSet(QString, filename, Filename);
	SimpleVarGetSet(bool, isChanged, Changed);

private:
	RuleListWidget * _ruleList;
};

#endif // DOCUMENTCONTROLLER_HPP
