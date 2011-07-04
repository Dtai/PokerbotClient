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


#include "ruleserialization.hpp"
#include <ruleSystem/graphicsView/elementgraphicsitem.hpp>
#include <ruleSystem/graphicsView/elementfactory.hpp>

using namespace ruleSystem;
using namespace ruleSystem::graphicsView;

namespace serialization
{
	namespace	qt
	{
		namespace
		{
			ElementFactory * factory() { return ElementFactory::Instance(); }
		}

		void serializeScene(ElementGraphicsScene * scene, QDataStream & stream)
		{
			// find all the elementGraphicsItem with no parent in the scene
			if(scene == 0)
			{
				stream << 0;
				return;
			}

			QList<QGraphicsItem*> items = scene->items();
			QList<ElementGraphicsItem*> serializables;
			foreach(QGraphicsItem * item, items)
			{
				ElementGraphicsItem * el = qgraphicsitem_cast<ElementGraphicsItem*>(item);
				if(el == 0 || el->parent() != 0 || el->element() == 0)
					continue;

				serializables << el;
			}

			stream << serializables.size();
			foreach(ElementGraphicsItem * it, serializables)
				stream << it->element() << it->pos();
		}

		void deserializeScene(ElementGraphicsScene * scene, QDataStream & stream)
		{
			int size;
			stream >> size;

			for(int i = 0; i < size; i++)
			{
				Element * e;
				QPointF p;

				stream >> e >> p;
				ElementGraphicsItem * cur = factory()->createGraphicsItem(e);
				scene->addItem(cur);
				cur->setPos(p);
			}
		}
	}
}
