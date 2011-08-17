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

		operators = new QMap<QPushButton*, QVector<QComboBox*>*>();
		values = new QMap<QPushButton*, QVector<QComboBox*>*>();
		plusses = new QMap<QPushButton*, QVector<QRadioButton*>*>();
		minusses = new QMap<QPushButton*, QVector<QRadioButton*>*>();
		postfixValues = new QMap<QPushButton*, QVector<QComboBox*>*>();

		cardExists = false;
		separatedColors = false;
		separatedValues = new QMap<QPushButton*, QVector<bool>*>();

		creator = new CardEvaluatorCreator();

		addCard();
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
		postfixValues->value(selectedCard)->at(index)->setEnabled(true);
		minusses->value(selectedCard)->at(index)->setEnabled(true);
		plusses->value(selectedCard)->at(index)->setEnabled(true);
	} else {
		postfixValues->value(selectedCard)->at(index)->setDisabled(true);
		minusses->value(selectedCard)->at(index)->setDisabled(true);
		plusses->value(selectedCard)->at(index)->setDisabled(true);
	}
}

void CardEvaluator::addValue(){
	operators->value(selectedCard)->append(creator->createOperators(ui->valuesScroll));
	values->value(selectedCard)->append(creator->createValues(ui->valuesScroll));
	plusses->value(selectedCard)->append(creator->createRadioButtonPlus(ui->valuesScroll));
	minusses->value(selectedCard)->append(creator->createRadioButtonMinus(ui->valuesScroll));
	postfixValues->value(selectedCard)->append(creator->createPostfixValues(ui->valuesScroll));
	separatedValues->value(selectedCard)->append(false);

	QComboBox *op = operators->value(selectedCard)->last();
	QComboBox *val = values->value(selectedCard)->last();
	QRadioButton *rbp = plusses->value(selectedCard)->last();
	QRadioButton *rbm = minusses->value(selectedCard)->last();
	QComboBox *postVal = postfixValues->value(selectedCard)->last();

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

	redrawSelectedCard();
}

void CardEvaluator::addCard(){
	if(cardExists){
		updateOwnVariables();
	}
	QPushButton *btn = new QPushButton("Card " + QString::number(cards->size()) + ":\n", ui->cards);
	btn->setObjectName(QString::number(cards->size()));
	connect(btn, SIGNAL(clicked()), this, SLOT(selectCard()));

	layoutCards->addWidget(btn);
	QWidget *viewport = new QWidget;
	viewport->setLayout(layoutCards);
	ui->cards->setWidget(viewport);
	cards->append(btn);

	hideValues();

	selectedCard = btn;
	cardExists = true;
	initValues();
	redrawSelectedCard();
}

void CardEvaluator::hideValues(){
	if(cardExists){
		for(int i=0; i<operators->value(selectedCard)->size(); ++i){
			operators->value(selectedCard)->at(i)->setVisible(false);
			values->value(selectedCard)->at(i)->setVisible(false);
			plusses->value(selectedCard)->at(i)->setVisible(false);
			minusses->value(selectedCard)->at(i)->setVisible(false);
			postfixValues->value(selectedCard)->at(i)->setVisible(false);
		}
	}
}

void CardEvaluator::showValues(){
	if(cardExists){
		for(int i=0; i<operators->value(selectedCard)->size(); ++i){
			operators->value(selectedCard)->at(i)->setVisible(true);
			values->value(selectedCard)->at(i)->setVisible(true);
			plusses->value(selectedCard)->at(i)->setVisible(true);
			minusses->value(selectedCard)->at(i)->setVisible(true);
			postfixValues->value(selectedCard)->at(i)->setVisible(true);
		}
	}
}

void CardEvaluator::initValues(){
	operators->insert(selectedCard, new QVector<QComboBox*>());
	values->insert(selectedCard, new QVector<QComboBox*>());
	plusses->insert(selectedCard, new QVector<QRadioButton*>());
	minusses->insert(selectedCard, new QVector<QRadioButton*>());
	postfixValues->insert(selectedCard,  new QVector<QComboBox*>());
	separatedValues->insert(selectedCard, new QVector<bool>());
	addValue();
}

void CardEvaluator::selectCard(){
	updateOwnVariables();
	hideValues();

	QString card = sender()->objectName();
	selectedCard = cards->at(card.toInt());
	showValues();
	loadInformationFromSelectedCard();
}

void CardEvaluator::updateOwnVariables(){
	if(!separatedColors){
		ui->color->insertSeparator(ui->color->count());
		separatedColors = true;
	}

	for(int i=0; i<values->value(selectedCard)->size(); ++i){
		if(!separatedValues->value(selectedCard)->at(i)){
			values->value(selectedCard)->at(i)->insertSeparator(values->value(selectedCard)->at(i)->count());
			separatedValues->value(selectedCard)->insert(i, true);
		}
	}

	if(ui->color->findText(ui->color->currentText()) == -1){
		ui->color->addItem(ui->color->currentText());
	}

	for(int i=0; i<values->value(selectedCard)->size(); ++i){
		if(values->value(selectedCard)->at(i)->findText(values->value(selectedCard)->at(i)->currentText()) == -1){
			values->value(selectedCard)->at(i)->addItem(values->value(selectedCard)->at(i)->currentText());
		}
	}
}

QMap<QString, QString> *CardEvaluator::getCurrentInformation(){
	QMap<QString, QString> *result = new QMap<QString, QString>();

	result->insert("color", ui->color->currentText());
	for(int i=0; i<operators->value(selectedCard)->size(); ++i){
		result->insertMulti("operator", operators->value(selectedCard)->at(i)->currentText());
		result->insertMulti("value", values->value(selectedCard)->at(i)->currentText());

		if(postfixValues->value(selectedCard)->at(i)->isEnabled()){
			if(minusses->value(selectedCard)->at(i)->isChecked()){
				result->insertMulti("postfixOperator", "-");
			} else {
				result->insertMulti("postfixOperator", "+");
			}
			result->insertMulti("postfixValue", postfixValues->value(selectedCard)->at(i)->currentText());
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
		this->operators->value(selectedCard)->at(i)->setCurrentIndex(this->operators->value(selectedCard)->at(i)->findText(operators.at(i)));
		this->values->value(selectedCard)->at(i)->setCurrentIndex(this->values->value(selectedCard)->at(i)->findText(values.at(i)));

		if(postfixOperators.at(i) == "+"){
			plusses->value(selectedCard)->at(i)->setChecked(true);
		} else {
			minusses->value(selectedCard)->at(i)->setChecked(true);
		}

		this->postfixValues->value(selectedCard)->at(i)->setCurrentIndex(this->postfixValues->value(selectedCard)->at(i)->findText(postfixValues.at(i)));
	}
}

void CardEvaluator::updateSelectedCard(){
	QString text = "Card ";
	text.append(selectedCard->objectName()).append("\n");
	text.append("Color: ").append(information->value(selectedCard)->value("color"));

//	QList<QString> operators = information->value(selectedCard)->values("operator");
//	QList<QString> values = information->value(selectedCard)->values("value");
//	QList<QString> postfixOperators = information->value(selectedCard)->values("postfixOperator");
//	QList<QString> postfixValues = information->value(selectedCard)->values("postfixValue");

	text.append("\nValue: ");
	for(int i=operators->value(selectedCard)->size()-1; i>=0; --i){
		text.append(operators->value(selectedCard)->at(i)->currentText());
		text.append(values->value(selectedCard)->at(i)->currentText());
		if(minusses->value(selectedCard)->at(i)->isEnabled()){
			if(minusses->value(selectedCard)->at(i)->isChecked()){
				text.append("-");
			}
			if(plusses->value(selectedCard)->at(i)->isChecked()){
				text.append("+");
			}
			text.append(postfixValues->value(selectedCard)->at(i)->currentText());
		}

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
