#include "cardEvaluator.hpp"
#include "ui_cardEvaluator.h"

#include <iostream>

CardEvaluator::CardEvaluator(QWidget *parent)
        : QWidget(parent),
		  ui(new Ui::CardEvaluator)
{
		ui->setupUi(this);

		connect(ui->addColor, SIGNAL(clicked()), this, SLOT(addColor()));
		connect(ui->addValue, SIGNAL(clicked()), this, SLOT(addValue()));
		connect(ui->value, SIGNAL(editTextChanged(QString)), this, SLOT(changePostfix()));
		connect(ui->newCard, SIGNAL(clicked()), this, SLOT(addCard()));

		for(int i=2; i<=10; ++i){
			postfixes.append(QString::number(i));
		}
		postfixes.append("J");
		postfixes.append("Q");
		postfixes.append("K");
		postfixes.append("A");

		ui->postfix->setDisabled(true);
		ui->postfix_minus->setDisabled(true);
		ui->postfix_plus->setDisabled(true);

		selectedCard = ui->card0;
		selectedCard->setText("Card 1:\n");
}

CardEvaluator::~CardEvaluator()
{
        delete ui;
}

void CardEvaluator::changePostfix(){
	if(postfixes.contains(ui->value->currentText())){
		ui->postfix->setDisabled(true);
		ui->postfix_minus->setDisabled(true);
		ui->postfix_plus->setDisabled(true);
	} else {
		ui->postfix->setEnabled(true);
		ui->postfix_minus->setEnabled(true);
		ui->postfix_plus->setEnabled(true);
	}
}

void CardEvaluator::addColor(){
	QString previous = selectedCard->text();
	selectedCard->setText(previous.append("\tColor: ").append(ui->color->currentText()));
}

void CardEvaluator::addValue(){
	QString previous = selectedCard->text();
	QString new0 = previous.append("\tValue: ");
	QString new1 = new0.append(ui->prefix->currentText());
	QString new2 = new1.append(ui->value->currentText());

	if(ui->postfix_minus->isEnabled()){
		QString new3 = new2;
		if(ui->postfix_minus->isChecked()){
			new3 = new3.append("-");
		} else if(ui->postfix_plus->isChecked()) {
			new3 = new3.append("+");
		}

		QString new4 = new3.append(ui->postfix->currentText());
		selectedCard->setText(new4);
	} else {
		selectedCard->setText(new2);
	}
}

void CardEvaluator::addCard(){
	QPushButton *btn = new QPushButton(ui->cards);
	btn->setGeometry(20, 80, 250, 50);
	btn->setText("Card 2:\n");
	btn->show();
	selectedCard = btn;
}
