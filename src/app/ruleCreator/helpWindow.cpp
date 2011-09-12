#include "helpWindow.hpp"
#include "ui_helpWindow.h"

#include <QMenu>

HelpWindow::HelpWindow(QWidget *parent)
	: QWidget(parent),
	  ui(new Ui::HelpWindow)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);

	connectToTable = new QString("Connectie met een tafel maken");
	makeRules = new QString("Regels maken");
	sendRules = new QString("Regels versturen");

	menu = new QMenu();
	menu->addAction(*connectToTable);
	menu->addAction(*makeRules);
	menu->addAction(*sendRules);
	ui->btnInformation->setMenu(menu);

	connect(ui->btnInformation->menu(), SIGNAL(triggered(QAction*)), this, SLOT(menuSelection(QAction*)));
}

HelpWindow::~HelpWindow()
{
	delete ui;
	delete connectToTable;
	delete makeRules;
	delete sendRules;
	delete menu;
}

void HelpWindow::menuSelection(QAction* action)
{
	if(action->text().compare(connectToTable) == 0){
		showHelpConnection();
	} else if (action->text().compare(makeRules) == 0 ){
		showHelpCreateRules();
	} else if(action->text().compare(sendRules) == 0){
		showHelpSendRules();
	} else {
		clear();
	}
}

void HelpWindow::showHelpConnection(){
	ui->information->setText("Hoe moet ik connecteren met een tafel?\n---Hier moet de uitleg komen---");
}

void HelpWindow::showHelpCreateRules(){
	ui->information->setText("Hoe moet ik regels maken?\n---Hier moet de uitleg komen---");
}

void HelpWindow::showHelpSendRules(){
	ui->information->setText("Hoe moet ik mijn regels versturen?\n---Hier moet de uitleg komen---");
}

void HelpWindow::clear(){
	ui->information->setText("");
}
