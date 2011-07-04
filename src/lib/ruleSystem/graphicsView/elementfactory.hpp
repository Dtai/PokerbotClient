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

#ifndef ELEMENTFACTORY_HPP
#define ELEMENTFACTORY_HPP

#include "../util/singleton.hpp"
#include "../element.hpp"
#include <QMap>

namespace ruleSystem
{
	namespace graphicsView
	{
		class ElementGraphicsItem;
		class ElementLayout;

		class ElementFactory : public Singleton<ElementFactory>
		{
			friend class Singleton<ElementFactory>;

		public:
			struct ElementCreator
			{
				virtual float scoreElement(const Type & type, Element * element) const = 0;
				virtual ElementGraphicsItem* create(const Type & type, Element * element) const = 0;
			};

		private:
			ElementFactory();
			~ElementFactory();

		public:
			/* Element creation functions */
			ElementGraphicsItem * createGraphicsItem(Element * element);
			ElementGraphicsItem * createGraphicsItem(const Type & type, const TypeIdentifier & id);
			void registerElementCreator(ElementCreator * creator);

			/* Layout functions */
			const ElementLayout * findLayout(const Type & type, const TypeIdentifier & id);
			const ElementLayout * findLayout(const Element * element);
			void registerLayout(const Type & type, const TypeIdentifier & id, ElementLayout * layout);

		private:
			QMap<QPair<Type, TypeIdentifier>, ElementLayout *> _registeredLayouts;
			QList<ElementCreator*> _registeredCreators;
		};
	}
}



#endif // ELEMENTFACTORY_HPP
