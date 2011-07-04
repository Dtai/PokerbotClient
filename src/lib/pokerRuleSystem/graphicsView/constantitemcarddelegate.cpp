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

#include "constantitemcarddelegate.hpp"


#include <ruleSystem/constant.hpp>
#include <QPainter>
#include <QLabel>

#include "../view/editcardlistdialog.hpp"
#include "../pokerrulesystem.hpp"

#include "../card/carddrawer.hpp"
#include "../card/card.hpp"

using namespace ruleSystem;

namespace poker
{
	namespace graphicsView
	{
		namespace
		{
			CardDrawer * drawer() { return CardDrawer::Instance(); }

			Constant * toCardListConstant(Element * element)
			{
				Constant * c = element_cast<Constant>(element);
				if(c == 0 || c->type() != type::cardEquationType())
					return 0;

				return c;
			}
			QList<Card> getCards(Constant * c)
			{
				return c->value().value<QList<Card> >();
			}

			QSizeF cardSize(const QList<Card> & cards)
			{
				QSizeF s;
				foreach(const Card & c, cards)
				{
					QSizeF tmp = drawer()->smallCardSize(c);
					s.setHeight(tmp.height());
					s.rwidth() += tmp.width();
				}

				return s;
			}
		}

		ConstantItemCardDelegate::ConstantItemCardDelegate()
		{
		}

		QSizeF ConstantItemCardDelegate::sizeHint(Element * element) const
		{
			Constant * c = toCardListConstant(element);
			if(c == 0)
				return QSizeF();

			return cardSize(getCards(c));
		}

		void ConstantItemCardDelegate::paint(QPainter * painter, Element * element) const
		{
			Constant * c = toCardListConstant(element);
			if(c == 0)
				return;

			QList<Card> cards = getCards(c);
			float xPos = 0;

			for(int i = 0; i < cards.size(); i++)
			{
				QPixmap p = drawer()->drawSmallCard(cards.at(i));
				painter->drawPixmap(xPos, 0, p.width(), p.height(), p);

				xPos += p.width();
			}
		}


		bool ConstantItemCardDelegate::edit(Element * element, const QPointF & /*position*/) const
		{
			Constant * c = toCardListConstant(element);
			if(c == 0)
				return false;

			poker::view::EditCardListDialog * dlg = new view::EditCardListDialog(getCards(c));
			if(dlg->exec() == QDialog::Accepted)
			{
				c->setValue(QVariant::fromValue<QList<Card> >(dlg->cards()));
				return true;
			}
			else
				return false;
		}
	}
}
