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

#ifndef ELEMENTSERIALIZER_HPP
#define ELEMENTSERIALIZER_HPP

#include "../../util/typeidentifier.hpp"
#include <QCoreApplication>

namespace ruleSystem
{
	class Element;
}

namespace serialization
{
	namespace qt
	{
		class ElementSerializer
		{
		public:
			ElementSerializer();
			virtual ~ElementSerializer();

			virtual const TypeIdentifier & identifier() const = 0;
			virtual ruleSystem::Element * deserialize(QDataStream & stream) const = 0;
			virtual void serialize(QDataStream & stream, ruleSystem::Element * element) const = 0;

			static const ElementSerializer * FindSerializer(ruleSystem::Element * element);
			static const ElementSerializer * FindSerializer(const QString & name);
			template <class T> static void RegisterSerializer();

		private:
			static void RegisterSerializer(ElementSerializer * serializer);
		};

		template <class T> void ElementSerializer::RegisterSerializer()
		{
			RegisterSerializer(new T);
		}

		template <class T> struct ElementRegisterer
		{
			ElementRegisterer()
			{
				ElementSerializer::RegisterSerializer<T>();
			}
		};
	}
}

QDataStream & operator<<(QDataStream & stream, ruleSystem::Element* element);
QDataStream & operator>>(QDataStream & stream, ruleSystem::Element * & element);



#endif // ELEMENTSERIALIZER_HPP
