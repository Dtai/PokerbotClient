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

#include "validcombobox.hpp"
#include <QLineEdit>
#include <QDebug>

namespace poker
{
	namespace view
	{
		ValidComboBox::ValidComboBox(QWidget * parent)
			: QComboBox(parent),
			_lastValidIndex(0),
			_myValidator(0)
		{
			setInsertPolicy(QComboBox::NoInsert);

			setEditable(true);
			connect(lineEdit(), SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));
			connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(onActivated(int)));
		}

		void ValidComboBox::onEditingFinished()
		{
			QString txt = currentText();

			if(myValidator() && !myValidator()->isValid(txt))
			{
				// return to the last good position
				clearEditText();
				setCurrentIndex(_lastValidIndex);
				return;
			}

			int pos;
			// check whether we have this item
			if( (pos = findData(txt)) == -1 && (pos = findText(txt)) == -1)
			{
				// if not, add to the list
				pos = count();
				addItem(txt, txt);
			}

			// update the index
			setCurrentIndex(pos);
		}

		void ValidComboBox::onActivated(int index)
		{
			_lastValidIndex = index;
		}
	}
}
