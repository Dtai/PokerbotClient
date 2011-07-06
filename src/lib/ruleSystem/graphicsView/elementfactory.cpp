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

#include "elementfactory.hpp"
#include "elementlayout.hpp"

namespace ruleSystem
{
	namespace graphicsView
	{
		typedef QPair<Type, TypeIdentifier> MapKey;
		typedef QMap<MapKey, ElementLayout*> LayoutMap;
		typedef QList<ElementFactory::ElementCreator*> CreatorList;

		namespace
		{
			ElementFactory::ElementCreator * findCreator(const CreatorList & lst, const Type & type, Element * element)
			{
				int bestPos = -1;
				float bestScore = 0;

				for(int i = 0; i < lst.size(); i++)
				{
					float curScore = lst[i]->scoreElement(type, element);

					if(curScore > bestScore)
					{
						bestScore = curScore;
						bestPos = i;
					}
				}

				if(bestScore == 0)
					return 0;
				else
					return lst[bestPos];
			}

			ElementLayout * searchLayout(const LayoutMap & map, const Type & type, const TypeIdentifier & typeIdentifier)
			{
				LayoutMap::const_iterator nearest = map.end();
				int closestDistance = -1;

				for(LayoutMap::const_iterator i = map.begin(); i != map.end(); i++)
				{
					// same type or not?
					if(i.key().first != type)
						continue;

					int curDistance = typeIdentifier.inheritanceDistance(i.key().second);

					// do we need to travel any farther
					if(curDistance == 0)
						return i.value();

					if(curDistance != -1)
					{
						if(closestDistance == -1 || curDistance < closestDistance)
						{
							closestDistance = curDistance;
							nearest = i;
						}
					}
				}

				if(closestDistance == -1)
					return 0;
				else
					return nearest.value();

			}
		}



		ElementFactory::ElementFactory()
		{
		}

		ElementFactory::~ElementFactory()
		{
			for(LayoutMap::iterator i = _registeredLayouts.begin(); i != _registeredLayouts.end(); i++)
				delete i.value();

                        qDeleteAll(_registeredCreators);
		}

		ElementGraphicsItem * ElementFactory::createGraphicsItem(Element * element)
		{
			if(element == 0)
				return 0;

			ElementCreator * c = findCreator(_registeredCreators, element->type(), element);
			if(c == 0)
			{
				qDebug() << "unable to create an ElementGraphicsItem for item" << element << "of type" << element->type().typeName();
				return 0;
			}

			return c->create(element->type(), element);
		}

		ElementGraphicsItem * ElementFactory::createGraphicsItem(const Type & type, const TypeIdentifier & /*identifier*/)
                {
			ElementCreator * c = findCreator(_registeredCreators, type, 0);
			if(c == 0)
			{
				qDebug() << "unable to create an empty ElementGraphicsItem of type" << type.typeName();
				return 0;
			}

			return c->create(type, 0);
		}

		void ElementFactory::registerElementCreator(ElementCreator * creator)
                {
			if(creator == 0)
                                return;

                        _registeredCreators << creator;
		}

		const ElementLayout * ElementFactory::findLayout(const Type & type, const TypeIdentifier & identifier)
		{
			return searchLayout(_registeredLayouts, type, identifier);
		}

		const ElementLayout * ElementFactory::findLayout(const Element * element)
		{
			return findLayout(element->type(), element->typeID());
		}

		void ElementFactory::registerLayout(const Type & type, const TypeIdentifier & identifier, ElementLayout * layout)
		{
			_registeredLayouts[MapKey(type, identifier)] = layout;
		}
	}
}
