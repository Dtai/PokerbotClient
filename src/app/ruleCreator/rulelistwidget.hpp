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


#ifndef RULELISTWIDGET_HPP
#define RULELISTWIDGET_HPP

#include <QWidget>
#include <ruleSystem/util/macro.hpp>
#include <ruleSystem/graphicsView/elementgraphicsscene.hpp>

class QVBoxLayout;
class RuleWidget;

class RuleListWidget : public QWidget
{
	Q_OBJECT
public:
	explicit RuleListWidget(QWidget *parent = 0);

	bool isAutoDeleteOn() const									{ return _autoDelete; }
	void setAutoDeleteStatus(bool autoDelete)		{ _autoDelete = autoDelete; }

	int numberOfRules() const;
	ruleSystem::graphicsView::ElementGraphicsScene * sceneForRule(int ruleNumber) const;

public slots:
	void moveRuleUp(int rule);
	void moveRuleDown(int rule);
	void ruleContentChanged(int rule);
	void deleteRule(int rule);
	void insertRule(int rulePos);
	void clearAll();

private slots:
	void onDeleteRule(int rule);

signals:
	void ruleWantsDeletion(int rule);
	void numberOfRulesChanged(int numberOfValidRules);
	void rulesChanged();

private:
	void swapRules(int pos1, int pos2);
	void updateRuleList();
	RuleWidget * createWidgetAt(int position);

private:
	QVBoxLayout * _ruleLayout;
	bool _autoDelete;
};

#endif // RULELISTWIDGET_HPP
