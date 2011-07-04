/*******************************************************************
* Copyright (c) 2009 Thomas Fannes (thomasfannes@gmail.com)
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following
* conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************/

#ifndef CARD_HPP
#define CARD_HPP

#include <QMetaType>
#include <QDataStream>
#include <QStringList>
#include <ruleSystem/util/macro.hpp>

namespace poker
{
class Card
{
public:
	static const QString Unknown()		{ return "?"; }

	static const QString Hearts()			{ return "hearts"; }
	static const QString Diamonds()		{ return "diamonds"; }
	static const QString Clubs()			{ return "clubs"; }
	static const QString Spades()			{ return "spades"; }

	static const QString Two()				{ return "2"; }
	static const QString Three()			{ return "3"; }
	static const QString Four()				{ return "4"; }
	static const QString Five()				{ return "5"; }
	static const QString Six()				{ return "6"; }
	static const QString Seven()			{ return "7"; }
	static const QString Eight()			{ return "8"; }
	static const QString Nine()				{ return "9"; }
	static const QString Ten()				{ return "10"; }
	static const QString Jack()				{ return "J"; }
	static const QString Queen()			{ return "Q"; }
	static const QString King()				{ return "K"; }
	static const QString Ace()				{ return "A"; }

	static const QList<QString> allRanks()	{ return QList<QString>() << Two() << Three() << Four() << Five() << Six() << Seven() << Eight() << Nine() << Ten() << Jack() << Queen() << King() << Ace(); }
	static const QList<QString> allSuits()	{ return QList<QString>() << Hearts() << Diamonds() << Clubs() << Spades(); }

public:
	Card(const QString & suitExpression, const QString & rankExpression);
	Card(const QString & suitExpression = Unknown(), const QStringList & rankExpressions = QStringList());

	void set(const QString & suitExpression, const QStringList & rankExpressions);

	bool operator==(const Card & other) const;
	bool operator!=(const Card & other) const;

	void addRankExpression(const QString & expression);

private:
	SimpleVarGetSet(QString, suitExpression, SuitExpression);
	SimpleVarGetSet(QStringList, rankExpressions, RankExpressions);
};

QDataStream & operator<<(QDataStream & stream, const Card & card);
QDataStream & operator>>(QDataStream & stream, Card & card);
}


Q_DECLARE_METATYPE(poker::Card)
Q_DECLARE_METATYPE(QList<poker::Card>)


#endif // CARD_HPP
