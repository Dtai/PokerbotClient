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

#include "rulewidget.hpp"
#include "ui_rulewidget.h"
#include <QBitmap>
#include <QDebug>
#include <QIcon>

using namespace ruleSystem::graphicsView;

namespace
{
	const QIcon & UpIcon()
	{
		static QIcon upIcon;

		if(!upIcon.isNull())
			return upIcon;

		upIcon = QIcon(QPixmap(":/arrow_up"));
		upIcon.addPixmap(QPixmap(":/arrow_up_gray"), QIcon::Disabled);

		return upIcon;
	}

	const QIcon & DownIcon()
	{
		static QIcon downIcon;

		if(!downIcon.isNull())
			return downIcon;

		downIcon = QIcon(QPixmap(":/arrow_down"));
		downIcon.addPixmap(QPixmap(":/arrow_down_gray"), QIcon::Disabled);

		return downIcon;
	}

	const QIcon & DeleteIcon()
	{
		static QIcon delIcon;

		if(!delIcon.isNull())
			return delIcon;

		delIcon = QIcon(QPixmap(":/delete"));

		return delIcon;
	}
}

RuleWidget::RuleWidget(QWidget *parent)
	: QFrame(parent),
	_scene(new ElementGraphicsScene(this)),
	_position(-1),
	ui(new Ui::RuleWidget)
{
	ui->setupUi(this);

	// initialize the graphics scene / view
	ui->graphicsView->setMinimumHeight(RuleWidget::MinimumHeight());
	ui->graphicsView->setScene(scene());
	ui->graphicsView->setAcceptDrops(true);
	connect(scene(), SIGNAL(sceneRectChanged(QRectF)), this, SLOT(onSceneRectChanged()));
	connect(scene(), SIGNAL(changed(QList<QRectF>)), this, SLOT(onSceneRectChanged()));

	connect(ui->arrowDown, SIGNAL(clicked()), this, SLOT(onMoveDownwardClicked()));
	connect(ui->arrowUp, SIGNAL(clicked()), this, SLOT(onMoveUpwardClicked()));
	connect(ui->deleteRule, SIGNAL(clicked()), this, SLOT(onDeleteRuleClicked()));
	connect(scene(), SIGNAL(changed(QList<QRectF>)), this, SLOT(onRuleChanged()));

	// initialize the buttons
	ui->arrowDown->setIcon(DownIcon());
	ui->arrowUp->setIcon(UpIcon());
	ui->deleteRule->setIcon(DeleteIcon());
}

void RuleWidget::onSceneRectChanged()
{
	scene()->setSceneRect(scene()->itemsBoundingRect());
	ui->graphicsView->setSceneRect(scene()->sceneRect().adjusted(-RuleWidget::Margin(), -RuleWidget::Margin(), RuleWidget::Margin(), RuleWidget::Margin()));
}

RuleWidget::~RuleWidget()
{
	delete ui;
}

void RuleWidget::setPosition(int position)
{
	_position = position;
	ui->ruleNumber->setText(QString(tr("Rule %1:")).arg(position+1));

}

void RuleWidget::setDeleteEnabled(bool isEnabled)
{
	ui->deleteRule->setEnabled(isEnabled);
}

void RuleWidget::setDownEnabled(bool isEnabled)
{
	ui->arrowDown->setEnabled(isEnabled);
}

void RuleWidget::setUpEnabled(bool isEnabled)
{
	ui->arrowUp->setEnabled(isEnabled);
}

void RuleWidget::onMoveUpwardClicked()
{
	emit moveUpward(position());
}

void RuleWidget::onMoveDownwardClicked()
{
	emit moveDownward(position());
}

void RuleWidget::onDeleteRuleClicked()
{
	emit deleteRule(position());
}

void RuleWidget::onRuleChanged()
{
	emit ruleChanged(position());
}
