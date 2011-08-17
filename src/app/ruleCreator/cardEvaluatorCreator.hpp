#ifndef CARDEVALUATORCREATOR_HPP
#define CARDEVALUATORCREATOR_HPP

#include <QStringList>
#include <QComboBox>
#include <QRadioButton>

class CardEvaluatorCreator
{

public:
		CardEvaluatorCreator();
		~CardEvaluatorCreator();
		QComboBox *createOperators(QWidget *parent);
		QComboBox *createValues(QWidget *parent);
		QComboBox *createPostfixValues(QWidget *parent);
		QRadioButton *createRadioButtonPlus(QWidget *parent);
		QRadioButton *createRadioButtonMinus(QWidget *parent);

private:
		QStringList *operators;
		QStringList *values;
		QStringList *postfixValues;

		void initOperators();
		void initValues();
		void initPostfixValues();
};

#endif // CARDEVALUATORCREATOR_HPP
