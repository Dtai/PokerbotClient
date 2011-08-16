#ifndef CARDEVALUATOR_HPP
#define CARDEVALUATOR_HPP

#include <QWidget>

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
		void addColor();
		void addValue();
		void changePostfix();

private:
		Ui::CardEvaluator *ui;
		QVector<QString> postfixes;
};

#endif // CARDEVALUATOR_HPP
