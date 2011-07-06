#include "helpWindow.hpp"
#include "ui_helpWindow.h"
#include <QMenu>

HelpWindow::HelpWindow(QWidget *parent)
        : QWidget(parent),
          ui(new Ui::HelpWindow)
{
        ui->setupUi(this);

        QMenu *menu = new QMenu();
        menu->addAction("Connectie met een tafel maken");
        menu->addAction("Regels maken");
        menu->addAction("Regels versturen");
        ui->btnInformation->setMenu(menu);

        showHelpConnection();
        showHelpCreateRules();
        showHelpSendRules();
}

HelpWindow::~HelpWindow()
{
        delete ui;
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
