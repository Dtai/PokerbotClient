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

	menu = new QMenu();
	actions = new QList<QAction *>();

	actions->append(menu->addAction("Tutorial"));
	actions->last()->setObjectName("tutorial");

	actions->append(menu->addAction("Wat is poker"));
	actions->last()->setObjectName("poker");

	actions->append(menu->addAction("Wat is ruleCreator"));
	actions->last()->setObjectName("ruleCreator");

	actions->append(menu->addAction("Wat zijn de features"));
	actions->last()->setObjectName("features");

	actions->append(menu->addAction("Wat zijn de functies"));
	actions->last()->setObjectName("functions");

	ui->btnInformation->setMenu(menu);

	connect(ui->btnInformation->menu(), SIGNAL(triggered(QAction*)), this, SLOT(menuSelection(QAction*)));
}

HelpWindow::~HelpWindow() {
	delete ui;
	delete menu;
}

void HelpWindow::menuSelection(QAction* action) {
	ui->btnInformation->setText(action->text());
	showHelp(action->objectName());
}

void HelpWindow::showHelp(QString id){
	QMap<QString, QUrl> links = helpEngine->linksForIdentifier(id);

	 if (!links.isEmpty()) {
		 QByteArray helpData = helpEngine->fileData(links.constBegin().value());
		 if (!helpData.isEmpty()){
			ui->information->setText(helpData);
		 }
	 }
}
