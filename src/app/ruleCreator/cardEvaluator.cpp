#include "cardEvaluator.hpp"
#include "ui_cardEvaluator.h"

#include <iostream>

CardEvaluator::CardEvaluator(QWidget *parent)
        : QWidget(parent),
		  ui(new Ui::CardEvaluator)
{
		ui->setupUi(this);

		connect(ui->addValue, SIGNAL(clicked()), this, SLOT(addValue()));
		connect(ui->newCard, SIGNAL(clicked()), this, SLOT(addCard()));
		connect(ui->deleteCard, SIGNAL(clicked()), this, SLOT(deleteCard()));
		connect(ui->color, SIGNAL(editTextChanged(QString)), this, SLOT(redrawSelectedCard()));

		layoutValues = new QVBoxLayout;
		layoutCards = new QVBoxLayout;
		cards = new QVector<QPushButton*>();
		information = new QMap<QPushButton*, QMap<QString, QString>*>();

		operators = new QVector<QComboBox*>();
		values = new QVector<QComboBox*>();
		plusses = new QVector<QRadioButton*>();
		minusses = new QVector<QRadioButton*>();
		postfixValues = new QVector<QComboBox*>();

		separatedColors = false;
		separatedValues = new QVector<bool>();

		creator = new CardEvaluatorCreator();

		addCard();
		addValue();
		redrawSelectedCard();
}

CardEvaluator::~CardEvaluator()
{
        delete ui;
}

void CardEvaluator::redrawSelectedCard(){
	information->insert(selectedCard, getCurrentInformation());
	updateSelectedCard();
}

void CardEvaluator::changePostfix(){
	QComboBox *box = qobject_cast<QComboBox*>(sender());
	int index = sender()->objectName().toInt();
	if(box->currentText().at(0).isLower()){
		postfixValues->at(index)->setEnabled(true);
		minusses->at(index)->setEnabled(true);
		plusses->at(index)->setEnabled(true);
	} else {
		postfixValues->at(index)->setDisabled(true);
		minusses->at(index)->setDisabled(true);
		plusses->at(index)->setDisabled(true);
	}
}

void CardEvaluator::addValue(){
	operators->append(creator->createOperators(ui->valuesScroll));
	values->append(creator->createValues(ui->valuesScroll));
	plusses->append(creator->createRadioButtonPlus(ui->valuesScroll));
	minusses->append(creator->createRadioButtonMinus(ui->valuesScroll));
	postfixValues->append(creator->createPostfixValues(ui->valuesScroll));
	separatedValues->append(false);

	QComboBox *op = operators->last();
	QComboBox *val = values->last();
	QRadioButton *rbp = plusses->last();
	QRadioButton *rbm = minusses->last();
	QComboBox *postVal = postfixValues->last();

	QButtonGroup *group = new QButtonGroup(ui->valuesScroll);
	group->addButton(rbp);
	group->addButton(rbm);

	QVBoxLayout *rbs = new QVBoxLayout();
	rbs->addWidget(rbp);
	rbs->addWidget(rbm);

	QHBoxLayout *post = new QHBoxLayout();
	post->addLayout(rbs);
	post->addWidget(postVal);

	QHBoxLayout *newVal = new QHBoxLayout();
	newVal->addWidget(op);
	newVal->addWidget(val);
	newVal->addLayout(post);

	layoutValues->addLayout(newVal);
	QWidget *viewport = new QWidget;
	viewport->setLayout(layoutValues);
	ui->valuesScroll->setWidget(viewport);

	val->setObjectName(QString::number(plusses->size()-1));
	connect(val, SIGNAL(editTextChanged(QString)), this, SLOT(changePostfix()));
	connect(op, SIGNAL(currentIndexChanged(int)), this, SLOT(redrawSelectedCard()));
	connect(val, SIGNAL(editTextChanged(QString)), this, SLOT(redrawSelectedCard()));
	connect(postVal, SIGNAL(currentIndexChanged(int)), this, SLOT(redrawSelectedCard()));
	connect(rbm, SIGNAL(clicked()), this, SLOT(redrawSelectedCard()));
	connect(rbp, SIGNAL(clicked()), this, SLOT(redrawSelectedCard()));
}

void CardEvaluator::addCard(){
	updateOwnVariables();
	QPushButton *btn = new QPushButton("Card " + QString::number(cards->size()) + ":\n", ui->cards);
	btn->setObjectName(QString::number(cards->size()));
	connect(btn, SIGNAL(clicked()), this, SLOT(selectCard()));

	layoutCards->addWidget(btn);
	QWidget *viewport = new QWidget;
	viewport->setLayout(layoutCards);
	ui->cards->setWidget(viewport);
	cards->append(btn);

	selectedCard = btn;
	redrawSelectedCard();
}

void CardEvaluator::selectCard(){
	updateOwnVariables();

	QString card = sender()->objectName();
	selectedCard = cards->at(card.toInt());
	loadInformationFromSelectedCard();
}

void CardEvaluator::updateOwnVariables(){
	if(!separatedColors){
		ui->color->insertSeparator(ui->color->count());
		separatedColors = true;
	}

	for(int i=0; i<values->size(); ++i){
		if(!separatedValues->at(i)){
			values->at(i)->insertSeparator(values->at(i)->count());
			separatedValues->insert(i, true);
		}
	}

	if(ui->color->findText(ui->color->currentText()) == -1){
		ui->color->addItem(ui->color->currentText());
	}

	for(int i=0; i<values->size(); ++i){
		if(values->at(i)->findText(values->at(i)->currentText()) == -1){
			values->at(i)->addItem(values->at(i)->currentText());
		}
	}
}

QMap<QString, QString> *CardEvaluator::getCurrentInformation(){
	QMap<QString, QString> *result = new QMap<QString, QString>();

	result->insert("color", ui->color->currentText());
	for(int i=0; i<operators->size(); ++i){
		result->insertMulti("operator", operators->at(i)->currentText());
		result->insertMulti("value", values->at(i)->currentText());

		if(postfixValues->at(i)->isEnabled()){
			if(minusses->at(i)->isChecked()){
				result->insertMulti("postfixOperator", "-");
			} else {
				result->insertMulti("postfixOperator", "+");
			}
			result->insertMulti("postfixValue", postfixValues->at(i)->currentText());
		} else {
			result->insertMulti("postfixOperator", "");
			result->insertMulti("postfixValue", "");
		}
	}

	return result;
}

void CardEvaluator::loadInformationFromSelectedCard(){
	ui->color->setCurrentIndex(ui->color->findText(information->value(selectedCard)->value("color")));

	QList<QString> operators = information->value(selectedCard)->values("operator");
	QList<QString> values = information->value(selectedCard)->values("value");
	QList<QString> postfixOperators = information->value(selectedCard)->values("postfixOperator");
	QList<QString> postfixValues = information->value(selectedCard)->values("postfixValue");

	for(int i=0; i<operators.size(); ++i){
		this->operators->at(i)->setCurrentIndex(this->operators->at(i)->findText(operators.at(i)));
		this->values->at(i)->setCurrentIndex(this->values->at(i)->findText(values.at(i)));

		if(postfixOperators.at(i) == "+"){
			plusses->at(i)->setChecked(true);
		} else {
			minusses->at(i)->setChecked(true);
		}

		this->postfixValues->at(i)->setCurrentIndex(this->postfixValues->at(i)->findText(postfixValues.at(i)));
	}
}

void CardEvaluator::updateSelectedCard(){
	QString text = "Card ";
	text.append(selectedCard->objectName()).append("\n");
	text.append("Color: ").append(information->value(selectedCard)->value("color"));

	QList<QString> operators = information->value(selectedCard)->values("operator");
	QList<QString> values = information->value(selectedCard)->values("value");
	QList<QString> postfixOperators = information->value(selectedCard)->values("postfixOperator");
	QList<QString> postfixValues = information->value(selectedCard)->values("postfixValue");

	text.append("\nValue: ");
	for(int i=operators.size()-1; i>=0; --i){
		text.append(operators.at(i));
		text.append(values.at(i));
		text.append(postfixOperators.at(i));
		text.append(postfixValues.at(i));
		if(i != 0){
			text.append("\n");
		}
	}

	selectedCard->setText(text);
}

void CardEvaluator::deleteCard(){
	int index = cards->indexOf(selectedCard);
	cards->remove(index);
	delete selectedCard;
	if(index > 0){
		selectedCard = cards->at(index-1);
	} else {
		addCard();
	}
}
