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
#include <pokerRuleSystem/dictionary/featureDictionary.hpp>

#include "model/elementmodel.hpp"
#include "model/predefinedelementmodel.hpp"
#include "view/elementview.hpp"
#include "network/codeSender.hpp"
#include "network/goodbyeSender.hpp"

#include <QDockWidget>
#include <QTreeView>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QDebug>
#include <QGraphicsView>
#include <QMessageBox>
#include <QInputDialog>
#include <QWebView>
#include <QtConcurrentRun>
#include <QDesktopWidget>

#include "rulewidget.hpp"
#include "rulelistwidget.hpp"
#include "documentcontroller.hpp"
#include "settingsmanager.hpp"
#include "settingsdialog.hpp"
#include "welcomeWindow.hpp"

#include "config/reader.hpp"

using namespace ruleSystem;
using namespace ruleSystem::graphicsView;
using namespace poker;

const QString emptyRuleSetSender() { return QString("emptyRuleSetSender"); }

namespace
{
QDockWidget * createDockWidget(const QString & title, const QList<Element*> & elements, ElementModel::ElementDescriber * describer, QWidget * parent);
QString writePrologCode(const QList<Action*> & actionList);
ruleSystem::Feature * registerAndCreateFeature(SimpleDB & db, const QString & name, const ruleSystem::Type & type, const QString & description = QString());
ruleSystem::Feature * registerAndCreateFeature(SimpleDB & db, const QString & name, const QString &uiName, const ruleSystem::Type & type, const QString & description = QString());
ruleSystem::Function * createFunction(const Calculator * calculator, const QString & description);
ruleSystem::Constant * createConstant(const Type & type, const QVariant & value, const QString & description);
ruleSystem::Action * createAction(ruleSystem::Action * a, const QString & description);
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
		ui(new Ui::MainWindow),
		_currentRuleList(0),
		_currentDocController(0),
		_settings(SettingsManager::Instance()),
		_predefModel(),
		hw(0)
{
	poker::initialise();

	ui->setupUi(this);
	createDockWidgets();
	ui->dwAction->setMaximumHeight(100);
	ui->dwConstant->setMaximumHeight(100);
	ui->dwPredef->setMaximumHeight(100);

	_ruleLists = new QMap<QString, RuleListWidget*>();
	_docControllers = new QMap<QString, DocumentController*>();

	ui->statusbar->showMessage(tr("Welcome"));

	QDesktopWidget w;
	int width = w.availableGeometry().width();
	ui->tabWidget->setMaximumWidth(width/3);
	addRuleTab("tab1");
	addRuleTab("tab2");
	addRuleTab("tab3");

	connect(_settings, SIGNAL(settingsChanged()), this, SLOT(updateExportMenu()));
	connect(ui->menuExport, SIGNAL(triggered(QAction *)), this, SLOT(exportCode(QAction *)));
	connect(ui->actionShow_Code, SIGNAL(triggered()), this, SLOT(showCode()));

	connect(ui->actionShow_information, SIGNAL(triggered()), this, SLOT(showInformation()));
	connect(ui->actionConnect_to_table, SIGNAL(triggered()), this, SLOT(showConnectToTable()));
	connect(ui->tabWidgetRules, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentRuleList(int)));

	tabs = new QVector<QWidget*>();

	showMaximized();
	showWelcomeWindow();

	_predefModel.renewModel(_settings->predefinedElements());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::showWelcomeWindow(){
	_settings->reloadSettings();
	WelcomeWindow *ww = new WelcomeWindow(_settings, this);
	ww->setWindowModality(Qt::ApplicationModal);
	ww->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	ww->show();
}

void MainWindow::showInformation(){
	hw = new HelpWindow();
    hw->show();
}

void MainWindow::changeCurrentRuleList(int index){
	if(_ruleLists->count() != 0){
		disconnectFromDocController();
		setCurrentRuleList(ui->tabWidgetRules->widget(index)->objectName());
		connectToDocController();
	}
}

void MainWindow::setCurrentRuleList(QString name){
	_currentRuleList = _ruleLists->value(name);
	_currentDocController = _docControllers->value(name);
}

void MainWindow::disconnectFromDocController(){
	disconnect(ui->action_Save, SIGNAL(triggered()), _currentDocController, SLOT(save()));
	disconnect(ui->action_Save_As, SIGNAL(triggered()), _currentDocController, SLOT(saveAs()));
	disconnect(ui->action_Open, SIGNAL(triggered()), _currentDocController, SLOT(open()));
	disconnect(ui->action_New, SIGNAL(triggered()), _currentDocController, SLOT(newFile()));
}

void MainWindow::connectToDocController(){
	connect(ui->action_Save, SIGNAL(triggered()), _currentDocController, SLOT(save()));
	connect(ui->action_Save_As, SIGNAL(triggered()), _currentDocController, SLOT(saveAs()));
	connect(ui->action_Open, SIGNAL(triggered()), _currentDocController, SLOT(open()));
	connect(ui->action_New, SIGNAL(triggered()), _currentDocController, SLOT(newFile()));
}

void MainWindow::addTab(QString playerName, QString tableName){
	Reader r;
	QUrl url = r.getWatchTableURL();
	url.addQueryItem("name", tableName);
	url.addQueryItem("playerName", playerName);

	QString tabName = "";
	tabName = "Tafel: " + tableName + " (" + playerName + ")";
	QString objectName = playerName + "@" + tableName;
	QWebView *tab = new QWebView(ui->tabWidget);
	tab->setUrl(url);
	tab->setObjectName(objectName);

	ui->tabWidget->addTab(tab, tabName);
	tabs->append(tab);
}

void MainWindow::addRuleTab(QString tabName){
	QScrollArea *scroll = new QScrollArea(ui->tabWidgetRules);
	scroll->setWidgetResizable(true);
	scroll->setObjectName(tabName);

	RuleListWidget *rlw = new RuleListWidget(scroll);
	scroll->setWidget(rlw);

	QVBoxLayout *vBoxLayout = new QVBoxLayout();
	vBoxLayout->addWidget(scroll);

	delete ui->tabWidgetRules->layout();
	ui->tabWidgetRules->setLayout(vBoxLayout);
	ui->tabWidgetRules->addTab(scroll, tabName);
	_ruleLists->insert(tabName, rlw);

	DocumentController *dc = new DocumentController(rlw, this);
	connect(dc, SIGNAL(numberOfRulesChanged(int)), this, SLOT(numberOfRulesChanged(int)));
	connect(dc, SIGNAL(error(QString,QString)), this, SLOT(showError(QString,QString)));
	_docControllers->insert(tabName, dc);

	connect(rlw, SIGNAL(ruleWantsDeletion(int)), this, SLOT(onDeleteRule(int)));

	// GUI will have first tab open, so that one is the current one
	if(_currentRuleList == 0){
		setCurrentRuleList(tabName);
		connectToDocController();
	}
}


void MainWindow::showError(const QString & title, const QString & errorMessage)
{
	QMessageBox::critical(0, title, errorMessage);
}

void MainWindow::showConnectToTable()
{
	_settings->reloadSettings();

	SettingsDialog * d = new SettingsDialog(_settings, this);
	d->setWindowModality(Qt::ApplicationModal);
	d->show();
}

void MainWindow::showCode()
{
	//QList<Action*> validActions = _docController->checkAllRules();
	DocumentController *dc = new DocumentController(_currentRuleList);
	QList<Action *> validActions = dc->checkAllRules();

	if(validActions.size() == 0)
		return;

	QString code = writePrologCode(validActions);
	if(!code.isEmpty()){
		QMessageBox::information(0, tr("Prolog code"), code);
	}
}

void MainWindow::updateExportMenu()
{
	ui->menuExport->clear();
	ui->menuExport->setEnabled(!_settings->connections().isEmpty());

    QString prefix = tr("Current tab to ");

	for(int i = 0; i < _settings->connections().size(); i++)
	{
		const ConnectionTarget & d = _settings->connections().at(i);
		QVariant val = QVariant::fromValue(d);

		QAction * subMenu = ui->menuExport->addAction(prefix + d.format());
		subMenu->setData(val);
		subMenu->setObjectName(QString("%1").arg(i));
	}
}

void MainWindow::exportCode(QAction* choice)
{
	ui->statusbar->showMessage(tr("Exporting code"));

	// retrieve connection (from choice)
	ConnectionTarget d = choice->data().value<ConnectionTarget>();

	// retrieve rules (from _currentDocController)
	QList<Action*> validRules = _currentDocController->checkAllRules();

	if(validRules.size() == 0){
		ui->statusbar->showMessage(tr("Nothing to export"));
		return;
	}

	QString code = writePrologCode(validRules);

	if(code.isEmpty()){
		ui->statusbar->showMessage(tr("Nothing to export"));
		return;
	}

	CodeSender *cs = new CodeSender(d, code);
	connect(cs, SIGNAL(finished()), this, SLOT(correctExportCode()));
	connect(cs, SIGNAL(errored()), this, SLOT(incorrectExportCode()));
	cs->send();

	int index = 0;
	for(int i=0; i<tabs->size(); ++i){
		if(tabs->at(i)->objectName() == d.playerName + "@" + d.tableName){
			index = i;
		}
	}

	ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::correctExportCode(){
	ui->statusbar->showMessage(tr("Code correct exported"));
}

void MainWindow::incorrectExportCode(){
	ui->statusbar->showMessage(tr("Code incorrect exported"));
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

void MainWindow::resizeEvent(QResizeEvent *event){
	ui->tabWidget->setMaximumWidth(width()/3);
	event->accept();
}

void MainWindow::sendGoodbye(){
	for(int i=0; i<_settings->connections().count(); ++i){
		ConnectionTarget ct;
		ct.playerName = _settings->connections().at(i).playerName;
		ct.tableName = _settings->connections().at(i).tableName;

		GoodbyeSender *gs = new GoodbyeSender(ct);
		gs->send();
	}
}

void MainWindow::closeEvent(QCloseEvent * event) {
	ui->statusbar->showMessage(tr("Goodbye"));
	sendGoodbye();

	// save the file
//	Ask for save for every tab
//	for(int i=0; i< ui->tabWidgetRules->count(); ++i){
//		ui->tabWidgetRules->setCurrentIndex(i);
//		_docControllers->value(ui->tabWidgetRules->tabText(i))->askForSave();
//	}

	if(_currentDocController->askForSave()){
		// save the predefined elements
		_settings->setPredefinedElements(_predefModel.elements());
		_settings->writeSettings();

		if(hw !=0 && hw->isVisible()){
			hw->close();
		}

		event->accept();
	} else {
		event->ignore();
	}
}

void MainWindow::onDeleteRule(int rule)
{
	if(_currentRuleList->sceneForRule(rule) == 0){
		return;
	}

	if(_currentRuleList->sceneForRule(rule)->isEmpty()){
		_currentRuleList->deleteRule(rule);
		return;
	}

	QString title = QString(tr("Delete rule %1")).arg(rule+1);
	QString text = QString(tr("Are you sure you want to delete rule %1?")).arg(rule+1);

	if(QMessageBox::question(this, title, text, QMessageBox::Yes | QMessageBox::Cancel) == QMessageBox::Cancel)
		return;

	_currentRuleList->deleteRule(rule);
}

void MainWindow::createDockWidgets()
{
	setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);

	/* Create the action list view */
	ui->vwFeature->setModel(new ElementModel(new FeatureDescriber, createAllFeatures(), this));
	ui->vwConstant->setModel(new ElementModel(new ConstantDescriber, createAllConstants(), this));
	ui->vwFunction->setModel(new ElementModel(new FunctionDescriber, createAllFunctions(), this));
	ui->vwAction->setModel(new ElementModel(new ActionDescriber, createAllActions(), this));

	ui->vwCard->setModel(new ElementModel(new UniversalDescriber, createCard(), this));

	ui->vwPredef->setModel(&_predefModel);
}

QList<Element*> MainWindow::createCard(){
	QList<Element*> elements;

	Feature *f1 = new Feature(type::cardListType(), HandCards::name());
	f1->setDevName(HandCards::devName());
	f1->setDescription(tr("What are my hand cards?"));
	elements.append(f1);

	Feature *f2 = new Feature(type::cardListType(), TableCards::name());
	f2->setDevName(TableCards::devName());
	f2->setDescription(tr("What cards are there on the table?"));
	elements.append(f2);

	Feature *f3 = new Feature(type::cardListType(), AllCards::name());
	f3->setDevName(AllCards::devName());
	f3->setDescription(tr("What cards do I have in my hand or are on the table?"));
	elements.append(f3);

	Function *f4 = new Function(CalculatorCreator<function::ContainsFunctor>::Create());
	f4->setDescription(tr("This functions checks if the cardlist matches the cardequation"));
	elements.append(f4);

	Constant *c = new Constant(type::cardEquationType(), QVariant::fromValue<QList<Card> >(QList<Card>() << Card()));
	c->setDescription(tr("A cardequation consisting out of one or more cards"));
	elements.append(c);

	return elements;
}

QList<Element*> MainWindow::createAllFeatures()
{
	db.setName("testDB");
	DBWrapper::RegisterDB(&db);

	QList<Element*> allFeatures;
	allFeatures << registerAndCreateFeature(db, IsPreFlop::name(), IsPreFlop::devName(), type::booleanType(), tr("Is the game in pre-flop-phase?"));
	allFeatures << registerAndCreateFeature(db, IsFlop::name(), IsFlop::devName(), type::booleanType(), tr("Is the game in flop-phase?"));
	allFeatures << registerAndCreateFeature(db, IsTurn::name(), IsTurn::devName(), type::booleanType(), tr("Is the game in turn fase?"));
	allFeatures << registerAndCreateFeature(db, IsRiver::name(), IsRiver::devName(), type::booleanType(), tr("Is the game in river-phase?"));
	allFeatures << registerAndCreateFeature(db, IsPostFlop::name(), IsPostFlop::devName(), type::booleanType(), tr("Is the game in post-flop-phase?"));
	allFeatures << registerAndCreateFeature(db, IsBigBlind::name(), IsBigBlind::devName(), type::booleanType(), tr("Am I second in row?"));
	allFeatures << registerAndCreateFeature(db, IsSmallBlind::name(), IsSmallBlind::devName(), type::booleanType(), tr("Am I first in row?"));
	allFeatures << registerAndCreateFeature(db, IsButton::name(), IsButton::devName(), type::booleanType(), tr("Am I last in row?"));

	allFeatures << registerAndCreateFeature(db, Shortage::name(), Shortage::devName(), type::numericalType(), tr("How much many should I add to call?"));
	allFeatures << registerAndCreateFeature(db, Balance::name(), Balance::devName(), type::numericalType(), tr("How much money do I still have?"));
	allFeatures << registerAndCreateFeature(db, PotSize::name(), PotSize::devName(), type::numericalType(), tr("How much many is there in the pot?"));
	allFeatures << registerAndCreateFeature(db, ActivePlayers::name(), ActivePlayers::devName(), type::numericalType(), tr("How many players haven't folded yet?"));
	allFeatures << registerAndCreateFeature(db, ActivePlayersWithMoney::name(), ActivePlayersWithMoney::devName(), type::numericalType(), tr("How many players haven't folded yet and are not all in?"));
	allFeatures << registerAndCreateFeature(db, MaximumProfit::name(), MaximumProfit::devName(), type::numericalType(), tr("How much many can I maximally win?"));
	allFeatures << registerAndCreateFeature(db, MinimumRaise::name(), MinimumRaise::devName(), type::numericalType(), tr("What's the minimum I should raise?"));
	allFeatures << registerAndCreateFeature(db, MaximumRaise::name(), MaximumRaise::devName(), type::numericalType(), tr("What's the maximum I can raise?"));
	allFeatures << registerAndCreateFeature(db, AmountRaises::name(), AmountRaises::devName(), type::numericalType(), tr("How many times has there been raised this round?"));
	allFeatures << registerAndCreateFeature(db, Translator::AddTranslation("random", tr("random")), type::numericalType(), tr("A random number between zero and one."));

	allFeatures << registerAndCreateFeature(db, HandCards::name(), HandCards::devName(), type::cardListType(), tr("What are my hand cards?"));
	allFeatures << registerAndCreateFeature(db, TableCards::name(), TableCards::devName(), type::cardListType(), tr("What cards are there on the table?"));
	allFeatures << registerAndCreateFeature(db, AllCards::name(), AllCards::devName(), type::cardListType(), tr("What cards do I have in my hand or are on the table?"));

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

ruleSystem::Feature * registerAndCreateFeature(SimpleDB & db, const QString & name, const QString &devName, const ruleSystem::Type & type, const QString & description)
{
	db.registerFeature(name, type);
	Feature * f = db.createFeature(name);
	f->setDescription(description);
	f->setDevName(devName);

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
