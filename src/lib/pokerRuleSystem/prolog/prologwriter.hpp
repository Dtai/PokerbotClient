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


#ifndef POKER_PROLOGWRITER_HPP
#define POKER_PROLOGWRITER_HPP

#include <ruleSystem/prolog/prologwriter.hpp>
#include <ruleSystem/util/macro.hpp>
#include "../card/cardexpressionvalidator.hpp"

namespace poker
{
namespace prolog
{

class PokerCodeInformation : public ruleSystem::PrologWriter::CodeInformation
{
public:
	static QString rankVarPrefix() { return ruleSystem::PrologWriter::CodeInformation::varPrefix() + "R"; }
	static QString suitVarPrefix() { return ruleSystem::PrologWriter::CodeInformation::varPrefix() + "S"; }

	PokerCodeInformation(int ruleNumber);
	~PokerCodeInformation();

	PtrVarGet(card::CardExpressionValidator, rankValidator);
	PtrVarGet(card::CardExpressionValidator, suitValidator);
};

} // namespace prolog
} // namespace poker

#endif // PROLOGWRITER_HPP
