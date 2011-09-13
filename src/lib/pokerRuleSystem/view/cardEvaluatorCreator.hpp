#ifndef CARDEVALUATORCREATOR_HPP
#define CARDEVALUATORCREATOR_HPP

#include <QStringList>
#include <QComboBox>
#include <QRadioButton>
#include <QPushButton>

class CardEvaluatorCreator
{

public:
		CardEvaluatorCreator();
		~CardEvaluatorCreator();
		QComboBox *createOperators(QWidget *parent);
		QComboBox *createValues(QWidget *parent);
		QComboBox *createPostfixValues(QWidget *parent);
		QPushButton *createDeleteValue(QWidget *parent, QString name);
		void addValue(QString value);

private:
		QStringList *operators;
		QStringList *values;
		QStringList *ownValues;
		QStringList *postfixValues;

		void initOperators();
		void initValues();
		void initOwnValues();
		void initPostfixValues();
};

#endif // CARDEVALUATORCREATOR_HPP
