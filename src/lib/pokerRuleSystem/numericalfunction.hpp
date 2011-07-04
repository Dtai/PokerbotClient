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

#ifndef NUMERICALFUNCTION_HPP
#define NUMERICALFUNCTION_HPP

#include <ruleSystem/calculator.hpp>
#include "pokerrulesystem.hpp"

namespace poker
{
	namespace function
	{
		struct AddFunctor
		{
			const static QString UniqueName() { return "numADD"; }
			const static ruleSystem::Type OutputType() { return type::numericalType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "plus"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & elements) const;
		};
		struct SubtractFunctor
		{
			const static QString UniqueName() { return "numSUB"; }
			const static ruleSystem::Type OutputType() { return type::numericalType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "min"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & elements) const;
		};
		struct DivideFunctor
		{
			const static QString UniqueName() { return "numDIV"; }
			const static ruleSystem::Type OutputType() { return type::numericalType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "gedeeld door"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & elements) const;
		};
		struct MultiplyFunctor
		{
			const static QString UniqueName() { return "numMUL"; }
			const static ruleSystem::Type OutputType() { return type::numericalType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "maal"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & elements) const;
		};
		struct InvertFunctor
		{
			const static QString UniqueName() { return "numINV"; }
			const static ruleSystem::Type OutputType() { return type::numericalType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "inv"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & elements) const;
		};
	}
}

#endif // NUMERICALFUNCTION_HPP
