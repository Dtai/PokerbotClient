#include "helpWindow.hpp"
#include "ui_helpWindow.h"

#include <QMenu>
#include <QFileInfo>

HelpWindow::HelpWindow(QWidget *parent)
	: QWidget(parent),
	  ui(new Ui::HelpWindow)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	QFileInfo fileInfo("doc.qhc");
	helpEngine = new QHelpEngineCore(fileInfo.absoluteFilePath());

	tutorial = new QString("Tutorial");
	poker = new QString("Wat is poker");
	ruleCreator = new QString("Wat is RuleCreator");

	menu = new QMenu();
	actions = new QList<QAction *>();

	actions->append(menu->addAction(*tutorial));
	actions->last()->setObjectName("tutorial");

	actions->append(menu->addAction(*poker));
	actions->last()->setObjectName("poker");

	actions->append(menu->addAction(*ruleCreator));
	actions->last()->setObjectName("RuleCreator");

	ui->btnInformation->setMenu(menu);

	connect(ui->btnInformation->menu(), SIGNAL(triggered(QAction*)), this, SLOT(menuSelection(QAction*)));
}

HelpWindow::~HelpWindow() {
	delete ui;
	delete tutorial;
	delete poker;
	delete ruleCreator;
	delete menu;
}

void HelpWindow::menuSelection(QAction* action) {
	showHelp(action->objectName());
}

void HelpWindow::showHelp(QString id){
	QMap<QString, QUrl> links = helpEngine->linksForIdentifier(id);

	 if (links.count()) {
		 QByteArray helpData = helpEngine->fileData(links.constBegin().value());
		 if (!helpData.isEmpty()){
			ui->information->setText(helpData);
		 }
	 }
}
