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

#include "card.hpp"

namespace poker
{
	Card::Card(const QString & suitExpression, const QString & rankExpression)
		: _suitExpression(suitExpression),
			_rankExpressions(QStringList() << rankExpression)
	{
	}

	Card::Card(const QString & suitExpression, const QStringList & rankExpressions)
		: _suitExpression(suitExpression),
		_rankExpressions(rankExpressions)
	{
	}

	bool Card::operator==(const Card & other) const
	{
		return other.suitExpression() == suitExpression() && other.rankExpressions() == rankExpressions();
	}

	bool Card::operator!=(const Card & other) const
	{
		return !operator==(other);
	}

	void Card::addRankExpression(const QString & expression)
	{
		_rankExpressions << expression;
	}

	void Card::set(const QString & suitExpression, const QStringList & rankExpressions)
	{
		setSuitExpression(suitExpression);
		setRankExpressions(rankExpressions);
	}

	QDataStream & operator<<(QDataStream & stream, const Card & card)
	{
		stream << card.suitExpression() << card.rankExpressions();
		return stream;
	}

	QDataStream &operator>>(QDataStream & stream, Card & card)
	{
		QString suitExpression;
		QStringList rankExpressions;

		stream >> suitExpression >> rankExpressions;
		card.set(suitExpression, rankExpressions);

		return stream;
	}
}
