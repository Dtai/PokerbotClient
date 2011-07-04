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

#ifndef CARDEDITWIDGET_HPP
#define CARDEDITWIDGET_HPP

#include <QWidget>
#include <QStandardItemModel>
#include <ruleSystem/util/macro.hpp>


#include "../card/card.hpp"
#include "../card/carddrawer.hpp"
#include "../card/cardexpressionvalidator.hpp"

namespace poker
{
	namespace view
	{
		namespace Ui
		{
			class CardEditWidget;
		}

		class CardEditWidget : public QWidget
		{
			Q_OBJECT

		public:
			explicit CardEditWidget(QWidget *parent = 0);
			~CardEditWidget();

			const QPixmap & cardPixmap() const;

			void setValidCard(bool isValid);

		public slots:
			void setCard(const poker::Card & card);

		private slots:
			void updateDeleteButton();
			void removeExpression();
			void dataToCard();
			void tryToAddExpression();

		protected:
			void changeEvent(QEvent *e);

		private:
			void fillComboBoxes();
			void initialiseConnections();
			void redrawCard();



		signals:
			void cardChanged();

		private:
			Ui::CardEditWidget *ui;
			RefVarGet(poker::Card, card);
			PtrVarGet(poker::graphicsView::CardDrawer, drawer);
			SimpleVarGet(bool, isValidCard);
			QStandardItemModel _rankExpressionsModel;

			poker::card::CardExpressionValidator * _rankValidator;
		};
	}
}

#endif // CARDEDITWIDGET_HPP
