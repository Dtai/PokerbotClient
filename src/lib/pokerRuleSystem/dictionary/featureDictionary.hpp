#ifndef FEATUREDICTIONARY_HPP
#define FEATUREDICTIONARY_HPP

#include <QString>
#include <QObject>

namespace poker
{

class AllCards: public QObject {
	Q_OBJECT
public:
	AllCards():QObject(){;}
	static const QString name() {return tr("all cards");}
	static const QString devName() {return "allekaarten";}
};

class TableCards : public QObject
{
	Q_OBJECT
public:
	TableCards():QObject(){;}
	static const QString name() {return tr("table cards");}
	static const QString devName() {return "tafelkaarten";}
};

class HandCards : public QObject
{
	Q_OBJECT
public:
	HandCards():QObject(){;}
	static const QString name() {return tr("hand cards");}
	static const QString devName() {return "handkaarten";}
};

class AmountRaises : public QObject
{
	Q_OBJECT
public:
	AmountRaises():QObject(){;}
	static const QString name() {return tr("amount raises");}
	static const QString devName() {return "aantalraises";}
};
}

#endif // FEATUREDICTIONARY_HPP
