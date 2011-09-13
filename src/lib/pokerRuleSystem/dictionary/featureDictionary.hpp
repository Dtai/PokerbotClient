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

class TableCards : public QObject {
	Q_OBJECT
public:
	TableCards():QObject(){;}
	static const QString name() {return tr("table cards");}
	static const QString devName() {return "tafelkaarten";}
};

class HandCards : public QObject {
	Q_OBJECT
public:
	HandCards():QObject(){;}
	static const QString name() {return tr("hand cards");}
	static const QString devName() {return "handkaarten";}
};

class AmountRaises : public QObject {
	Q_OBJECT
public:
	AmountRaises():QObject(){;}
	static const QString name() {return tr("amount raises");}
	static const QString devName() {return "aantalraises";}
};

class MaximumRaise : public QObject{
	Q_OBJECT
public:
	MaximumRaise() : QObject(){}
	static const QString name(){return tr("maximum raise");}
	static const QString devName(){return "maximumraise";}
};

class MinimumRaise : public QObject{
	Q_OBJECT
public:
	MinimumRaise() : QObject(){}
	static const QString name(){return tr("minimum raise");}
	static const QString devName(){return "minimumraise";}
};

class MaximumProfit : public QObject{
	Q_OBJECT
public:
	MaximumProfit() : QObject(){}
	static const QString name(){return tr("maximum profit");}
	static const QString devName(){return "maximalewinst";}
};

class ActivePlayersWithMoney : public QObject{
	Q_OBJECT
public:
	ActivePlayersWithMoney() : QObject(){}
	static const QString name(){return tr("active players with money");}
	static const QString devName(){return "actievespelersmetgeld";}
};

class ActivePlayers : public QObject{
	Q_OBJECT
public:
	ActivePlayers() : QObject(){}
	static const QString name(){return tr("active players");}
	static const QString devName(){return "actievespelers";}
};

class PotSize : public QObject{
	Q_OBJECT
public:
	PotSize() : QObject(){}
	static const QString name(){return tr("pot size");}
	static const QString devName(){return "potgrootte";}
};

class Balance : public QObject{
	Q_OBJECT
public:
	Balance() : QObject(){}
	static const QString name(){return tr("balance");}
	static const QString devName(){return "saldo";}
};

class Shortage : public QObject{
	Q_OBJECT
public:
	Shortage() : QObject(){}
	static const QString name(){return tr("shortage");}
	static const QString devName(){return "tekort";}
};

class IsPreFlop : public QObject{
	Q_OBJECT
public:
	IsPreFlop() : QObject(){}
	static const QString name(){return tr("is pre flop");}
	static const QString devName(){return "ispreflop";}
};

class IsFlop : public QObject{
	Q_OBJECT
public:
	IsFlop() : QObject(){}
	static const QString name(){return tr("is flop");}
	static const QString devName(){return "isflop";}
};

class IsTurn : public QObject{
	Q_OBJECT
public:
	IsTurn() : QObject(){}
	static const QString name(){return tr("is turn");}
	static const QString devName(){return "isturn";}
};

class IsRiver : public QObject{
	Q_OBJECT
public:
	IsRiver() : QObject(){}
	static const QString name(){return tr("is river");}
	static const QString devName(){return "isriver";}
};

class IsPostFlop : public QObject{
	Q_OBJECT
public:
	IsPostFlop() : QObject(){}
	static const QString name(){return tr("is post flop");}
	static const QString devName(){return "ispostflop";}
};

class IsBigBlind : public QObject{
	Q_OBJECT
public:
	IsBigBlind() : QObject(){}
	static const QString name(){return tr("is big blind");}
	static const QString devName(){return "isbigblind";}
};

class IsSmallBlind : public QObject{
	Q_OBJECT
public:
	IsSmallBlind() : QObject(){}
	static const QString name(){return tr("is small blind");}
	static const QString devName(){return "issmallblind";}
};

class IsButton : public QObject{
	Q_OBJECT
public:
	IsButton() : QObject(){}
	static const QString name(){return tr("is button");}
	static const QString devName(){return "isbutton";}
};

}

#endif // FEATUREDICTIONARY_HPP
