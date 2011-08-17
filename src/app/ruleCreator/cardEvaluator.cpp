#include "cardEvaluator.hpp"
#include "ui_cardEvaluator.h"

#include <iostream>

CardEvaluator::CardEvaluator(QWidget *parent)
        : QWidget(parent),
		  ui(new Ui::CardEvaluator)
{
		ui->setupUi(this);

		connect(ui->addValue, SIGNAL(clicked()), this, SLOT(addValue()));
		connect(ui->value, SIGNAL(editTextChanged(QString)), this, SLOT(changePostfix()));
		connect(ui->newCard, SIGNAL(clicked()), this, SLOT(addCard()));
		connect(ui->deleteCard, SIGNAL(clicked()), this, SLOT(deleteCard()));
		connect(ui->color, SIGNAL(editTextChanged(QString)), this, SLOT(redrawCard()));
		connect(ui->prefix, SIGNAL(editTextChanged(QString)), this, SLOT(redrawCard()));
		connect(ui->value, SIGNAL(editTextChanged(QString)), this, SLOT(redrawCard()));
		connect(ui->postfix, SIGNAL(editTextChanged(QString)), this, SLOT(redrawCard()));
		connect(ui->postfix_minus, SIGNAL(clicked()), this, SLOT(redrawCard()));
		connect(ui->postfix_plus, SIGNAL(clicked()), this, SLOT(redrawCard()));

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

		layout = new QVBoxLayout;
		cards = new QVector<QPushButton*>();
		numberOfCards = 0;

		information = new QMap<QPushButton*, QMap<QString, QString>*>();

		addCard();
}

CardEvaluator::~CardEvaluator()
{
        delete ui;
}

void CardEvaluator::redrawCard(){
	information->insert(selectedCard, getCurrentInformation());
	updateInformationCurrentCard();
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
	btn->setObjectName(QString::number(numberOfCards));
	btn->setMinimumSize(250, 50);
	++numberOfCards;
	btn->setText("Card " + QString::number(numberOfCards) + ":\n");
	btn->show();
	selectedCard = btn;

	layout->addWidget(btn);
	QWidget *viewport = new QWidget;
	viewport->setLayout(layout);
	ui->cards->setWidget(viewport);

	cards->append(btn);

	connect(btn, SIGNAL(clicked()), this, SLOT(selectCard()));

	information->insert(selectedCard, getCurrentInformation());
	updateInformationCurrentCard();
}

void CardEvaluator::selectCard(){
	QString card = sender()->objectName();
	selectedCard = cards->at(card.toInt());

	loadInformationFromSelectedCard();
}

QMap<QString, QString> *CardEvaluator::getCurrentInformation(){
	QMap<QString, QString> *result = new QMap<QString, QString>();

	result->insert("color", ui->color->currentText());
	result->insert("operator", ui->prefix->currentText());
	result->insert("value", ui->value->currentText());
	if(ui->postfix->isEnabled()){
		if(ui->postfix_minus){
			result->insert("postfixOperator", "-");
		} else {
			result->insert("postfixOperator", "+");
		}
		result->insert("postfixValue", ui->postfix->currentText());
	}

	return result;
}

void CardEvaluator::loadInformationFromSelectedCard(){
	ui->color->setCurrentIndex(ui->color->findText(information->value(selectedCard)->value("color")));
	ui->prefix->setCurrentIndex(ui->prefix->findText(information->value(selectedCard)->value("operator")));
	ui->value->setCurrentIndex(ui->value->findText(information->value(selectedCard)->value("value")));
	if(information->value(selectedCard)->contains("postfixOperator")){
		if(information->value(selectedCard)->value("postfixOperator") == "+"){
			ui->postfix_plus->setChecked(true);
		} else {
			ui->postfix_minus->setChecked(true);
		}
	}
	if(information->value(selectedCard)->contains("postfixValue")){
		ui->postfix->setCurrentIndex(ui->postfix->findText(information->value(selectedCard)->value("postfixValue")));
	}
}

void CardEvaluator::updateInformationCurrentCard(){
	QString text = "Card ";
	text.append(selectedCard->objectName()).append("\n");
	text.append("Color: ").append(information->value(selectedCard)->value("color"));
	text.append("\nValue: ").append(information->value(selectedCard)->value("operator"));
	text.append(information->value(selectedCard)->value("value"));
	text.append(information->value(selectedCard)->value("postfixOperator"));
	text.append(information->value(selectedCard)->value("postfixValue"));

	selectedCard->setText(text);
}

void CardEvaluator::deleteCard(){
	int index = cards->indexOf(selectedCard);
	cards->remove(index);
	--numberOfCards;
	delete selectedCard;
	if(index > 0){
		selectedCard = cards->at(index-1);
	} else {
		addCard();
	}
}

