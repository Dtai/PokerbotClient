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

		ui->textEdit->setText("Card 1:\n");

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
	QString previous = ui->textEdit->toPlainText();
	ui->textEdit->setText(previous.append("\tColor: ").append(ui->color->currentText()));
}

void CardEvaluator::addValue(){
	QString previous = ui->textEdit->toPlainText();
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
		ui->textEdit->setText(new4);
	} else {
		ui->textEdit->setText(new2);
	}
}
