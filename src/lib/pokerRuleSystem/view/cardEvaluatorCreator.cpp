#include "cardEvaluatorCreator.hpp"

CardEvaluatorCreator::CardEvaluatorCreator(QObject *parent) : QObject(parent){
	initSuits();
	initDevNameSuits();
	initOperators();
	initValues();
	initOwnValues();
	initPostfixValues();
}

QString CardEvaluatorCreator::devNameSuitOfIndex(int index){
	return devNameSuits->at(index);
}

void CardEvaluatorCreator::initDevNameSuits(){
	devNameSuits = new QStringList();
	devNameSuits->append("hearts");
	devNameSuits->append("spades");
	devNameSuits->append("clubs");
	devNameSuits->append("diamonds");
}

void CardEvaluatorCreator::initSuits(){
	suits = new QStringList();
	suits->append(tr("hearts"));
	suits->append(tr("spades"));
	suits->append(tr("clubs"));
	suits->append(tr("diamonds"));
}

void CardEvaluatorCreator::initOperators(){
	operators = new QStringList();
	operators->append("=");
	operators->append(">");
	operators->append(">=");
	operators->append("<");
	operators->append("<=");
}

void CardEvaluatorCreator::initValues(){
	values = new QStringList();
	values->append("2");
	values->append("3");
	values->append("4");
	values->append("5");
	values->append("6");
	values->append("7");
	values->append("8");
	values->append("9");
	values->append("10");
	values->append("J");
	values->append("Q");
	values->append("K");
	values->append("A");
	values->append("$var");
}

void CardEvaluatorCreator::initOwnValues(){
	ownValues = new QStringList();
}

void CardEvaluatorCreator::initPostfixValues(){
	postfixValues = new QStringList();
	postfixValues->append("-3");
	postfixValues->append("-2");
	postfixValues->append("-1");
	postfixValues->append("");
	postfixValues->append("+1");
	postfixValues->append("+2");
	postfixValues->append("+3");
}

QComboBox *CardEvaluatorCreator::createOperators(QWidget *parent){
	QComboBox *result = new QComboBox(parent);
	result->addItems(*operators);

	return result;
}

QComboBox *CardEvaluatorCreator::createValues(QWidget *parent){
	QComboBox *result = new QComboBox(parent);
	result->addItems(*values);
	result->setEditable(true);

	if(ownValues->size() > 0){
		result->insertSeparator(result->count());
		result->addItems(*ownValues);
	}

	return result;
}

QComboBox *CardEvaluatorCreator::createPostfixValues(QWidget *parent){
	QComboBox *result = new QComboBox(parent);
	result->addItems(*postfixValues);
	result->setDisabled(true);

	return result;
}

QPushButton *CardEvaluatorCreator::createDeleteValue(QWidget *parent, QString name){
	QPushButton *result = new QPushButton("X", parent);
	result->setFixedWidth(25);
	result->setObjectName(name);

	return result;
}

void CardEvaluatorCreator::addValue(QString value){
	ownValues->append(value);
}
