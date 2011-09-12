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

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "util/macro.hpp"
#include <QVariant>
#include <QString>
#include "type.hpp"
#include <QDebug>
#include <exception>
#include "util/typeidentifier.hpp"
#include <QMap>
#include <QCoreApplication>

#define ErrorMsg(PTR, VALUE) if(PTR) (*PTR) = VALUE
#define CleanErrorMsg(PTR) if(PTR) PTR->clear()
#define CleanSuccess(BOOL) if(BOOL) *BOOL = true
#define SuccessVal(BOOL, VALUE) if(BOOL) *BOOL = VALUE

namespace ruleSystem
{
	class IElementListener;

	class Element
	{
		Q_DECLARE_TR_FUNCTIONS(Element);
                TYPEID_ROOT_HEADER("Element");

	public:
		Element(const Type & type, const QString & name = QString());
		virtual ~Element() = 0;

		// functions to implement in base classes
		virtual bool isCorrect(QString * errorMessage = 0) const = 0;
		virtual Element * clone() const = 0;

		/* child/parent functions */
		bool hasElementTree(Element * element) const;
		bool removeChildElement(Element * element);
		void removeFromParent();

		/* input management functions */
		QList<QString> inputPositions() const;
		Element * inputAt(const QString & inputPosition) const;
		bool hasInputAt(const QString & inputPosition) const;
		Element * setInput(const QString & inputPosition, Element * element, bool * succeeded = 0, QString * errorMessage = 0);
		Element * setInput(const QString & inputPosition, Element * element, QString * errorMessage);
		void swapInputs(const QString & inputPositionA, const QString & inputPositionB, bool * succeeded = 0, QString * errorMessage = 0);
		void swapInputs(const QString & inputPositionA, const QString & inputPositionB, QString * errorMessage);
		Element * removeInputAt(const QString & inputPosition, bool * succeeded = 0, QString * errorMessage = 0);
		Element * removeInputAt(const QString & inputPosition, QString * errorMessage);
		virtual bool checkInputType(const QString & inputPosition, Element * inputElement, QString * errorMessage = 0) const;
		virtual QList<QString> requiredInputs() const;
		virtual Type inputType(const QString & inputPosition, bool & isValid) const = 0;
		int numberOfInputs() const;

		/* info functions */
		operator const QString() const;
		virtual const QString toString() const;

		/* listener functions */
		void attachListener(IElementListener * listener);
		void removeListener(IElementListener * listener);

		void setDevName(const QString &devName);
		QString devName();

	protected:
		/* input management functions */
		virtual QString translateInputPosition(const QString & inputPosition) const;
		virtual void onInputChanged(const QString & inputPosition, Element * oldElement);
		const QMap<QString, Element *> & inputElements() const;

		void setName(const QString & name);

	private:
		void notifyListeners();
		QMap<QString, Element *> _inputElements;

		RefVarGetProtectedSet(Type, type, Type);
		RefVarGetSet(QString, description, Description);
		PtrVarGet(Element, parent);
		RefVarGet(QString, name);
		QList<IElementListener*> _listeners;

		QString _devName;
	};

	/* Function definitions */
	template <class T> bool element_castable(const Element * element);
	template <class T> T * element_cast(Element * element);
	template <class T> T * element_cast(const Element * element);
	bool element_castable(const Element *element, const TypeIdentifier & typeID);


	/* Template implementations */
	template <class T> bool element_castable(const Element * element)
	{
		if (!element)
			return false;

		return element->typeID().inherits(T::TypeID());
	}

	template <class T> T * element_cast(Element * element)
	{
		if(!element_castable<T>(element))
			return 0;

		return static_cast<T*>(element);
	}
	template <class T> const T * element_cast(const Element * element)
	{
		if(!element_castable<T>(element))
			return 0;

		return static_cast<T*>(element);
	}

}

#endif // VALUE_HPP
