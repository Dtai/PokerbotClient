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

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <ruleSystem/graphicsView/elementfactory.hpp>
#include <ruleSystem/graphicsView/elementgraphicsitem.hpp>
#include <ruleSystem/graphicsView/elementgraphicsscene.hpp>
#include <ruleSystem/constant.hpp>
#include <ruleSystem/function.hpp>

#include <pokerRuleSystem/pokerrulesystem.hpp>
#include <pokerRuleSystem/pokeraction.hpp>
#include <pokerRuleSystem/types.hpp>



using namespace ruleSystem;
using namespace ruleSystem::graphicsView;
using namespace poker;
//using namespace poker::graphicsView;

namespace
{
	ElementFactory * factory() { return ElementFactory::Instance(); }
}


MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	scene = new ElementGraphicsScene(this);
	ui->graphicsView->setScene(scene);
	ui->graphicsView->setSceneRect(QRectF(-100,-100, 200, 200));

	poker::initialise();

	Constant * r = new Constant(type::booleanType(), QVariant(true));
	Element * f = new Function(CalculatorCreator<function::BoolEqualFunctor>::Create());
	Element * f2 = new Function(CalculatorCreator<function::ORFunctor>::Create());
	Element * f3 = new Function(CalculatorCreator<function::BoolEqualFunctor>::Create());
	f->setInput("0", r);
	f->setInput("1", f2);

	f2->setInput("0", f3);
	a = new PokerAction("fold");
	a->setInput(Action::InputPosition(), f);

	scene->addItem(factory()->createGraphicsItem(a));
}

MainWindow::~MainWindow()
{
	delete a;
	delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
		QMainWindow::changeEvent(e);
	switch (e->type())
	{
		case QEvent::LanguageChange:
				ui->retranslateUi(this);
				break;
		default:
				break;
		}
}


