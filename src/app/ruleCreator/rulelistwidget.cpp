/*******************************************************************
* Copyright (c) 2010 Thomas Fannes (thomasfannes@gmail.com)
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

#include "rulelistwidget.hpp"
#include <QVBoxLayout>
#include "rulewidget.hpp"
#include <QDebug>

RuleListWidget::RuleListWidget(QWidget *parent)
	: QWidget(parent),
	_ruleLayout(new QVBoxLayout),
	_autoDelete(false)
{
	_ruleLayout->setSpacing(10);

	delete layout();

	QVBoxLayout * l = new QVBoxLayout;
	setLayout(l);
	l->addLayout(_ruleLayout);
	l->addStretch(9);
	setObjectName("listSelector");
	setStyleSheet("#listSelector {background-color: black;}");

	updateRuleList();
}

void RuleListWidget::moveRuleUp(int rule)
{
	if(rule < 1)
		return;

	swapRules(rule-1, rule);
	updateRuleList();

}

void RuleListWidget::moveRuleDown(int rule)
{
	if(rule >= _ruleLayout->count()-1)
		return;

	swapRules(rule, rule+1);
	updateRuleList();
}

void RuleListWidget::insertRule(int rulePos)
{
	if(rulePos > _ruleLayout->count())
		rulePos = _ruleLayout->count();

	_ruleLayout->insertWidget(rulePos, createWidgetAt(rulePos));

	updateRuleList();

	emit numberOfRulesChanged(numberOfRules()-1);
}

void RuleListWidget::ruleContentChanged(int rule)
{
	if(rule != _ruleLayout->count()-1)
		return;

	updateRuleList();
}

void RuleListWidget::deleteRule(int rule)
{
	if(rule < 0 || rule >= _ruleLayout->count())
		return;

	delete _ruleLayout->itemAt(rule)->widget();

	updateRuleList();

	emit numberOfRulesChanged(numberOfRules()-1);
}

void RuleListWidget::clearAll()
{
	while(_ruleLayout->count() != 0)
		delete _ruleLayout->itemAt(0)->widget();

	updateRuleList();

	emit numberOfRulesChanged(numberOfRules()-1);
}

void RuleListWidget::onDeleteRule(int rule)
{
	if(isAutoDeleteOn())
		deleteRule(rule);
	else
		emit ruleWantsDeletion(rule);
}


void RuleListWidget::swapRules(int pos1, int pos2)
{
	Q_ASSERT(pos1 < pos2);

	if(pos1 < 0 || pos2 < 0 || pos1 > _ruleLayout->count() || pos2 > _ruleLayout->count())
		return;

	RuleWidget * w2 = qobject_cast<RuleWidget*>(_ruleLayout->takeAt(pos2)->widget());
	RuleWidget * w1 = qobject_cast<RuleWidget*>(_ruleLayout->takeAt(pos1)->widget());

	Q_ASSERT(w1 && w2);

	_ruleLayout->insertWidget(pos1, w2);
	_ruleLayout->insertWidget(pos2, w1);

	w2->setPosition(pos1);
	w1->setPosition(pos2);
}

void RuleListWidget::updateRuleList()
{
	// create a first element if necessary
	if(_ruleLayout->count() == 0)
		_ruleLayout->addWidget(createWidgetAt(0));

	// create a last element if necessary
	RuleWidget * last = qobject_cast<RuleWidget*>(_ruleLayout->itemAt(_ruleLayout->count()-1)->widget());
	Q_ASSERT(last != 0);
	if(!last->scene()->isEmpty())
	{
		_ruleLayout->addWidget(createWidgetAt(_ruleLayout->count()));
		emit numberOfRulesChanged(numberOfRules() - 1);
	}

	for(int i = 0; i < _ruleLayout->count(); i++)
	{
		RuleWidget * w = qobject_cast<RuleWidget*>(_ruleLayout->itemAt(i)->widget());
		Q_ASSERT(w != 0);

		w->setPosition(i);

		w->setUpEnabled(i != 0 && i != _ruleLayout->count()-1);
		w->setDownEnabled(i < _ruleLayout->count() - 2);
		w->setDeleteEnabled(i != _ruleLayout->count() - 1);
	}

	emit rulesChanged();
}

RuleWidget * RuleListWidget::createWidgetAt(int position)
{
	RuleWidget * w = new RuleWidget(this);
	w->setPosition(position);
	w->show();

	connect(w, SIGNAL(deleteRule(int)), this, SLOT(onDeleteRule(int)));
	connect(w, SIGNAL(moveDownward(int)), this, SLOT(moveRuleDown(int)));
	connect(w, SIGNAL(moveUpward(int)), this, SLOT(moveRuleUp(int)));
	connect(w, SIGNAL(ruleChanged(int)), this, SLOT(ruleContentChanged(int)));

	return w;
}

int RuleListWidget::numberOfRules() const
{
	return _ruleLayout->count();
}

ruleSystem::graphicsView::ElementGraphicsScene * RuleListWidget::sceneForRule(int ruleNumber) const
{
	if(ruleNumber < 0 || ruleNumber >= _ruleLayout->count())
		return 0;

	RuleWidget * w = qobject_cast<RuleWidget*>(_ruleLayout->itemAt(ruleNumber)->widget());
	if(w == 0)
		return 0;

	return w->scene();
}
