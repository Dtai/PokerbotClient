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

#define BOOST_SPIRIT_USE_OLD_NAMESPACE

#include "rankparser.hpp"
#include "regex.h"
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/classic_assign_actor.hpp>
#include <boost/bind.hpp>

#include <QDebug>

using namespace boost::spirit;
using namespace boost;

namespace poker {
namespace card {

namespace
{
struct myRankParser : public grammar<myRankParser>
{
	myRankParser(RankObject * rankObject) : _rankObject(rankObject) {}

	template <typename ScannerT> struct definition
	{
		definition(myRankParser const& self)
		{
			Formula = Comparation >> (Constant | (Variable >> ! ((str_p("+")|str_p("-")) >> Number )));

			Comparation =
					(str_p(">=")
					| str_p(">")
					| str_p("=")
					| str_p("<=")
					| str_p("<"))[boost::bind(&myRankParser::setComparation, &self, _1, _2)];


			Constant =
					( str_p("10")
					| str_p("2")
					| str_p("3")
					| str_p("4")
					| str_p("5")
					| str_p("6")
					| str_p("7")
					| str_p("8")
					| str_p("9")
					| str_p("J")
					| str_p("Q")
					| str_p("K")
					| str_p("A"))[boost::bind(&myRankParser::setConstant, &self, _1, _2)];

			Variable =
					(range_p('a', 'z') >> * ( range_p('a', 'z')
																	 | range_p('A', 'Z')))[boost::bind(&myRankParser::setVariable, &self, _1, _2)];


			Number =
					(range_p('1', '9')
					| str_p("10")
					| str_p("11")
					| str_p("12"))[boost::bind(&myRankParser::setIsNumerical, &self, _1, _2)];
		}

		rule<ScannerT> Formula, Comparation, Constant, Variable, Number;
		rule<ScannerT> const& start() const { return Formula; };
	};

private:
	void setComparation(const char * first, const char * last) const
	{
		if(_rankObject)
			_rankObject->comparator = QString::fromStdString(std::string(first, last));
	}
	void setConstant(const char * first, const char * last) const
	{
		if(_rankObject)
			_rankObject->constant = QString::fromStdString(std::string(first, last));
	}
	void setVariable(const char * first, const char * last) const
	{
		if(_rankObject)
			_rankObject->variableName = QString::fromStdString(std::string(first, last));
	}
	void setIsNumerical(const char *, const char *) const
	{
		_rankObject->hasNumericalOperation = true;
	}

public:
	RankObject * _rankObject;
};
}

RankObject::RankObject() : hasNumericalOperation(false) {}




int RankParser::parse(const QString & expression, RankObject & object)
{
	std::string s = qPrintable(expression);

	myRankParser p(&object);
	parse_info<const char *> pInfo = boost::spirit::parse(s.c_str(), p, space_p);

	if(pInfo.full)
	{
		if(!object.variableName.isEmpty())
			allVariables() << object.variableName;

		return -1;
	}
	else
		return pInfo.stop - s.c_str();
}

int RankParser::parse(const QString &expression)
{
	RankObject object;
	return parse(expression, object);
}




}
}

