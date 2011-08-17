#ifndef CARDEVALUATOR_HPP
#define CARDEVALUATOR_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "cardEvaluatorCreator.hpp"

namespace Ui {
class CardEvaluator;
}

class CardEvaluator : public QWidget
{
        Q_OBJECT

public:
		CardEvaluator(QWidget *parent = 0);
		~CardEvaluator();
private slots:
		void addCard();
		void deleteCard();
		void addValue();
		void changePostfix();
		void selectCard();
		void redrawSelectedCard();

private:
		Ui::CardEvaluator *ui;
		QPushButton *selectedCard;
		QVBoxLayout *layoutCards;
		QVBoxLayout *layoutValues;
		QVector<QPushButton*> *cards;
		QMap<QPushButton*, QMap<QString, QString>*> *information;
		bool separatedColors;
		CardEvaluatorCreator *creator;

		QVector<QComboBox*> *operators;
		QVector<QComboBox*> *values;
		QVector<QRadioButton*> *minusses;
		QVector<QRadioButton*> *plusses;
		QVector<QComboBox*> *postfixValues;
		QVector<bool> *separatedValues;

		void loadInformationFromSelectedCard();
		void updateSelectedCard();
		QMap<QString, QString> *getCurrentInformation();
		void updateOwnVariables();
};

#endif // CARDEVALUATOR_HPP
