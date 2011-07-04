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

#include "pokeractiondelegate.hpp"
#include "pokeraction.hpp"
#include "elementhelper.hpp"
#include <QSizeF>
#include <QFontMetricsF>
#include <QPainter>
#include "view/editpokeractiondialog.hpp"

using namespace ruleSystem;
using namespace ruleSystem::graphicsView;

namespace poker
{
	namespace graphicsView
	{
		PokerActionDelegate::PokerActionDelegate()
		{
		}

		QSizeF PokerActionDelegate::sizeHint(Element * element) const
		{
			PokerAction * ac = element_cast<PokerAction>(element);

			if(ac == 0)
				return DefaultItemDelegate::sizeHint(element);

			QFontMetricsF f(font());
			return QSizeF(f.width(ac->pokerActionName()), f.height()) + QSizeF(1,0);
		}

		void PokerActionDelegate::paint(QPainter * painter, Element * element) const
		{
			PokerAction * ac = element_cast<PokerAction>(element);

			if(ac == 0)
				return;

			QRectF drawRct(QPointF(), sizeHint(element));

			painter->setFont(font());
			painter->drawText(drawRct.adjusted(1,0,0,0), ac->pokerActionName());
		}

		bool PokerActionDelegate::edit(Element * element, const QPointF & /*position*/) const
		{
			PokerAction * ac = element_cast<PokerAction>(element);
			if(ac == 0)
				return false;

			view::EditPokerActionDialog * dlg = new view::EditPokerActionDialog(ac->pokerActionName());
			if(dlg->exec() == QDialog::Accepted)
			{
				ac->setPokerActionName(dlg->value());
				return true;
			}

			return false;
		}

	}
}
