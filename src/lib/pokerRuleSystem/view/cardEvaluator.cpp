#include "cardEvaluator.hpp"
#include "ui_cardEvaluator.h"

#include <QGraphicsColorizeEffect>

CardEvaluator::CardEvaluator(QList<poker::Card> givenCards, ruleSystem::Constant *constant, QWidget *parent)
        : QWidget(parent),
		  ui(new Ui::CardEvaluator)
{
		ui->setupUi(this);
		setAttribute(Qt::WA_DeleteOnClose);

		this->constant = constant;
		returnValue = false;

		connect(ui->addValue, SIGNAL(clicked()), this, SLOT(addValue()));
		connect(ui->newCard, SIGNAL(clicked()), this, SLOT(addCard()));
		connect(ui->deleteCard, SIGNAL(clicked()), this, SLOT(deleteCard()));
		connect(ui->color, SIGNAL(editTextChanged(QString)), this, SLOT(redrawSelectedCard()));
		connect(ui->save, SIGNAL(clicked()), this, SLOT(save()));
		connect(ui->cancel, SIGNAL(clicked()), this, SLOT(deleteLater()));

		layoutValues = new QVBoxLayout;
		layoutCards = new QVBoxLayout;
		_cards = new QVector<QPushButton*>();
		information = new QMap<QPushButton*, QMap<QString, QString>*>();

		operators = new QMap<QPushButton*, QVector<QComboBox*>*>();
		values = new QMap<QPushButton*, QVector<QComboBox*>*>();
		postfixValues = new QMap<QPushButton*, QVector<QComboBox*>*>();
		deleteValues = new QMap<QPushButton*, QVector<QPushButton*>*>();

		cardExists = false;
		separatedColors = false;
		separatedValues = false;

		creator = new CardEvaluatorCreator();

		insertGivenCards(givenCards);
}

CardEvaluator::~CardEvaluator(){
	delete ui;
	delete layoutCards;
	delete layoutValues;
	delete creator;

	deleteValuesOfMap(operators);
	deleteValuesOfMap(values);
	deleteValuesOfMap(postfixValues);
	deleteValuesOfMap(deleteValues);

	QList<QMap<QString, QString>*> list = information->values();
	for(int i=0; i<list.count(); ++i){
		delete list.at(i);
	}
	delete information;

	for(int i=0; i<_cards->count(); ++i){
		delete _cards->at(i);
	}
	delete _cards;
}

template <class T>
void CardEvaluator::deleteValuesOfMap(QMap<QPushButton*, QVector<T*>*> *map){
	QList<QVector<T*>*> list = map->values();
	for(int i=0; i<list.count(); ++i){
		for(int j=0; j<list.at(i)->count(); ++j){
			delete list.at(i)->at(j);
		}
	}
	delete map;
}

void CardEvaluator::parse(QStringList values, QStringList *ops, QStringList *vals, QStringList *postOps, QStringList *postVals){
	foreach(QString s, values){
		QString op = "";
		QString val = "";
		QString postOp = "";
		QString postVal = "";

		if(s.at(1) == '='){
			op = s.mid(0, 2);
			if(s.at(2).isDigit() || s.at(2) == 'J' || s.at(2) == 'Q' || s.at(2) == 'K' || s.at(2) == 'A'){
				val = s.at(2);
			} else {
				int i = 2;
				while(s.at(i) != '+' && s.at(i) != '-'){
					val.append(s.at(i));
					++i;
				}
				postOp.append(s.at(i));
				i++;
				postVal = s.mid(i);
			}

		} else {
			op = s.mid(0, 1);
			if(s.at(1).isDigit() || s.at(1) == 'J' || s.at(1) == 'Q' || s.at(1) == 'K' || s.at(1) == 'A'){
				val = s.at(1);
			} else {
				int i = 1;
				while(s.at(i) != '+' && s.at(i) != '-'){
					val.append(s.at(i));
					++i;
				}
				postOp.append(s.at(i));
				i++;
				postVal = s.mid(i);
			}
		}

		ops->append(op);
		vals->append(val);
		postOps->append(postOp);
		postVals->append(postVal);
	}
}

void CardEvaluator::parse(QStringList values, QStringList *ops, QStringList *vals, QStringList *postVals){
	foreach(QString s, values){
		QString op = "";
		QString val = "";
		QString postVal = "";

		if(s.at(1) == '='){
			op = s.mid(0, 2);
			if(s.at(2).isDigit() || s.at(2) == 'J' || s.at(2) == 'Q' || s.at(2) == 'K' || s.at(2) == 'A'){
				val = s.at(2);
			} else {
				int i = 2;
				while(i<s.count() && s.at(i) != '+' && s.at(i) != '-'){
					val.append(s.at(i));
					++i;
				}
				postVal = s.mid(i);
			}

		} else {
			op = s.mid(0, 1);
			if(s.at(1).isDigit() || s.at(1) == 'J' || s.at(1) == 'Q' || s.at(1) == 'K' || s.at(1) == 'A'){
				val = s.at(1);
			} else {
				int i = 1;
				while(i<s.count() && s.at(i) != '+' && s.at(i) != '-'){
					val.append(s.at(i));
					++i;
				}
				postVal = s.mid(i);
			}
		}

		ops->append(op);
		vals->append(val);
		postVals->append(postVal);
	}
}


void CardEvaluator::insertGivenCards(QList<poker::Card> givenCards){
	for(int i=0; i<givenCards.size(); ++i){
		QString color = givenCards.at(i).suitExpression();
		QStringList values = givenCards.at(i).rankExpressions();

		QStringList *ops = new QStringList();
		QStringList *vals = new QStringList();
		QStringList *postVals = new QStringList();

		parse(values, ops, vals, postVals);

		addCard();
		ui->color->setCurrentIndex(ui->color->findText(color));
		for(int i=0; i<values.size(); ++i){
			operators->value(selectedCard)->at(i)->setCurrentIndex(operators->value(selectedCard)->at(i)->findText(ops->at(i)));
			if(this->values->value(selectedCard)->at(i)->findText(vals->at(i)) == -1){
				this->values->value(selectedCard)->at(i)->addItem(vals->at(i));
			}
			this->values->value(selectedCard)->at(i)->setCurrentIndex(this->values->value(selectedCard)->at(i)->findText(vals->at(i)));

			postfixValues->value(selectedCard)->at(i)->setCurrentIndex(postfixValues->value(selectedCard)->at(i)->findText(postVals->at(i)));
			if(i != values.size()-1){
				addValue();
			}
		}

		updateSelectedCard();
	}
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
	} else {
		postfixValues->value(selectedCard)->at(index)->setDisabled(true);
	}
}

void CardEvaluator::addValue(){
	operators->value(selectedCard)->append(creator->createOperators(ui->valuesScroll));
	values->value(selectedCard)->append(creator->createValues(ui->valuesScroll));
	postfixValues->value(selectedCard)->append(creator->createPostfixValues(ui->valuesScroll));
	postfixValues->value(selectedCard)->last()->setCurrentIndex(3); //TODO magic variable
	deleteValues->value(selectedCard)->append(creator->createDeleteValue(ui->valuesScroll, QString::number(operators->value(selectedCard)->size()-1)));

	QComboBox *op = operators->value(selectedCard)->last();
	QComboBox *val = values->value(selectedCard)->last();
	QComboBox *postVal = postfixValues->value(selectedCard)->last();
	QPushButton *del = deleteValues->value(selectedCard)->last();

	QHBoxLayout *newVal = new QHBoxLayout();
	newVal->addWidget(op);
	newVal->addWidget(val);
	newVal->addWidget(postVal);
	newVal->addWidget(del);

	layoutValues->addLayout(newVal);
	QWidget *viewport = new QWidget;
	viewport->setLayout(layoutValues);
	ui->valuesScroll->setWidget(viewport);

	val->setObjectName(QString::number(values->value(selectedCard)->size()-1));
	connect(val, SIGNAL(editTextChanged(QString)), this, SLOT(changePostfix()));
	connect(op, SIGNAL(currentIndexChanged(int)), this, SLOT(redrawSelectedCard()));
	connect(val, SIGNAL(editTextChanged(QString)), this, SLOT(redrawSelectedCard()));
	connect(postVal, SIGNAL(currentIndexChanged(int)), this, SLOT(redrawSelectedCard()));
	connect(del, SIGNAL(clicked()), this, SLOT(deleteValue()));

	redrawSelectedCard();
}

void CardEvaluator::deleteValue(){
	int index = sender()->objectName().toInt();
	operators->value(selectedCard)->at(index)->deleteLater();
	values->value(selectedCard)->at(index)->deleteLater();
	postfixValues->value(selectedCard)->at(index)->deleteLater();

	operators->value(selectedCard)->remove(index);
	values->value(selectedCard)->remove(index);
	postfixValues->value(selectedCard)->remove(index);
	deleteValues->value(selectedCard)->remove(index);

	sender()->deleteLater();
	redrawSelectedCard();
}

void CardEvaluator::deleteValuesOfCard(QPushButton *card){
	for(int i=0; i<operators->value(card)->size(); ++i){
		operators->value(card)->at(i)->deleteLater();
		values->value(card)->at(i)->deleteLater();
		postfixValues->value(card)->at(i)->deleteLater();
		deleteValues->value(card)->at(i)->deleteLater();
	}

	operators->remove(card);
	values->remove(selectedCard);
	postfixValues->remove(selectedCard);
	deleteValues->remove(selectedCard);
}

int CardEvaluator::newCardName(){
	for(int i=0; i<_cards->size(); ++i){
		bool exists = false;
		foreach(QPushButton *card, *_cards){
			if(card->objectName().toInt() == i){
				exists = true;
			}
		}
		if(!exists){
			return i;
		}
	}
	return _cards->size();
}

void CardEvaluator::addCard(){
	if(cardExists){
		updateOwnVariables();
	}
	QPushButton *btn = new QPushButton("Card " + QString::number(newCardName()) + ":\n", ui->cards);
	btn->setObjectName(QString::number(newCardName()));
	connect(btn, SIGNAL(clicked()), this, SLOT(selectCard()));

	layoutCards->addWidget(btn);
	QWidget *viewport = new QWidget;
	viewport->setLayout(layoutCards);
	ui->cards->setWidget(viewport);
	_cards->append(btn);

	hideValues();

	selectedCard = btn;
	cardExists = true;
	initValues();
	redrawSelectedCard();
	colorizeCards();
}

void CardEvaluator::hideValues(){
	if(cardExists){
		for(int i=0; i<operators->value(selectedCard)->size(); ++i){
			operators->value(selectedCard)->at(i)->setVisible(false);
			values->value(selectedCard)->at(i)->setVisible(false);
			postfixValues->value(selectedCard)->at(i)->setVisible(false);
			deleteValues->value(selectedCard)->at(i)->setVisible(false);
		}
	}
}

void CardEvaluator::showValues(){
	if(cardExists){
		for(int i=0; i<operators->value(selectedCard)->size(); ++i){
			operators->value(selectedCard)->at(i)->setVisible(true);
			values->value(selectedCard)->at(i)->setVisible(true);
			postfixValues->value(selectedCard)->at(i)->setVisible(true);
			deleteValues->value(selectedCard)->at(i)->setVisible(true);
		}
	}
}

void CardEvaluator::initValues(){
	operators->insert(selectedCard, new QVector<QComboBox*>());
	values->insert(selectedCard, new QVector<QComboBox*>());
	postfixValues->insert(selectedCard,  new QVector<QComboBox*>());
	deleteValues->insert(selectedCard, new QVector<QPushButton*>());
	addValue();
}

void CardEvaluator::selectCard(){
	updateOwnVariables();
	hideValues();
	selectedCard = qobject_cast<QPushButton*>(sender());
	showValues();
	loadInformationFromSelectedCard();
	colorizeCards();
}

void CardEvaluator::colorizeCards(){
	foreach(QPushButton *card, *_cards){
		QGraphicsColorizeEffect *ce = new QGraphicsColorizeEffect(card);
		ce->setColor(Qt::darkGray);
		card->setGraphicsEffect(ce);
	}

	QGraphicsColorizeEffect *ce = new QGraphicsColorizeEffect(selectedCard);
	ce->setColor(Qt::blue);
	selectedCard->setGraphicsEffect(ce);
}

void CardEvaluator::updateOwnVariables(){
	if(ui->color->findText(ui->color->currentText()) == -1){
		if(!separatedColors){
			ui->color->insertSeparator(ui->color->count());
			separatedColors = true;
		}
		ui->color->addItem(ui->color->currentText());
	}

	for(int i=0; i<values->value(selectedCard)->size(); ++i){
		if(values->value(selectedCard)->at(i)->findText(values->value(selectedCard)->at(i)->currentText()) == -1){
			if(!separatedValues){
				foreach(QVector<QComboBox*> *v, values->values()){
					foreach(QComboBox *comboBox, *v){
						comboBox->insertSeparator(comboBox->count());
						separatedValues = true;
					}
				}
			}
			foreach(QVector<QComboBox*> *v, values->values()){
				foreach(QComboBox *comboBox, *v){
					comboBox->addItem(values->value(selectedCard)->at(i)->currentText());
				}
			}
			creator->addValue(values->value(selectedCard)->at(i)->currentText());
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
			result->insertMulti("postfixValue", postfixValues->value(selectedCard)->at(i)->currentText());
		} else {
			result->insertMulti("postfixValue", "");
		}
	}

	return result;
}

void CardEvaluator::loadInformationFromSelectedCard(){
	ui->color->setCurrentIndex(ui->color->findText(information->value(selectedCard)->value("color")));

	QList<QString> operators = information->value(selectedCard)->values("operator");
	QList<QString> values = information->value(selectedCard)->values("value");
	QList<QString> postfixValues = information->value(selectedCard)->values("postfixValue");

	for(int i=0; i<operators.size(); ++i){
		this->operators->value(selectedCard)->at(i)->setCurrentIndex(this->operators->value(selectedCard)->at(i)->findText(operators.at(i)));
		this->values->value(selectedCard)->at(i)->setCurrentIndex(this->values->value(selectedCard)->at(i)->findText(values.at(i)));
		this->postfixValues->value(selectedCard)->at(i)->setCurrentIndex(this->postfixValues->value(selectedCard)->at(i)->findText(postfixValues.at(i)));
	}
}

void CardEvaluator::updateSelectedCard(){
	QString text = "Card ";
	text.append(selectedCard->objectName()).append("\n");
	text.append("Color: ").append(information->value(selectedCard)->value("color"));

	text.append("\nValue: ");
	for(int i=0; i<operators->value(selectedCard)->size(); ++i){
		text.append(operators->value(selectedCard)->at(i)->currentText());
		text.append(values->value(selectedCard)->at(i)->currentText());
		text.append(postfixValues->value(selectedCard)->at(i)->currentText());

		if(i != operators->value(selectedCard)->size()-1){
			text.append("\n");
		}
	}

	selectedCard->setText(text);
}

void CardEvaluator::deleteCard(){
	int index = _cards->indexOf(selectedCard);
	_cards->remove(index);
	deleteValuesOfCard(selectedCard);
	delete selectedCard;
	if(_cards->size() > 0){
		int newIndex = (index-1<0) ? index+1 : index-1;
		selectedCard = _cards->at(newIndex);
		colorizeCards();
	} else {
		cardExists = false;
		addCard();
	}
	showValues();
}

QList<poker::Card> CardEvaluator::cards() const{
	QList<poker::Card> *cards = new QList<poker::Card>();

	for(int i=0; i<_cards->size(); ++i){
		QString color = information->value(_cards->at(i))->value("color");
		QList<QString> operators = information->value(_cards->at(i))->values("operator");
		QList<QString> values = information->value(_cards->at(i))->values("value");
		QList<QString> postfixValues = information->value(_cards->at(i))->values("postfixValue");

		QStringList ranks;
		for(int i=0; i<operators.size(); ++i){
			QString rank = operators.at(i);
			rank.append(values.at(i));
			rank.append(postfixValues.at(i));
			ranks.append(rank);
		}

		poker::Card c;
		c.setSuitExpression(color);
		c.setRankExpressions(ranks);
		cards->append(c);
	}

	return *cards;
}

void CardEvaluator::save(){
	constant->setValue(QVariant::fromValue<QList<poker::Card> >(cards()));
	returnValue = true;
	emit ready();
	close();
}
