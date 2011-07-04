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

#include <ruleSystem/serialization/qt/elementserializer.hpp>
#include "pokeraction.hpp"
#include "raiseaction.hpp"
#include <ruleSystem/evaluatable.hpp>

using namespace ruleSystem;
using namespace poker;

namespace serialization
{
	namespace qt
	{
		class PokerActionSerializer : public ElementSerializer
		{
		public:
			const TypeIdentifier & identifier() const
			{
				return PokerAction::TypeID();
			}

			Element * deserialize(QDataStream & stream) const
			{
				QString n;
				Element * e;
				stream >> n >> e;


				PokerAction * a = new PokerAction(n);
				a->setInput(Action::InputPosition(), e);
				return a;
			}

			void serialize(QDataStream & stream, Element *element) const
			{
				PokerAction * a = element_cast<PokerAction>(element);

				stream << a->name();
				stream << a->inputAt(Action::InputPosition());
			}
		};

		class RaiseActionSerializer : public ElementSerializer
		{
		public:
			const TypeIdentifier & identifier() const
			{
				return RaiseAction::TypeID();
			}

			Element * deserialize(QDataStream & stream) const
			{
				Element * e;
				Element * v;
				stream >> e >> v;


				RaiseAction * a = new RaiseAction();
				a->setInput(Action::InputPosition(), e);
				a->setInput(RaiseAction::BetSizePosition(), v);

				return a;
			}

			void serialize(QDataStream & stream, Element *element) const
			{
				RaiseAction * a = element_cast<RaiseAction>(element);

				stream << a->inputAt(Action::InputPosition());
				stream << a->inputAt(RaiseAction::BetSizePosition());
			}
		};


		namespace
		{
			ElementRegisterer<PokerActionSerializer> c1;
			ElementRegisterer<RaiseActionSerializer> c2;
		}
	}
}



