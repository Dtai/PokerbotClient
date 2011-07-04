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

#ifndef ELEMENTLAYOUT_HPP
#define ELEMENTLAYOUT_HPP

#include "../util/macro.hpp"
#include <QRectF>
#include <QSize>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QPointF>
#include <QFont>

namespace ruleSystem
{
	namespace graphicsView
	{
		class ElementGraphicsItem;

		class ElementLayout
		{
		public:
			ElementLayout(const QPixmap & connector = QPixmap(), const QPixmap & selectedConnector = QPixmap(), const QBrush & backgroundBrush = QBrush(Qt::white));

		private:
			// spacing details
			SimpleVarGetSet(float, xMargin, XMargin);
			SimpleVarGetSet(float, yMargin, YMargin);
			SimpleVarGetSet(QSizeF, minSize, MinSize);
			SimpleVarGetSet(float, inputItemSpacing, InputItemSpacing);

			// drawing details
			SimpleVarGetSet(float, roundness, Roundness);
			RefVarGetSet(QBrush, backgroundBrush, BackgroundBrush);
			RefVarGetSet(QBrush, selectedBackgroundBrush, SelectedBackgroundBrush);
			RefVarGetSet(QPen, textPen, TextPen);
			RefVarGetSet(QPen, strokePen, StrokePen);
			RefVarGetSet(QPen, selectedStrokePen, SelectedStrokePen);
			RefVarGetSet(QPixmap, connector, Connector);
			RefVarGetSet(QPixmap, selectedConnector, SelectedConnector);
			RefVarGetSet(QPointF, connectorLeftCenter, ConnectorLeftCenter);
			RefVarGetSet(QFont, font, Font);
		};
	}
}

#endif // ELEMENTLAYOUT_HPP
