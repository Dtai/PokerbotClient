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

#ifndef TYPES_HPP
#define TYPES_HPP

#include <ruleSystem/type.hpp>

namespace type
{
	ruleSystem::Type numericalType();
	ruleSystem::Type cardListType();
	ruleSystem::Type cardEquationType();
}

namespace poker
{
	struct BoolName
	{
		const static QString EqualName()					   { return "booleq"; }
		const static QString LesserThanName()				 { return "boollt"; }
		const static QString LesserThanOrEqualName() { return "boolltoreq"; }
		const static QString GreaterThanName()			 { return "boolgt"; }
		const static QString GreaterThanOrEqualName(){ return "boolgtoreq"; }
		const static ruleSystem::Type InputType()		 { return type::booleanType(); }
	};

	struct NumName
	{
		const static QString EqualName()				     { return "numeq"; }
		const static QString LesserThanName()			   { return "numlt"; }
		const static QString LesserThanOrEqualName() { return "numltoreq"; }
		const static QString GreaterThanName()			 { return "numgt"; }
		const static QString GreaterThanOrEqualName(){ return "numgtoreq"; }
		const static ruleSystem::Type InputType()		 { return type::numericalType(); }
	};

	struct CardName
	{
		const static QString EqualName()				  { return "cardeq"; }
		const static ruleSystem::Type InputType()	{ return type::cardListType(); }
	};
}

#endif // TYPES_HPP
