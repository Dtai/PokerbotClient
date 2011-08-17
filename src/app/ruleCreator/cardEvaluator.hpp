#ifndef CARDEVALUATOR_HPP
#define CARDEVALUATOR_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

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
		void redrawCard();

private:
		Ui::CardEvaluator *ui;
		QVector<QString> postfixes;
		QPushButton *selectedCard;
		int numberOfCards;
		QVBoxLayout *layout;
		QVector<QPushButton*> *cards;
		QMap<QPushButton*, QMap<QString, QString>*> *information;

		void loadInformationFromSelectedCard();
		void updateInformationCurrentCard();
		QMap<QString, QString> *getCurrentInformation();
};

#endif // CARDEVALUATOR_HPP
