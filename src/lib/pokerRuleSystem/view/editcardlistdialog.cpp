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

#include "editcardlistdialog.hpp"
#include "ui_editcardlistdialog.h"
#include <QStandardItemModel>
#include <QDebug>

namespace poker
{
	namespace view
	{
		namespace
		{
			graphicsView::CardDrawer * drawer() { return graphicsView::CardDrawer::Instance(); }

			void setItemData(QStandardItem * item, const Card & card)
			{
				item->setData(QVariant::fromValue<Card>(card));
				item->setIcon(drawer()->drawNormalCard(card));
			}
		}


		EditCardListDialog::EditCardListDialog(const QList<Card> & cards)
			: QDialog(),
			ui(new Ui::EditCardListDialog),
			_model(new QStandardItemModel(this))
		{
			ui->setupUi(this);
			ui->cardList->setModel(_model);
			ui->cardList->setEditTriggers(QAbstractItemView::NoEditTriggers);

			connect(ui->cardList, SIGNAL(clicked(QModelIndex)), this, SLOT(cardActivated(QModelIndex)));
			connect(ui->cardEditor, SIGNAL(cardChanged()), this, SLOT(currentCardChanged()));
			connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(deleteSelectedCard()));
			connect(ui->btnInsert, SIGNAL(clicked()), this, SLOT(insertNewCard()));

			fillModel(cards);
		}

		EditCardListDialog::~EditCardListDialog()
		{
			delete ui;
		}

		void EditCardListDialog::changeEvent(QEvent *e)
		{
			QDialog::changeEvent(e);
			switch (e->type()) {
			case QEvent::LanguageChange:
				ui->retranslateUi(this);
				break;
			default:
				break;
			}
		}

		QList<Card> EditCardListDialog::cards() const
		{
			QList<Card> cards;

			for(int i = 0; i < _model->rowCount(); i++)
				cards << _model->item(i)->data().value<Card>();

			return cards;
		}


		void EditCardListDialog::cardActivated(const QModelIndex & index)
		{
			Card card = index.data(Qt::UserRole+1).value<Card>();
			ui->cardEditor->setCard(card);
		}

		void EditCardListDialog::currentCardChanged()
		{
			QModelIndex l = ui->cardList->currentIndex();

			if(!l.isValid())
				return;

			setItemData(_model->item(l.row()), ui->cardEditor->card());
		}

		void EditCardListDialog::fillModel(const QList<Card> & cards)
		{
			foreach(const Card & card, cards)
			{
				QStandardItem * it = new QStandardItem;
				setItemData(it, card);
				_model->appendRow(it);
			}

			// select the first card is possible
			if(cards.isEmpty())
			{
				ui->cardEditor->setValidCard(false);
			}
			else
			{
				ui->cardList->setCurrentIndex(_model->index(0, 0));
				cardActivated(_model->index(0,0));
			}
		}

		void EditCardListDialog::insertNewCard()
		{
			QModelIndex sel = ui->cardList->currentIndex();
			int row;


			if(sel.isValid())
				row = sel.row();
			else
				row = _model->rowCount();

			// create the new card
			QStandardItem * it = new QStandardItem;
			setItemData(it, Card());
			_model->insertRow(row, it);

			// select if
			ui->cardList->setCurrentIndex(_model->index(0, 0));
			cardActivated(_model->index(row, 0));

		}

		void EditCardListDialog::deleteSelectedCard()
		{
			QModelIndex sel = ui->cardList->currentIndex();

			if(!sel.isValid())
				return;

			_model->removeRow(sel.row());

			// any cards left
			if(_model->rowCount() != 0)
				// activate the current selected
				cardActivated(ui->cardList->currentIndex());
			else
				// disable the cards
				ui->cardEditor->setValidCard(false);
		}
	}
}
