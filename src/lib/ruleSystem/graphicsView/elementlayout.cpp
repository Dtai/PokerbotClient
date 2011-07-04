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

#include "elementlayout.hpp"
#include "elementgraphicsitem.hpp"
#include <QFontMetricsF>
#include "rule_defaults.hpp"
#include "elementitemdelegate.hpp"
#include <QDebug>

namespace ruleSystem
{
	namespace
	{
		QColor invert(const QColor & color)
		{
			return QColor(255-color.red(), 255-color.green(), 255-color.blue());
		}
	}

	namespace graphicsView
	{
		ElementLayout::ElementLayout(const QPixmap & connector, const QPixmap & selectedConnector, const QBrush & backgroundBrush)
			: _xMargin(defaults::elementLayout::xMargin()),
			_yMargin(defaults::elementLayout::yMargin()),
			_minSize(defaults::elementLayout::minSize()),
			_inputItemSpacing(defaults::elementLayout::inputItemSpacing()),
			_roundness(defaults::elementLayout::roundness()),
			_backgroundBrush(backgroundBrush),
			_selectedBackgroundBrush(invert(backgroundBrush.color())),
			_textPen(defaults::elementLayout::textPen()),
			_strokePen(defaults::elementLayout::strokePen()),
			_selectedStrokePen(defaults::elementLayout::selectedStrokePen()),
			_connector(connector),
			_selectedConnector(selectedConnector),
			_connectorLeftCenter(-_strokePen.widthF()/2.0f, -connector.height()/2.0f),
			_font(defaults::elementLayout::font())
		{
		}
	}
}
