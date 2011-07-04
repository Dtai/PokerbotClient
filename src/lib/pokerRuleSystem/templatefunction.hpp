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

#ifndef TEMPLATEFUNCTION_HPP
#define TEMPLATEFUNCTION_HPP

#include <QString>
#include "types.hpp"
#include <ruleSystem/evaluatable.hpp>
#include <ruleSystem/calculator.hpp>
#include <ruleSystem/function.hpp>

namespace poker
{
	namespace function
	{
		template <class T, class N> struct EqualFunctor
		{
			const static QString UniqueName() { return N::EqualName(); }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "=="; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const
			{
				return vals[0]->calculateValue().value<T>() == vals[1]->calculateValue().value<T>();
			}
		};

		template <class T, class N> struct LesserThanFunctor
		{
			const static QString UniqueName() { return N::LesserThanName(); }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "<"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const
			{
				return vals[0]->calculateValue().value<T>() < vals[1]->calculateValue().value<T>();
			}
		};

		template <class T, class N> struct LesserThanOrEqualFunctor
		{
			const static QString UniqueName() { return N::LesserThanOrEqualName(); }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return "<="; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const
			{
				return vals[0]->calculateValue().value<T>() <= vals[1]->calculateValue().value<T>();
			}
		};

		template <class T, class N> struct GreaterThanFunctor
		{
			const static QString UniqueName() { return N::GreaterThanName(); }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return ">"; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const
			{
				return vals[0]->calculateValue().value<T>() > vals[1]->calculateValue().value<T>();
			}
		};

		template <class T, class N> struct GreaterThanOrEqualFunctor
		{
			const static QString UniqueName() { return N::GreaterThanOrEqualName(); }
			const static ruleSystem::Type OutputType() { return type::booleanType(); }
			const static ruleSystem::Function::InputList InputTypes();
			const static QString VisibleName() { return ">="; }
			QVariant operator()(const QList<ruleSystem::Evaluatable*> & vals) const
			{
				return vals[0]->calculateValue().value<T>() >= vals[1]->calculateValue().value<T>();
			}
		};


		template <class T, class N> const ruleSystem::Function::InputList EqualFunctor<T,N>::InputTypes()
		{
			return ruleSystem::Function::InputList::CreateCountedList(N::InputType(), 2);
		}
		template <class T, class N> const ruleSystem::Function::InputList LesserThanFunctor<T,N>::InputTypes()
		{
			return ruleSystem::Function::InputList::CreateCountedList(N::InputType(), 2);
		}
		template <class T, class N> const ruleSystem::Function::InputList LesserThanOrEqualFunctor<T,N>::InputTypes()
		{
			return ruleSystem::Function::InputList::CreateCountedList(N::InputType(), 2);
		}
		template <class T, class N> const ruleSystem::Function::InputList GreaterThanFunctor<T,N>::InputTypes()
		{
			return ruleSystem::Function::InputList::CreateCountedList(N::InputType(), 2);
		}
		template <class T, class N> const ruleSystem::Function::InputList GreaterThanOrEqualFunctor<T,N>::InputTypes()
		{
			return ruleSystem::Function::InputList::CreateCountedList(N::InputType(), 2);
		}
	}
}

#endif // TEMPLATEFUNCTION_HPP
