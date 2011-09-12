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

#include "element.hpp"
#include "ielementlistener.hpp"

namespace ruleSystem
{
        TYPEID_ROOT_SOURCE("Element", Element)


	namespace
	{
		void tryToDetachElement(Element * element)
		{
			if(element ==0)
				return;

			element->removeFromParent();
		}
	}


	Element::Element(const Type & type, const QString & name)
		: _type(type),
		_parent(0),
		_name(name),
		_devName(name)
	{
	}

	Element::~Element()
	{
		// set this element from the parent
		if(parent())
			parent()->removeChildElement(this);

		// notify & remove the listeners
		QList<IElementListener*> listeners = _listeners;
		foreach(IElementListener * listener, listeners)
			listener->onElementDestroyed();

		_listeners.clear();


		// remove all the attached child elements
		while(_inputElements.size() != 0)
		{
			// clear the list
			Element * oldElement = _inputElements.begin().value();
			_inputElements.erase(_inputElements.begin());

			// delete the element
			if(oldElement)
			{
				oldElement->_parent = 0;
				delete oldElement;
			}


		}
	}

	bool Element::hasElementTree(Element * element) const
	{
		if(element == this)
			return true;

		QMap<QString, Element *>::const_iterator i;
		for(i = _inputElements.begin(); i != _inputElements.end(); ++i)
			if(i.value() && i.value()->hasElementTree(element))
				return true;

		return false;
	}

	bool Element::removeChildElement(Element * element)
	{
		QList<QString> lst = _inputElements.keys(element);

		if(lst.size() == 0)
			return false;

		foreach(const QString & s, lst)
			removeInputAt(s);

		return true;
	}

	void Element::removeFromParent()
	{
		if(parent() == 0)
			return;

		parent()->removeChildElement(this);
	}

	QList<QString> Element::inputPositions() const
	{
		return _inputElements.keys();
	}

	bool Element::checkInputType(const QString & inputPosition, Element * inputElement, QString * errorMessage) const
	{
		CleanErrorMsg(errorMessage);

		bool exists;
		Type iType = inputType(translateInputPosition(inputPosition), exists);

		if(!exists)
		{
			ErrorMsg(errorMessage, QString(tr("This element has no input with name %1")).arg(inputPosition));
			return false;
		}

		if(inputElement == 0)
			return true;

		if(iType == type::unknownType())
			return true;

		if(iType != inputElement->type())
		{
			ErrorMsg(errorMessage, QString(tr("This element expects an element of type %1 at position %2, not of type %3")).arg(iType.typeName()).arg(inputPosition).arg(inputElement->type().typeName()));
			return false;
		}

		return true;
	}

	Element * Element::inputAt(const QString & inputPosition) const
	{
		QMap<QString, Element *>::const_iterator i = _inputElements.find(translateInputPosition(inputPosition));

		return i == _inputElements.end() ? 0 : i.value();
	}

	bool Element::hasInputAt(const QString & inputPosition) const
	{
		return _inputElements.find(translateInputPosition(inputPosition)) != _inputElements.end();
	}

	Element * Element::setInput(const QString & inputPosition, Element * element, bool * succeeded, QString * errorMessage)
	{
		CleanErrorMsg(errorMessage);
		CleanSuccess(succeeded);

		tryToDetachElement(element);

		QString realInputPosition = translateInputPosition(inputPosition);

		// check all the requirements
		if(!checkInputType(realInputPosition, element, errorMessage))
		{
			SuccessVal(succeeded, false);
			return 0;
		}

		// we can attach it, first see if there is an old element
		QMap<QString, Element *>::const_iterator i = _inputElements.find(realInputPosition);
		Element * oldElement = (i ==_inputElements.end() ? 0 : i.value());

		// check for special case where we want to insert a zero into a non-existing position
		if(i == _inputElements.end() && element == 0)
		{
			_inputElements[realInputPosition] = 0;
			return 0;
		}

		// the same? don't do anything
		if(oldElement == element)
			return 0;

		// detach the old element
		if(oldElement)
			oldElement->_parent = 0;

		// detach the new element from it's previous parent
		_inputElements[realInputPosition] = element;
		if(element) element->_parent = this;

		onInputChanged(realInputPosition, oldElement);

		notifyListeners();
		return oldElement;
	}

	void Element::swapInputs(const QString & inputPositionA, const QString & inputPositionB, bool * succeeded, QString * errorMessage)
	{
		CleanErrorMsg(errorMessage);
		CleanSuccess(succeeded);

		// stupid function call?
		if(inputPositionA == inputPositionB)
			return;

		// get the elements
		Element * elOnA = inputAt(inputPositionA);
		Element * elOnB = inputAt(inputPositionB);

		// check the input types
		if(!checkInputType(inputPositionB, elOnA, errorMessage))
		{
			SuccessVal(succeeded, false);
			return;
		}

		if(!checkInputType(inputPositionA, elOnB, errorMessage))
		{
			SuccessVal(succeeded, false);
			return;
		}

		// it's possible, perform the swap
		_inputElements[inputPositionA] = elOnB;
		_inputElements[inputPositionB] = elOnA;

		// output the change
		onInputChanged(inputPositionA, elOnA);
		onInputChanged(inputPositionB, elOnB);

		notifyListeners();
	}

	Element * Element::removeInputAt(const QString & inputPosition, bool * succeeded, QString * errorMessage)
	{
		CleanErrorMsg(errorMessage);
		CleanSuccess(succeeded);

		// does the position exist?
		QMap<QString, Element *>::iterator i = _inputElements.find(inputPosition);
		if(i == _inputElements.end())
		{
			ErrorMsg(errorMessage, QString(tr("There exists no element at position %1")).arg(inputPosition));
			SuccessVal(succeeded, false);

			return 0;
		}

		// remove the entry
		Element * element = i.value();
		if(requiredInputs().contains(i.key()))
			i.value() = 0;
		else
			_inputElements.erase(i);

		// detach the element
		if(element) element->_parent = 0;
		if(element)
			onInputChanged(inputPosition, element);

		notifyListeners();
		return element;
	}


	Element * Element::setInput(const QString & inputPosition, Element * element, QString * errorMessage)
	{
		return setInput(inputPosition, element, 0, errorMessage);
	}

	void Element::swapInputs(const QString & inputPositionA, const QString & inputPositionB, QString * errorMessage)
	{
		return swapInputs(inputPositionA, inputPositionB, 0, errorMessage);
	}

	Element * Element::removeInputAt(const QString & inputPosition, QString * errorMessage)
	{
		return removeInputAt(inputPosition, 0, errorMessage);
	}

	QList<QString> Element::requiredInputs() const
	{
		return QList<QString>();
	}

	int Element::numberOfInputs() const
	{
		return _inputElements.size();
	}

	void Element::attachListener(IElementListener * listener)
	{
		if(listener == 0 || _listeners.contains(listener))
			return;

		_listeners << listener;
	}

	void Element::removeListener(IElementListener * listener)
	{
		if(listener == 0)
			return;

		_listeners.removeAll(listener);
	}

	Element::operator const QString() const
	{
		return toString();
	}


	const QString Element::toString() const
	{
		return typeID().name();
	}


	QString Element::translateInputPosition(const QString & inputPosition) const
	{
		return inputPosition;
	}

	void Element::onInputChanged(const QString & /*inputPosition*/, Element * /*oldElement*/)
	{

	}

	void Element::notifyListeners()
	{
		foreach(IElementListener * listener, _listeners)
			listener->onChildElementChanged(this);
	}

	const QMap<QString, Element *> & Element::inputElements() const
	{
		return _inputElements;
	}

	bool element_castable(const Element *element, const TypeIdentifier & typeID)
	{
		return element->typeID().inherits(typeID);
	}

	void Element::setName(const QString & name)
	{
		_name = name;
	}

	void Element::setDevName(const QString &devName){
		_devName = devName;
	}

	QString Element::devName(){
		return _devName;
	}
}
