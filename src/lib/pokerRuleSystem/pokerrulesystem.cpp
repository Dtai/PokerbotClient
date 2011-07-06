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

#include "pokerrulesystem.hpp"
#include <ruleSystem/element.hpp>
#include <ruleSystem/constant.hpp>
#include <ruleSystem/function.hpp>
#include <ruleSystem/feature.hpp>
#include <ruleSystem/action.hpp>
#include <ruleSystem/calculatorfactory.hpp>
#include <ruleSystem/graphicsView/elementlayout.hpp>
#include <ruleSystem/graphicsView/elementfactory.hpp>
#include <ruleSystem/graphicsView/elementgraphicsitem.hpp>
#include <ruleSystem/graphicsView/functiongraphicsitem.hpp>
#include <ruleSystem/graphicsView/defaultitemdelegate.hpp>
#include <ruleSystem/graphicsView/actiongraphicsitem.hpp>

#include "graphicsView/raiseactiongraphicsitem.hpp"
#include "graphicsView/constantitembooldelegate.hpp"
#include "graphicsView/constantitemnumericaldelegate.hpp"
#include "graphicsView/constantitemcarddelegate.hpp"

using namespace ruleSystem;
using namespace ruleSystem::graphicsView;
using namespace poker::graphicsView;

namespace poker
{
	namespace
	{
		CalculatorRegisterer<function::BoolEqualFunctor> b1;

		CalculatorRegisterer<function::NumEqualFunctor> n1;
		CalculatorRegisterer<function::NumLesserThanFunctor> n3;
		CalculatorRegisterer<function::NumLesserThanOrEqualFunctor> n4;
		CalculatorRegisterer<function::NumGreaterThanFunctor> n5;
		CalculatorRegisterer<function::NumGreaterThanOrEqualFunctor> n6;
		CalculatorRegisterer<function::ContainsFunctor> n7;

		ElementFactory * factory() { return ElementFactory::Instance(); }

		static QList<Type> dataTypes = QList<Type>()				<< type::booleanType()	<< type::numericalType()	<< type::cardListType() << type::unknownType()	<< type::voidType() << type::cardEquationType();
		static QList<QString> sTypes = QList<QString>()			<< "puzzle"							<< "tstuk"								<< "triangle"						<< "leeg"								<< "void"						<< "kroon";

		static QList<TypeIdentifier> categories = QList<TypeIdentifier>()		<< Element::TypeID()		<< Function::TypeID()	<< Constant::TypeID()	<< Feature::TypeID()	<< Action::TypeID();
		static QList<QString> sColors = QList<QString>()										<< "white"							<< "purple"						<<"yellow"						<< "green"						<< "blue";
		static QList<QColor> cColors = QList<QColor>()											<< QColor(255,255,255)	<< QColor(219,26,200)	<< QColor(219,204,31)	<< QColor(35,157,33)	<< QColor(170,204,255);
		static bool isStarted = false;

		template <class T> void registerLayout(const Type & type)
		{
			int typePos = dataTypes.indexOf(type);
			int idPos = categories.indexOf(T::TypeID());

			QString resource_name = QString(":/element/%1_%2").arg(sTypes[typePos]).arg(sColors[idPos]);
			QString h_resource_name = QString(":/element/h_%1_%2").arg(sTypes[typePos]).arg(sColors[idPos]);
			QBrush b(cColors[idPos]);
			ElementLayout * layout = new ElementLayout(QPixmap(resource_name), QPixmap(h_resource_name), b);

			factory()->registerLayout(type, T::TypeID(), layout);
		}


		void initialiseLayouts()
		{
			if(isStarted)
				return;

			registerLayout<Element>(type::booleanType());
			registerLayout<Element>(type::numericalType());
			registerLayout<Element>(type::cardListType());
			registerLayout<Element>(type::cardEquationType());
			registerLayout<Element>(type::unknownType());

			registerLayout<Constant>(type::booleanType());
			registerLayout<Constant>(type::numericalType());
			registerLayout<Constant>(type::cardEquationType());

			registerLayout<Feature>(type::booleanType());
			registerLayout<Feature>(type::numericalType());
			registerLayout<Feature>(type::cardListType());

			registerLayout<Action>(type::voidType());

			registerLayout<Function>(type::booleanType());
			registerLayout<Function>(type::numericalType());
			registerLayout<Function>(type::cardListType());

			isStarted = true;
		}

		struct FeatureGraphicsCreator : public ElementFactory::ElementCreator
		{
			virtual float scoreElement(const Type & /*type*/, Element * element) const
			{
				if(element == 0)
					return 0;
				return (element_castable<Feature>(element) ? 1.0f : 0.0f);
			}

			virtual ElementGraphicsItem* create(const Type & type, Element * element) const
			{
				if(element == 0)
					return 0;

				ElementGraphicsItem * it = new ElementGraphicsItem(element, factory()->findLayout(type, element->typeID()));
				it->setDelegate(new DefaultItemDelegate);
				it->elementChanged();

				return it;
			}
		};

		struct FunctionGraphicsCreator : public ElementFactory::ElementCreator
		{
			virtual float scoreElement(const Type & /*type*/, Element * element) const
			{
				if(element == 0)
					return 0;

				return (element_castable<Function>(element) ? 1.0f : 0.0f);
			}

			virtual ElementGraphicsItem * create(const Type & /*type*/, Element * element) const
			{
				if(element == 0)
					return 0;

				ElementGraphicsItem * it = new FunctionGraphicsItem(static_cast<Function*>(element));
				it->setDelegate(new DefaultItemDelegate);
				it->elementChanged();

				return it;
			}
		};
		struct EmptyGraphicsCreator : public ElementFactory::ElementCreator
		{
			virtual float scoreElement(const Type & /*type*/, Element * element) const
			{
				if(element == 0)
					return 1.0f;
				else
					return 0.2f;
			}

			virtual ElementGraphicsItem * create(const Type & type, Element * /*element*/) const
			{
				ElementGraphicsItem * it = new ElementGraphicsItem(0, factory()->findLayout(type, Element::TypeID()));
				it->elementChanged();

				return it;
			}
		};

		struct ConstantGraphicsCreator : public ElementFactory::ElementCreator
		{
			virtual float scoreElement(const Type & /*type*/, Element * element) const
			{
				if(element == 0)
					return 0;

				return (element_castable<Constant>(element) ? 1.0f : 0.0f);
			}

			virtual ElementGraphicsItem* create(const Type & type, Element * element) const
			{
				if(element == 0)
					return 0;

				ElementGraphicsItem * it = new ElementGraphicsItem(element, factory()->findLayout(type, element->typeID()));
				if(type == type::booleanType())
					it->setDelegate(new ConstantItemBoolDelegate);
				else if(type == type::numericalType())
					it->setDelegate(new ConstantItemNumericalDelegate);
				else if(type == type::cardEquationType())
					it->setDelegate(new ConstantItemCardDelegate);
				else
					it->setDelegate(new DefaultItemDelegate);

				it->elementChanged();

				return it;
			}
		};

		struct ActionGraphicsCreator : public ElementFactory::ElementCreator
		{
			virtual float scoreElement(const Type & /*type*/, Element * element) const
			{
				if(!element)
					return 0.0f;

				return element_castable<Action>(element) ? 1.0f : 0.0f;
			}

			virtual ElementGraphicsItem * create(const Type & /*type*/, Element *element) const
			{
				Action * action = element_cast<Action>(element);
				if(action == 0)
					return 0;

				ActionGraphicsItem * it = new ActionGraphicsItem(action);
				it->setDelegate(new DefaultItemDelegate);
				it->elementChanged();

				return it;
			}
		};

		struct RaiseActionGraphicsCreator : public ElementFactory::ElementCreator
		{
			virtual float scoreElement(const Type & /*type*/, Element * element) const
			{
				if(!element)
					return 0.0f;

				return element_castable<RaiseAction>(element) ? 1.4f : 0.0f;
			}

			virtual ElementGraphicsItem * create(const Type & /*type*/, Element *element) const
			{
				RaiseAction * action = element_cast<RaiseAction>(element);
				if(action == 0)
					return 0;

				RaiseActionGraphicsItem * it = new RaiseActionGraphicsItem(action);
				it->setDelegate(new DefaultItemDelegate);
				it->elementChanged();

				return it;
			}
		};

		void initialiseCreators()
		{
			factory()->registerElementCreator(new FeatureGraphicsCreator);
			factory()->registerElementCreator(new FunctionGraphicsCreator);
			factory()->registerElementCreator(new EmptyGraphicsCreator);
			factory()->registerElementCreator(new ConstantGraphicsCreator);
			//			factory()->registerElementCreator(new ConstantCardGraphicsCreator);
			factory()->registerElementCreator(new ActionGraphicsCreator);
			factory()->registerElementCreator(new RaiseActionGraphicsCreator);
			//			factory()->registerElementCreator(new IfThenElseGraphicsCreator);
		}
	}

	void initialise()
	{
		qRegisterMetaType<poker::Card>("poker::Card");
		qRegisterMetaTypeStreamOperators<poker::Card>("poker::Card");

		qRegisterMetaType<QList<poker::Card> >("QList<poker::Card>");
		qRegisterMetaTypeStreamOperators<QList<poker::Card> >("QList<poker::Card>");

		initialiseLayouts();
		initialiseCreators();
	}
}
