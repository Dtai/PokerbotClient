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

#include "suitparser.hpp"

#include <boost/regex.hpp>
#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/classic_assign_actor.hpp>
#include <boost/bind.hpp>
#include "card.hpp"


using namespace boost::spirit;
using namespace boost;

namespace poker {
namespace card {

namespace
{
struct mySuitParser : public grammar<mySuitParser>
{
	mySuitParser(SuitObject * suitObject) : _suitObject(suitObject) {}

	template <typename ScannerT> struct definition
	{
		definition(mySuitParser const& self)
		{
			Formula = Constant | Variable;

			Constant =
					 ( str_p(qPrintable(Card::Hearts()))
					 | str_p(qPrintable(Card::Clubs()))
					 | str_p(qPrintable(Card::Diamonds()))
					 | str_p(qPrintable(Card::Spades())))[boost::bind(&mySuitParser::setConstant, &self, _1, _2)];

			Variable =
					(range_p('a', 'z') >> * ( range_p('a', 'z')
																	 | range_p('A', 'Z')))[boost::bind(&mySuitParser::setVariable, &self, _1, _2)];
		}

		rule<ScannerT> Formula, Constant, Variable;
		rule<ScannerT> const& start() const { return Formula; };
	};

private:
	void setConstant(const char * first, const char * last) const
	{
		if(_suitObject)
			_suitObject->constant = QString::fromStdString(std::string(first, last));
	}
	void setVariable(const char * first, const char * last) const
	{
		if(_suitObject)
			_suitObject->variableName = QString::fromStdString(std::string(first, last));
	}

public:
	SuitObject * _suitObject;
};
}

int SuitParser::parse(const QString & expression, SuitObject & object)
{
	std::string s = qPrintable(expression);
	mySuitParser p(&object);
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

int SuitParser::parse(const QString & expression)
{
	SuitObject object;
	return parse(expression, object);
}



}
}

