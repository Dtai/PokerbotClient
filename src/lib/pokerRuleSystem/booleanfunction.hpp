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

#ifndef BOOLEANFUNCTION_HPP
#define BOOLEANFUNCTION_HPP

#include <ruleSystem/calculator.hpp>
#include "pokerrulesystem.hpp"

namespace poker
{
	namespace function
	{
		struct ORFunctor
		{
			const static QString UniqueName() { return "boolOR"; }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "or"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const;
		};
		struct ANDFunctor
		{
			const static QString UniqueName() { return "boolAND"; }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "and"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const;
		};
		struct NOTFunctor
		{
			const static QString UniqueName() { return "boolNOT"; }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "not"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const;
		};
		struct XORFunctor
		{
			const static QString UniqueName() { return "boolXOR"; }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "exor"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const;
		};
		struct ContainsFunctor
		{
			const static QString UniqueName() {return "contains"; }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "bevat"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const;
		};
	}
}



#endif // BOOLEANFUNCTION_HPP
