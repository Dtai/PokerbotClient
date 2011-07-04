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


#ifndef CARDEXPRESSIONVALIDATOR_HPP
#define CARDEXPRESSIONVALIDATOR_HPP

#include <QString>
#include <QRegExp>
#include "../view/validcombobox.hpp"
#include <ruleSystem/util/macro.hpp>
#include "simpleparser.hpp"

namespace poker
{
	namespace card
	{
		class CardExpressionValidator : public QObject, public poker::view::ValidComboBox::MyValidator
		{
			Q_OBJECT

		private:
			CardExpressionValidator(SimpleParser * parser, QObject * parent = 0);

		public:
			static QRegExp varRegex() { return QRegExp("[a-z][a-zA-Z]*"); }

			~CardExpressionValidator();

			static CardExpressionValidator * createRankParser(QObject * parent = 0);
			static CardExpressionValidator * createSuitParser(QObject * parent = 0);

			virtual bool isValid(const QString & text, QString * errorMessage = 0) const;

		private:
			SimpleParser * _parser;
		};
	}
}



#endif // CARDEXPRESSIONVALIDATOR_HPP
