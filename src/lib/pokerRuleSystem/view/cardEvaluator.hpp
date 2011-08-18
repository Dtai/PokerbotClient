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
		CardEvaluator(ruleSystem::Constant *c, QWidget *parent = 0);
		~CardEvaluator();
		QList<poker::Card> cards() const;
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
		ruleSystem::Constant *c;
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

		QMap<QPushButton*, QVector<QComboBox*>*> *operators;
		QMap<QPushButton*, QVector<QComboBox*>*> *values;
		QMap<QPushButton*, QVector<QRadioButton*>*> *minusses;
		QMap<QPushButton*, QVector<QRadioButton*>*> *plusses;
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
};

#endif // CARDEVALUATOR_HPP
