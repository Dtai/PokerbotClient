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


#include "cardexpressionvalidator.hpp"
#include "rankparser.hpp"
#include "suitparser.hpp"
#include <QRegExp>
#include <cassert>

namespace poker
{
	namespace card
	{
		CardExpressionValidator::CardExpressionValidator(SimpleParser * parser, QObject * parent)
			: QObject(parent),
				_parser(parser)
		{
			assert(parser);
		}

		CardExpressionValidator::~CardExpressionValidator()
		{
			delete _parser;
		}

		CardExpressionValidator * CardExpressionValidator::createRankParser(QObject * parent)
		{
			return new CardExpressionValidator(new RankParser, parent);
		}

		CardExpressionValidator * CardExpressionValidator::createSuitParser(QObject * parent)
		{
			return new CardExpressionValidator(new SuitParser, parent);
		}

		bool CardExpressionValidator::isValid(const QString & text, QString * errorMessage) const
		{
			std::size_t val = _parser->parse(text);

			if(val != -1)
			{
				if(errorMessage)
					(*errorMessage) = QString(tr("error at location %1")).arg(val);
				return false;
			}
			else
				return true;
		}
	}
}
