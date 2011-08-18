#include "cardEvaluatorCreator.hpp"

CardEvaluatorCreator::CardEvaluatorCreator(){
	initOperators();
	initValues();
	initOwnValues();
	initPostfixValues();
}

CardEvaluatorCreator::~CardEvaluatorCreator(){

}

void CardEvaluatorCreator::initOperators(){
	operators = new QStringList();
	operators->append("=");
	operators->append("!=");
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
}

void CardEvaluatorCreator::initOwnValues(){
	ownValues = new QStringList();
}

void CardEvaluatorCreator::initPostfixValues(){
	postfixValues = new QStringList();
	postfixValues->append("0");
	postfixValues->append("1");
	postfixValues->append("2");
	postfixValues->append("3");
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

QRadioButton *CardEvaluatorCreator::createRadioButtonMinus(QWidget *parent){
	QRadioButton *result = new QRadioButton(parent);
	result->setText("+");
	result->setChecked(true);
	result->setDisabled(true);

	return result;
}

QRadioButton *CardEvaluatorCreator::createRadioButtonPlus(QWidget *parent){
	QRadioButton *result = new QRadioButton(parent);
	result->setText("-");
	result->setDisabled(true);

	return result;
}

QPushButton *CardEvaluatorCreator::createDeleteValue(QWidget *parent, QString name){
	QPushButton *result = new QPushButton("X", parent);
	result->setObjectName(name);

	return result;
}

void CardEvaluatorCreator::addValue(QString value){
	ownValues->append(value);
}
