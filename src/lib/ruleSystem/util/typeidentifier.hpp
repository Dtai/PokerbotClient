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

#ifndef TYPEIDENTIFIER_HPP
#define TYPEIDENTIFIER_HPP

#include <QBitArray>
#include <QDebug>
#include "macro.hpp"
#include <boost/shared_ptr.hpp>

#define TYPEID_ROOT_HEADER(Name) \
public: \
                        static const TypeIdentifier & TypeID(); \
                        virtual const TypeIdentifier & typeID() const;

#define TYPEID_INHERIT_HEADER(Name, Superclass) \
public: \
                        static const TypeIdentifier & TypeID(); \
                        virtual const TypeIdentifier & typeID() const;

#define TYPEID_ROOT_SOURCE(Name, Classname) \
    const TypeIdentifier & Classname::TypeID() { const static TypeIdentifier id = TypeIdentifier::CreateRoot(Name); return id; } \
    const TypeIdentifier & Classname::typeID() const { return TypeID(); }



#define TYPEID_INHERIT_SOURCE(Name, Superclass, Classname) \
    const TypeIdentifier & Classname::TypeID() { const static TypeIdentifier id = TypeIdentifier::Inherit(Name, Superclass::TypeID()); return id; } \
    const TypeIdentifier & Classname::typeID() const { return TypeID(); }

	class TypeIdentifier
	{
		struct TreeDetail;

	private:
    TypeIdentifier(const QString & name);

	public:
		~TypeIdentifier();

		bool isRoot() const;
		bool inherits(const TypeIdentifier & other) const;
		int inheritanceDistance(const TypeIdentifier & other) const;
		const QString & name() const;

		bool operator==(const TypeIdentifier & rhs) const;
		bool operator<(const TypeIdentifier & rhs) const;

		static TypeIdentifier CreateRoot(const QString & name);
		static TypeIdentifier Inherit(const QString & name, const TypeIdentifier & superclass);

		friend QDebug operator<<(QDebug dbg, const TypeIdentifier & rhs);

	private:
		QString _name;
		QBitArray _key;
		boost::shared_ptr<TreeDetail> _tree;
	};


#endif // TYPEIDENTIFIER_HPP
