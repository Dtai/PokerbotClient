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

#include "cardeditwidget.hpp"
#include "ui_cardeditwidget.h"

#include <QDebug>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include "../card/cardexpressionvalidator.hpp"

using namespace poker;
using namespace graphicsView;

namespace poker
{
namespace view
{
namespace
{
void setComboBoxExpressionFromData(QComboBox * combobox, const QString & expression)
{
	int pos = combobox->findData(expression);
	if(pos == -1)
	{
		pos = combobox->count();
		combobox->addItem(expression, expression);
	}

	combobox->setCurrentIndex(pos);
}
}

CardEditWidget::CardEditWidget(QWidget *parent)
	:QWidget(parent),
		ui(new Ui::CardEditWidget),
		_drawer(CardDrawer::Instance()),
		_rankValidator(poker::card::CardExpressionValidator::createRankParser(this))
{
	ui->setupUi(this);
	ui->allExpressions->setModel(&_rankExpressionsModel);
	ui->allExpressions->setEditTriggers(QAbstractItemView::NoEditTriggers);

	// update the boxes and the connections
	fillComboBoxes();
	initialiseConnections();

	// set an empty card
	setCard(card());

	setValidCard(false);
}

CardEditWidget::~CardEditWidget()
{
	delete ui;
}

void CardEditWidget::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void CardEditWidget::setValidCard(bool isValid)
{
	_isValidCard = isValid;
	ui->cardDisplay->setEnabled(isValid);
}

void CardEditWidget::setCard(const Card & card)
{
	// update the card
	_card = card;

	// and fill the list box
	_rankExpressionsModel.clear();

	foreach(const QString & expr, card.rankExpressions())
		_rankExpressionsModel.appendRow(new QStandardItem(expr));


	// and set the layout data
	setComboBoxExpressionFromData(ui->suitExpression, card.suitExpression());


	redrawCard();
	setValidCard(true);
}


void CardEditWidget::fillComboBoxes()
{
	// fill the suit expression combobox
	ui->suitExpression->addItem(drawer()->unknownIcon(), "maakt niet uit", Card::Unknown());
	ui->suitExpression->addItem(drawer()->heartIcon(), "harten", Card::Hearts());
	ui->suitExpression->addItem(drawer()->spadeIcon(), "schoppen", Card::Spades());
	ui->suitExpression->addItem(drawer()->clubIcon(), "klaveren", Card::Clubs());
	ui->suitExpression->addItem(drawer()->diamondIcon(), "ruiten", Card::Diamonds());

	ui->suitExpression->setMyValidator(card::CardExpressionValidator::createSuitParser(this));
}

void CardEditWidget::initialiseConnections()
{
	connect(ui->suitExpression, SIGNAL(currentIndexChanged(int)), this, SLOT(dataToCard()));
	connect(ui->allExpressions, SIGNAL(clicked(QModelIndex)), this, SLOT(updateDeleteButton()));
	connect(ui->removeExpressionButton, SIGNAL(clicked()), this, SLOT(removeExpression()));
	connect(ui->addExpressionButton, SIGNAL(clicked()), this, SLOT(tryToAddExpression()));
}

void CardEditWidget::updateDeleteButton()
{
	ui->removeExpressionButton->setEnabled(true);
}

void CardEditWidget::removeExpression()
{
	QModelIndex i = ui->allExpressions->currentIndex();
	ui->allExpressions->model()->removeRow(i.row());
	ui->removeExpressionButton->setEnabled(false);

	dataToCard();
}

void CardEditWidget::redrawCard()
{
	ui->cardDisplay->setPixmap(drawer()->drawNormalCard(card()));
}

void CardEditWidget::dataToCard()
{
	// set the suit
	_card.setSuitExpression(ui->suitExpression->itemData(ui->suitExpression->currentIndex()).toString());

	_card.setRankExpressions(QStringList());

	// set the rank
	for(int i = 0; i < _rankExpressionsModel.rowCount(); i++)
		_card.addRankExpression(_rankExpressionsModel.item(i)->text());

	redrawCard();

	emit cardChanged();
}

void CardEditWidget::tryToAddExpression()
{
	// find the expression
	QString expr = ui->cutrExpressions->text();
	expr.remove(" ");
	if(expr == "" || expr.isEmpty())
		return;

	QString error;
	if(!_rankValidator->isValid(expr, &error))
	{
		QMessageBox::critical(0, "Error parsing expression", "Unable to parse expression: " + error);
		return;
	}

	_rankExpressionsModel.appendRow(new QStandardItem(expr));
	ui->cutrExpressions->clear();

	dataToCard();
}

}
}
