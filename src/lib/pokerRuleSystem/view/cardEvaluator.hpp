#ifndef CARDEVALUATOR_HPP
#define CARDEVALUATOR_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "cardEvaluatorCreator.hpp"
#include "../card/card.hpp"
#include <ruleSystem/constant.hpp>

namespace Ui {
class CardEvaluator;
}

class CardEvaluator : public QWidget
{
        Q_OBJECT

public:
		CardEvaluator(QList<poker::Card> givenCards, ruleSystem::Constant *constant, QWidget *parent = 0);
		~CardEvaluator();
		QList<poker::Card> cards() const;
		bool returnValue;
private slots:
		void addCard();
		void deleteCard();
		void addValue();
		void changePostfix();
		void selectCard();
		void redrawSelectedCard();
		void deleteValue();
		void save();

private:
		ruleSystem::Constant *constant;
		Ui::CardEvaluator *ui;
		QPushButton *selectedCard;
		QVBoxLayout *layoutCards;
		QVBoxLayout *layoutValues;
		QVector<QPushButton*> *_cards;
		QMap<QPushButton*, QMap<QString, QString>*> *information;
		bool cardExists;
		bool separatedColors;
		bool separatedValues;
		CardEvaluatorCreator *creator;

		QMap<QPushButton*, int> *suitIndex;
		QMap<QPushButton*, QVector<QComboBox*>*> *operators;
		QMap<QPushButton*, QVector<QComboBox*>*> *values;
		QMap<QPushButton*, QVector<QComboBox*>*> *postfixValues;
		QMap<QPushButton*, QVector<QPushButton*>*> *deleteValues;

		void loadInformationFromSelectedCard();
		void updateSelectedCard();
		QMap<QString, QString> *getCurrentInformation();
		void updateOwnVariables();
		void initValues();
		void showValues();
		void hideValues();
		void colorizeCards();
		void deleteValuesOfCard(QPushButton *card);
		int newCardName();
		void insertGivenCards(QList<poker::Card>);
		void parse(QStringList values, QStringList *ops, QStringList *vals, QStringList *postVals);
		template <class T>
		void deleteValuesOfMap(QMap<QPushButton*, QVector<T*>*> *map);
		bool areCorrectVariables();
		bool isCorrectValue(QString value);
		bool isCorrectSuit(QString suit);
		bool isCorrectVariable(QString var);
signals:
		void ready();
};

#endif // CARDEVALUATOR_HPP
