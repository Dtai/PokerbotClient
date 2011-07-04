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

#include "constantitembooldelegate.hpp"
#include <ruleSystem/constant.hpp>
#include "../view/editbooldialog.hpp"

using namespace ruleSystem;
using namespace ruleSystem::graphicsView;
using namespace poker::view;

namespace poker
{
	namespace graphicsView
	{
		bool ConstantItemBoolDelegate::edit(Element * element, const QPointF & /*position*/) const
		{
			Constant * c = element_cast<Constant>(element);
			if(c == 0) return false;

			EditBoolDialog * dlg = new EditBoolDialog(c->value().toBool());
			if(dlg->exec() == QDialog::Accepted)
			{
				c->setValue(QVariant(dlg->value()));
				return true;
			}
			else return false;
		}
	}
}
