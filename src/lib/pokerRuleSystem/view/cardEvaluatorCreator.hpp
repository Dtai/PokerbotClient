#ifndef CARDEVALUATORCREATOR_HPP
#define CARDEVALUATORCREATOR_HPP

#include <QObject>
#include <QStringList>
#include <QComboBox>
#include <QRadioButton>
#include <QPushButton>

class CardEvaluatorCreator : public QObject{
	Q_OBJECT
public:
		CardEvaluatorCreator(QObject *parent = 0);
		QComboBox *createOperators(QWidget *parent);
		QComboBox *createValues(QWidget *parent);
		QComboBox *createPostfixValues(QWidget *parent);
		QPushButton *createDeleteValue(QWidget *parent, QString name);
		void addValue(QString value);
		QString devNameSuitOfIndex(int index);

private:
		QStringList *devNameSuits;
		QStringList *suits;
		QStringList *operators;
		QStringList *values;
		QStringList *ownValues;
		QStringList *postfixValues;

		void initSuits();
		void initDevNameSuits();
		void initOperators();
		void initValues();
		void initOwnValues();
		void initPostfixValues();
		friend class CardEvaluator;
};

#endif // CARDEVALUATORCREATOR_HPP
