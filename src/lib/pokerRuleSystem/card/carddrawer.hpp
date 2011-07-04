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

#ifndef CARDDRAWER_HPP
#define CARDDRAWER_HPP

#include <QPixmap>
#include <QIcon>
#include <ruleSystem/util/macro.hpp>
#include <ruleSystem/util/singleton.hpp>

namespace poker
{
	class Card;

	namespace graphicsView
	{
		class CardDrawer : public Singleton<CardDrawer>
		{
			friend class Singleton<CardDrawer>;

		private:
			CardDrawer();
			~CardDrawer();

		public:
			QPixmap drawNormalCard(const Card & card) const;
			QPixmap drawSmallCard(const Card & card) const;

			QSize smallCardSize(const Card & card) const;
			QSize normalCardSize(const Card & card) const;

		private:
			const QPixmap * cardPixmap(const Card & card) const;
			QSize cardSize(const Card & card, float scaleFactor) const;
			QPixmap drawCard(const Card & card, float scaleFactor) const;
			QPixmap DrawPixmapCard(const Card & card, float scaleFactor) const;
			QPixmap DrawTextCard(const Card & card, float scaleFactor) const;

			RefVarGetSet(bool, drawMatchEqual, DrawMatchEqual);
			RefVarGetSet(bool, drawValueMatch,drawValueMatch);

			QPixmap _heart;
			QPixmap _diamond;
			QPixmap _spade;
			QPixmap _club;
			QPixmap _unknown;
			RefVarGet(QIcon, heartIcon);
			RefVarGet(QIcon, diamondIcon);
			RefVarGet(QIcon, spadeIcon);
			RefVarGet(QIcon, clubIcon);
			RefVarGet(QIcon, unknownIcon);
		};
	}
}

#endif // CARDDRAWER_HPP
