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

#include "rule_defaults.hpp"

namespace ruleSystem
{
	namespace defaults
	{
		namespace elementLayout
		{
			float xMargin()					{ return 5.0f; }
			float yMargin()					{ return 5.0f; }
			QSizeF minSize()				{ return QSizeF(70.0f, 22.0f); }
			float inputItemSpacing()		{ return 3.0f; }
			float roundness()				{ return 0.0f; }
			QBrush backgroundBrush()		{ return QBrush(Qt::white); }
			QPen textPen()					{ return QPen(QBrush(Qt::black), 1.0f);}
			QPen strokePen()				{ return QPen(QBrush(Qt::black), 1.0f);}
			QPen selectedStrokePen()		{ return QPen(QBrush(Qt::black), 2.0f);}
			QFont font()					{ static QFont f("Monospace"); f.setStyleHint(QFont::TypeWriter); f.setPointSize(8); return f; }
		}

		namespace elementGraphicsItem
		{
			QString mimeType()				{ return "app/rule-element"; }
			QString hotSpotMimeType() { return "app/rule-element-hotSpot"; }
		}
	}
}
