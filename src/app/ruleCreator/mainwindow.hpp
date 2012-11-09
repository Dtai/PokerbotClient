/*******************************************************************
* Copyright (c) 2009 Thomas Fannes (thomasfannes@gmail.com)
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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <pokerRuleSystem/simpledb.hpp>
#include "model/predefinedelementmodel.hpp"
#include "helpWindow.hpp"

class SettingsManager;

namespace Ui
{
	class MainWindow;
}

namespace poker
{
	class SimpleDB;
}

class QVBoxLayout;
class RuleListWidget;
class DocumentController;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void showError(const QString & title, const QString & errorMessage);
	void addTab(QString playerName, QString tableName);
	void addRuleTab(QString tabName);

private slots:
	void onDeleteRule(int rule);
	void showCode();
	void updateExportMenu();
	void exportCode();
	void showInformation();
	void showConnectToTable();
	void numberOfRulesChanged(int numberOfRealRules);
	void correctExportCode();
	void incorrectExportCode();
	void changeCurrentRuleList(int index);

protected:
	void changeEvent(QEvent * e);
	void closeEvent(QCloseEvent * event);
	void resizeEvent(QResizeEvent *);

private:
	void createDockWidgets();
	void showWelcomeWindow();
	void setCurrentRuleList(QString name);
	void disconnectFromDocController();
	void connectToDocController();
	void sendGoodbye();

	QList<ruleSystem::Element*> createAllFeatures();
	QList<ruleSystem::Element*> createAllFunctions();
	QList<ruleSystem::Element*> createAllConstants();
	QList<ruleSystem::Element*> createAllActions();
	QList<ruleSystem::Element*> createCard();

private:
	Ui::MainWindow *ui;
	poker::SimpleDB db;
	SettingsManager * _settings;
	PredefinedElementModel _predefModel;
	QVector<QWidget*> *tabs;
	HelpWindow *hw;

	QMap<QString, RuleListWidget*> *_ruleLists;
	QMap<QString, DocumentController*> *_docControllers;
	RuleListWidget *_currentRuleList;
	DocumentController *_currentDocController;
};

#endif // MAINWINDOW_HPP
