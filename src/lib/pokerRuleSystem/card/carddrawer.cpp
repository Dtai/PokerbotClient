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

#include "carddrawer.hpp"
#include <QPainter>
#include "card.hpp"
#include <QDebug>

namespace poker
{
	const static float ratio = 88.0f/63.0f;
	const static float abs_height = 88;

	const static float big_scale = 4;
	const static float small_scale = 0.5f;
	const static float rel_textHeight = 15;
	const static float rel_margin = 4;
	const static float rel_img_size = 36;
	const static float rel_suit_midY = abs_height - rel_img_size/2.0f-rel_margin;
	const static float rel_rank_midY = (rel_suit_midY - rel_margin*3)/2.0f + rel_margin;

	namespace graphicsView
	{
		CardDrawer::CardDrawer()
			:_drawMatchEqual(true),
			_drawValueMatch(true),
			_heart(":/card/heart"),
			_diamond(":/card/diamond"),
			_spade(":/card/spade"),
			_club(":/card/club"),
			_unknown(":/card/unknown"),
			_heartIcon(_heart),
			_diamondIcon(_diamond),
			_spadeIcon(_spade),
			_clubIcon(_club),
			_unknownIcon(_unknown)
		{
		}

		CardDrawer::~CardDrawer()
		{
		}

		QPixmap CardDrawer::drawCard(const Card & card, float scaleFactor) const
		{
			if(cardPixmap(card) == 0)
				return DrawTextCard(card, scaleFactor);
			else
				return DrawPixmapCard(card, scaleFactor);
		}

		QPixmap CardDrawer::DrawPixmapCard(const Card & card, float scaleFactor) const
		{
			QFont f;
			f.setPointSizeF(rel_textHeight*scaleFactor);
			const QPixmap * suit = cardPixmap(card);
			const QString txt = card.rankExpressions().isEmpty() ? "=?" : card.rankExpressions().join(";");

			QFontMetricsF mf(f);
			float textWidth = mf.width(txt);
			float textHeight = mf.height();
			float imgSize = rel_img_size*scaleFactor;

			float height = abs_height*scaleFactor;
			float width = qMax(qMax(imgSize, textWidth) + 2*rel_margin*scaleFactor, height/ratio);

			float imgStartX = width/2.0f - imgSize/2.0f;
			float imgStartY = (rel_suit_midY-rel_img_size/2.0f)*scaleFactor;
			float textX = width/2.0f - textWidth/2.0f;
			float textY = rel_rank_midY*scaleFactor - textHeight/2.0f;

			QPixmap pix(width, height);
			pix.fill(Qt::white);
			QPainter p(&pix);
			p.setPen(QPen(QBrush(Qt::black), 1));
			p.setFont(f);
			p.drawRect(0, 0, width-1 , height-1);



			p.drawText(textX, textY, textWidth, textHeight, Qt::AlignCenter, txt);
			p.drawPixmap(imgStartX, imgStartY, imgSize, imgSize, *suit);


			return pix;
		}

		QPixmap CardDrawer::DrawTextCard(const Card & card, float scaleFactor) const
		{
			QFont f;
			f.setPointSizeF(rel_textHeight*scaleFactor);
			const QString & suit = card.suitExpression();
			const QString txt = card.rankExpressions().isEmpty() ? "=?" : card.rankExpressions().join(";");

			QFontMetricsF mf(f);
			float textWidth_R = mf.width(txt);
			float textWidth_S = mf.width(suit);
			float textHeight = mf.height();
			float imgSize = rel_img_size*scaleFactor;

			float height = abs_height*scaleFactor;
			float width = qMax(qMax(textWidth_S, textWidth_R) + 2*rel_margin*scaleFactor, height/ratio);

			float imgStartX = width/2.0f - textWidth_S/2.0f;
			float imgStartY = rel_suit_midY*scaleFactor - textHeight/2.0f;
			float textX = width/2.0f - textWidth_R/2.0f;
			float textY = rel_rank_midY*scaleFactor - textHeight/2.0f;

			QPixmap pix(width, height);
			pix.fill(Qt::white);
			QPainter p(&pix);
			p.setPen(QPen(QBrush(Qt::black), 1));
			p.setFont(f);
			p.drawRect(0, 0, width-1 , height-1);

			p.drawText(textX, textY, textWidth_R, textHeight, Qt::AlignCenter, txt);
			p.drawText(imgStartX, imgStartY, textWidth_S, textHeight, Qt::AlignCenter, suit);

			return pix;
		}

		QPixmap CardDrawer::drawNormalCard(const Card & card) const
		{
			return drawCard(card, big_scale);
		}

		QPixmap CardDrawer::drawSmallCard(const Card & card) const
		{
			return drawCard(card, small_scale);
		}

		QSize CardDrawer::cardSize(const Card & card, float scaleFactor) const
		{
			QFont f;
			f.setPointSizeF(rel_textHeight*scaleFactor);
			const QString txt = card.rankExpressions().isEmpty() ? "=?" : card.rankExpressions().join(";");

			QFontMetricsF mf(f);
			float textWidth = mf.width(txt);
			float imgSize = rel_img_size*scaleFactor;

			float height = abs_height*scaleFactor;
			float width = qMax(qMax(imgSize, textWidth) + 2*rel_margin*scaleFactor, height/ratio);
			return QSize(width, height);
		}

		QSize CardDrawer::smallCardSize(const Card & card) const
		{
			return cardSize(card, small_scale);
		}

		QSize CardDrawer::normalCardSize(const Card & card) const
		{
			return cardSize(card, big_scale);
		}

		const QPixmap * CardDrawer::cardPixmap(const Card & card) const
		{
			if(card.suitExpression() == QString())
				return &_unknown;
			else if(card.suitExpression() == Card::Clubs())
				return &_club;
			else if(card.suitExpression() == Card::Diamonds())
				return &_diamond;
			else if(card.suitExpression() == Card::Hearts())
				return &_heart;
			else if(card.suitExpression() == Card::Spades())
				return &_spade;
			else
				return 0;
		}
	}
}
