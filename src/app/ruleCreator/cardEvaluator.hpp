#ifndef CARDEVALUATOR_HPP
#define CARDEVALUATOR_HPP

#include <QWidget>
#include <QPushButton>

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
		void addColor();
		void addValue();
		void changePostfix();

private:
		Ui::CardEvaluator *ui;
		QVector<QString> postfixes;
		QPushButton *selectedCard;
};

#endif // CARDEVALUATOR_HPP
