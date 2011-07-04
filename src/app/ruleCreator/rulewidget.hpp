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

#ifndef RULEWIDGET_HPP
#define RULEWIDGET_HPP

#include <QFrame>
#include <ruleSystem/util/macro.hpp>
#include <ruleSystem/graphicsView/elementgraphicsscene.hpp>

namespace Ui
{
	class RuleWidget;
}

class RuleWidget : public QFrame
{
	Q_OBJECT

public:
	static const float MinimumHeight() { return 200; }
	static const float Margin() { return 10; }


	explicit RuleWidget(QWidget *parent = 0);
	~RuleWidget();


	void setPosition(int position);
	private slots:

	void onSceneRectChanged();

signals:
	void moveUpward(int rule);
	void moveDownward(int rule);
	void deleteRule(int rule);
	void ruleChanged(int rule);

public slots:
	void setUpEnabled(bool isEnabled);
	void setDownEnabled(bool isEnabled);
	void setDeleteEnabled(bool isEnabled);
	void onMoveUpwardClicked();
	void onMoveDownwardClicked();
	void onDeleteRuleClicked();
	void onRuleChanged();

private:
	PtrVarGet(ruleSystem::graphicsView::ElementGraphicsScene, scene);
	SimpleVarGet(int, position);
	Ui::RuleWidget *ui;
};

#endif // RULEWIDGET_HPP
