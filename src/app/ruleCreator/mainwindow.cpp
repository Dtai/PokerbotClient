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

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <ruleSystem/dbwrapper.hpp>
#include <ruleSystem/feature.hpp>
#include <ruleSystem/function.hpp>
#include <ruleSystem/constant.hpp>
#include <ruleSystem/graphicsView/elementfactory.hpp>
#include <ruleSystem/graphicsView/elementgraphicsitem.hpp>
#include <ruleSystem/graphicsView/elementgraphicsscene.hpp>
#include <ruleSystem/prolog/prologwriter.hpp>
#include <ruleSystem/util/translator.hpp>

#include <pokerRuleSystem/pokerrulesystem.hpp>
#include <pokerRuleSystem/pokeraction.hpp>
#include <pokerRuleSystem/raiseaction.hpp>
#include <pokerRuleSystem/booleanfunction.hpp>
#include <pokerRuleSystem/simpledb.hpp>
#include <pokerRuleSystem/prolog/prologwriter.hpp>

#include "model/elementmodel.hpp"
#include "model/predefinedelementmodel.hpp"
#include "view/elementview.hpp"
#include "network/codeSender.hpp"

#include <QDockWidget>
#include <QTreeView>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QDebug>
#include <QGraphicsView>
#include <QMessageBox>
#include <QInputDialog>
#include <QWebView>

#include "rulewidget.hpp"
#include "rulelistwidget.hpp"
#include "documentcontroller.hpp"
#include "settingsmanager.hpp"
#include "settingsdialog.hpp"
#include "helpWindow.hpp"
#include "visualiseWindow.hpp"
#include "welcomeWindow.hpp"

using namespace ruleSystem;
using namespace ruleSystem::graphicsView;
using namespace poker;

const QString emptyRuleSetSender() { return QString("emptyRuleSetSender"); }

namespace
{
QDockWidget * createDockWidget(const QString & title, const QList<Element*> & elements, ElementModel::ElementDescriber * describer, QWidget * parent);
QString writePrologCode(const QList<Action*> & actionList);
ruleSystem::Feature * registerAndCreateFeature(SimpleDB & db, const QString & name, const ruleSystem::Type & type, const QString & description = QString());
ruleSystem::Function * createFunction(const Calculator * calculator, const QString & description);
ruleSystem::Constant * createConstant(const Type & type, const QVariant & value, const QString & description);
ruleSystem::Action * createAction(ruleSystem::Action * a, const QString & description);
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
		ui(new Ui::MainWindow),
		_ruleList(new RuleListWidget),
		_docController(new DocumentController(_ruleList, this)),
		_settings(SettingsManager::Instance()),
		_predefModel()
{
	poker::initialise();

	ui->setupUi(this);
	createDockWidgets();
	ui->scrollArea->setWidget(_ruleList);

	connect(_ruleList, SIGNAL(ruleWantsDeletion(int)), this, SLOT(onDeleteRule(int)));

	connect(ui->action_Save, SIGNAL(triggered()), _docController, SLOT(save()));
	connect(ui->action_Save_As, SIGNAL(triggered()), _docController, SLOT(saveAs()));
	connect(ui->action_Open, SIGNAL(triggered()), _docController, SLOT(open()));
	connect(ui->action_New, SIGNAL(triggered()), _docController, SLOT(newFile()));

	connect(_settings, SIGNAL(settingsChanged()), this, SLOT(updateExportMenu()));
	connect(ui->menuExport, SIGNAL(triggered(QAction *)), this, SLOT(exportCode(QAction *)));
    connect(ui->actionShow_Code, SIGNAL(triggered()), this, SLOT(showCode()));
	connect(_docController, SIGNAL(numberOfRulesChanged(int)), this, SLOT(numberOfRulesChanged(int)));
	connect(_docController, SIGNAL(error(QString,QString)), this, SLOT(showError(QString,QString)));

	connect(ui->actionShow_information, SIGNAL(triggered()), this, SLOT(showInformation()));
	connect(ui->actionAdd_table, SIGNAL(triggered()), this, SLOT(addTable()));
	connect(ui->actionConnect_to_table, SIGNAL(triggered()), this, SLOT(showConnectToTable()));

	showMaximized();
	showWelcomeWindow();

	QWebView *tab1 = new QWebView(ui->tabWidget);
	ui->tabWidget->addTab(tab1, "Common table");
	tab1->setUrl(QUrl("http://134.58.39.45"));

	QWebView *tab2 = new QWebView(ui->tabWidget);
	ui->tabWidget->addTab(tab2, "Test table");
	tab2->setUrl(QUrl("http://134.58.39.45"));

	_predefModel.renewModel(_settings->predefinedElements());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::showWelcomeWindow(){
	_settings->reloadSettings();
	WelcomeWindow *ww = new WelcomeWindow(_settings);
	ww->setWindowModality(Qt::ApplicationModal);
	ww->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	ww->show();
}

void MainWindow::showInformation(){
    HelpWindow *hw = new HelpWindow();
    hw->show();
}

void MainWindow::showVisualisation(){
	VisualiseWindow *vw = new VisualiseWindow();
	vw->show();
}

void MainWindow::addTable(){
	QString nameTable;

	QInputDialog id;
	id.setLabelText("Wat is de naam van de tafel?");
	int res = id.exec();

	if(res == QDialog::Accepted){
		nameTable = id.textValue();
	} else {
		return;
	}

	QWebView *tab = new QWebView(ui->tabWidget);
	ui->tabWidget->addTab(tab, nameTable);
	QString url;
	url.append("http://tias.pagekite.me/ObserveTable.php?\"tableName=");
	url.append(nameTable);
	url.append("\"");
	tab->setUrl(QUrl(url));
}

void MainWindow::showError(const QString & title, const QString & errorMessage)
{
	QMessageBox::critical(0, title, errorMessage);
}

void MainWindow::showConnectToTable()
{
	_settings->reloadSettings();

	SettingsDialog * d = new SettingsDialog(_settings);
	d->setWindowModality(Qt::ApplicationModal);
	d->show();
}

void MainWindow::showCode()
{
	QList<Action*> validActions = _docController->checkAllRules();

	if(validActions.size() == 0)
		return;

	QString code = writePrologCode(validActions);
	QMessageBox::information(0, "Prolog code", code);
}

void MainWindow::updateExportMenu()
{
	ui->menuExport->clear();
	ui->menuExport->setEnabled(!_settings->connections().isEmpty());

	for(int i = 0; i < _settings->connections().size(); i++)
	{
		const ConnectionTarget & d = _settings->connections().at(i);
		QVariant val = QVariant::fromValue(d);

		QAction * subMenu = ui->menuExport->addAction(d.format());
		subMenu->setData(val);
		subMenu->setObjectName(QString("%1").arg(i));

		if(d.emptyRuleSetExporter)
		{
			QAction * subMenu = ui->menuExport->addAction(d.extendedFormat());
			subMenu->setData(val);
			subMenu->setObjectName(emptyRuleSetSender());
		}
	}
}

void MainWindow::exportCode(QAction * action)
{
	ConnectionTarget d = action->data().value<ConnectionTarget>();
	QList<Action*> validActions = _docController->checkAllRules();

	if(action->objectName() == emptyRuleSetSender())
	{
		CodeSender *cs = new CodeSender(d, "do(call, 1) :- true.");
		cs->send();
		return;
	}

	if(validActions.size() == 0)
		return;

	QString code = writePrologCode(validActions);

	if(code.isEmpty())
		return;

	CodeSender *cs = new CodeSender(d, code);
	cs->send();
}

void MainWindow::numberOfRulesChanged(int numberOfRealRules)
{
	ui->menuExport->setEnabled(numberOfRealRules != 0);
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	// save the file
	_docController->askForSave();

	// save the predefined elements
	_settings->setPredefinedElements(_predefModel.elements());
	_settings->writeSettings();

	event->accept();
}

void MainWindow::onDeleteRule(int rule)
{
	if(_ruleList->sceneForRule(rule) == 0)
		return;

	if(_ruleList->sceneForRule(rule)->isEmpty())
	{
		_ruleList->deleteRule(rule);
		return;
	}

	QString title = QString(tr("Verwijder regel %1")).arg(rule+1);
	QString text = QString(tr("Ben je zeker dat je regel %1 wil verwijderen?")).arg(rule+1);

	if(QMessageBox::question(this, title, text, QMessageBox::Yes | QMessageBox::Cancel) == QMessageBox::Cancel)
		return;

	_ruleList->deleteRule(rule);
}

void MainWindow::createDockWidgets()
{
	setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);

	/* Create the action list view */
	ui->vwFeature->setModel(new ElementModel(new FeatureDescriber, createAllFeatures(), this));
	ui->vwConstant->setModel(new ElementModel(new ConstantDescriber, createAllConstants(), this));
	ui->vwFunction->setModel(new ElementModel(new FunctionDescriber, createAllFunctions(), this));
	ui->vwAction->setModel(new ElementModel(new ActionDescriber, createAllActions(), this));

	ui->vwPredef->setModel(&_predefModel);
}

QList<Element*> MainWindow::createAllFeatures()
{
	db.setName("testDB");
	DBWrapper::RegisterDB(&db);

	QList<Element*> allFeatures;
	allFeatures << registerAndCreateFeature(db, "ispreflop", type::booleanType(), tr("Is the game in pre-flop-phase?"));
	allFeatures << registerAndCreateFeature(db, "isflop", type::booleanType(), tr("Is the game in flop-phase?"));
	allFeatures << registerAndCreateFeature(db, "isturn", type::booleanType(), tr("Is the game in turn fase?"));
	allFeatures << registerAndCreateFeature(db, "isriver", type::booleanType(), tr("Is the game in river-phase?"));
	allFeatures << registerAndCreateFeature(db, "ispostflop", type::booleanType(), tr("Is the game in post-flop-phase?"));
	allFeatures << registerAndCreateFeature(db, "isbigblind", type::booleanType(), tr("Am I second in row?"));
	allFeatures << registerAndCreateFeature(db, "issmallblind", type::booleanType(), tr("Am I first in row?"));
	allFeatures << registerAndCreateFeature(db, "isbutton", type::booleanType(), tr("Am I last in row?"));

	allFeatures << registerAndCreateFeature(db, "tekort", type::numericalType(), tr("How much many should I add to call?"));
	allFeatures << registerAndCreateFeature(db, "saldo", type::numericalType(), tr("How much money do I still have?"));
	allFeatures << registerAndCreateFeature(db, "potgrootte", type::numericalType(), tr("How much many is there in the pot?"));
	allFeatures << registerAndCreateFeature(db, "actievespelers", type::numericalType(), tr("How many players haven't folded yet?"));
	allFeatures << registerAndCreateFeature(db, "actievespelersmetgeld", type::numericalType(), tr("How many players haven't folded yet and are not all in?"));
	allFeatures << registerAndCreateFeature(db, "maximalewinst", type::numericalType(), tr("How much many can I maximally win?"));
	allFeatures << registerAndCreateFeature(db, "minimumraise", type::numericalType(), tr("What's the minimum I should raise?"));
	allFeatures << registerAndCreateFeature(db, "maximumraise", type::numericalType(), tr("What's the maximum I can raise?"));
	allFeatures << registerAndCreateFeature(db, "aantalraises", type::numericalType(), tr("How many times has there been raised this round?"));
	allFeatures << registerAndCreateFeature(db, Translator::AddTranslation("random", tr("random")), type::numericalType(), tr("A random number between zero and one."));

	allFeatures << registerAndCreateFeature(db, "handkaarten", type::cardListType(), tr("What are my hand cards?"));
	allFeatures << registerAndCreateFeature(db, "tafelkaarten", type::cardListType(), tr("What cards are there on the table?"));
	allFeatures << registerAndCreateFeature(db, "allekaarten", type::cardListType(), tr("What cards do I have in my hand or are on the table?"));

	return allFeatures;
}

QList<Element*> MainWindow::createAllFunctions()
{
	QList<Element*> functions;

	functions << createFunction(CalculatorCreator<function::ANDFunctor>::Create(), tr("This function returns true if all the inputs are true"));
	functions << createFunction(CalculatorCreator<function::ORFunctor>::Create(), tr("This function returns true as soon as one if the inputs is tru"));
	functions << createFunction(CalculatorCreator<function::NOTFunctor>::Create(), tr("This function return true to false and vice versa"));

	functions << createFunction(CalculatorCreator<function::NumEqualFunctor>::Create(), tr("This function returns true if two numbers are equal"));
	functions << createFunction(CalculatorCreator<function::NumLesserThanFunctor>::Create(), tr("This function returns true if number one is smaller than the second number"));
	functions << createFunction(CalculatorCreator<function::NumLesserThanOrEqualFunctor>::Create(), tr("This function returns true if number one is smalleror equal  than the second number"));
	functions << createFunction(CalculatorCreator<function::NumGreaterThanFunctor>::Create(), tr("This function returns true if number one is larger than the second number"));
	functions << createFunction(CalculatorCreator<function::NumGreaterThanOrEqualFunctor>::Create(), tr("This function returns true if number one is larger or equal than the second number"));

	functions << createFunction(CalculatorCreator<function::BoolEqualFunctor>::Create(), tr("This function returns true if both the inputs have the same value"));

	functions << createFunction(CalculatorCreator<function::AddFunctor>::Create(), tr("This functions calculates the sum of the inputs"));
	functions << createFunction(CalculatorCreator<function::MultiplyFunctor>::Create(), tr("This functions calculates the product of the inputs"));
	functions << createFunction(CalculatorCreator<function::SubtractFunctor>::Create(), tr("This functions calculates the difference of the inputs"));
	functions << createFunction(CalculatorCreator<function::DivideFunctor>::Create(), tr("This functions divides number one by number two"));

	functions << createFunction(CalculatorCreator<function::ContainsFunctor>::Create(), tr("This functions checks if the cardlist matches the cardequation"));

	return functions;
}

QList<Element*> MainWindow::createAllConstants()
{
	QList<Element*> constants;

	constants << createConstant(type::booleanType(), true, tr("A boolean constant, true or false"));
	constants << createConstant(type::numericalType(), 3.14f, tr("A rational number"));
	constants << createConstant(type::cardEquationType(), QVariant::fromValue<QList<Card> >(QList<Card>() << Card()), tr("A cardequation consisting out of one or more cards"));

	return constants;
}

QList<Element*> MainWindow::createAllActions()
{
	QList<Element*> actions;

	actions << createAction(new PokerAction("call"), tr("call if the input is true"));
	actions << createAction(new PokerAction("fold"), tr("fold if the input is true"));
	actions << createAction(new RaiseAction(), tr("raise with a certain value if the input is true"));

	return actions;
}

namespace
{
QDockWidget * createDockWidget(const QString & title, const QList<Element*> & elements, ElementModel::ElementDescriber * describer, QWidget * parent)
{
	/* Create the action list view */
	QDockWidget * dockW = new QDockWidget(title);
	QTreeView * view = new ElementView(dockW);
	dockW->setWidget(view);
	dockW->setFeatures(QDockWidget::DockWidgetMovable);

	view->setItemsExpandable(false);
	view->setRootIsDecorated(false);
	view->setModel(new ElementModel(describer, elements, parent));
	view->setDragEnabled(true);

	return dockW;
}

QString writePrologCode(const QList<Action*> & actionList)
{
	QStringList allCode;

	for(int i = 0; i < actionList.size(); i++)
	{
		Action * a = actionList[i];
		Q_ASSERT(a);

		QString error;
		bool success;

		ruleSystem::PrologWriter w(new poker::prolog::PokerCodeInformation(i+1));
		QString code = w.writeSafeCode(a, &success, &error);

		if(!success)
		{
			QMessageBox::critical(
						0,
						MainWindow::tr("Error creating prolog code"),
			MainWindow::tr("Error for rule %1: %2").arg(i).arg(error));

			return QString();
		}

		allCode << code;
	}


	return allCode.join("\n\n");
}

ruleSystem::Feature * registerAndCreateFeature(SimpleDB & db, const QString & name, const ruleSystem::Type & type, const QString & description)
{
	db.registerFeature(name, type);
	Feature * f = db.createFeature(name);
	f->setDescription(description);

	return f;
}

ruleSystem::Function * createFunction(const Calculator * calculator, const QString & description)
{
	Function * f = new Function(calculator);
	f->setDescription(description);

	return f;
}

ruleSystem::Constant * createConstant(const Type & type, const QVariant & value, const QString & description)
{
	Constant * c = new Constant(type, value);
	c->setDescription(description);

	return c;
}


ruleSystem::Action * createAction(ruleSystem::Action * a, const QString & description)
{
	a->setDescription(description);

	return a;
}

}
