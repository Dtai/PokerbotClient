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

#include "typeidentifier.hpp"
#include "util/macro.hpp"

class TypeIdentifier::TreeDetail
{
public:
	TreeDetail()
		: _currentPos(0)
	{
	}

	int createKeyPos()
	{
		int pos = _currentPos;
		_currentPos++;

		return pos;
	}

private:
	int _currentPos;
};

TypeIdentifier::TypeIdentifier(const QString & name)
        : _name(name)
{
}

TypeIdentifier::~TypeIdentifier()
{
}

TypeIdentifier TypeIdentifier::CreateRoot(const QString & name)
{
	TypeIdentifier id(name);
	id._tree = boost::shared_ptr<TreeDetail>(new TreeDetail);
	int keyPos = id._tree->createKeyPos();

	id._key = QBitArray(keyPos+1, true);

	return id;
}

TypeIdentifier TypeIdentifier::Inherit(const QString & name, const TypeIdentifier & superclass)
{
	TypeIdentifier id(name);
	id._tree = superclass._tree;

        TreeDetail * psup = superclass._tree.get();
        TreeDetail * pchild = id._tree.get();

        bool val = id._tree == superclass._tree;

	int keyPos = id._tree->createKeyPos();
	id._key = superclass._key;
	id._key.resize(keyPos+1);
	id._key.setBit(keyPos, true);

	return id;
}

bool TypeIdentifier::isRoot() const
{
	return _key.size() == 1;
}

bool TypeIdentifier::inherits(const TypeIdentifier & other) const
{
	if(other._tree != _tree)
		return false;

	QBitArray ar = _key&other._key;
	ar.truncate(other._key.size());

	return ar.operator==(other._key);
}

int TypeIdentifier::inheritanceDistance(const TypeIdentifier & other) const
{
	if(!inherits(other))
		return -1;

	QBitArray ar = operator ^(_key, other._key);
	return ar.count(true);
}

const QString & TypeIdentifier::name() const
{
	return _name;
}

bool TypeIdentifier::operator==(const TypeIdentifier & rhs) const
{
	return rhs._tree == _tree && rhs._key == _key;
}

bool TypeIdentifier::operator<(const TypeIdentifier & rhs) const
{
	if(_tree < rhs._tree)
		return true;

	if(_tree < rhs._tree)
		return false;

	if(_key.size() < rhs._key.size())
		return true;

	if(_key.size() > rhs._key.size())
		return false;

	if(_key == rhs._key)
		return false;

	// check if they are the same
	for(int i = 0; i < _key.size(); i++)
	{
		if(_key.at(i) == rhs._key.at(i))
			continue;

		return !(_key.at(i));
	}

	return false;
}

QDebug operator<<(QDebug dbg, const TypeIdentifier & rhs)
{
	dbg.nospace() << "TypeID: Root at" <<  rhs._tree << "; bits:";
	for(int i = 0; i < rhs._key.size(); i++)
		if(rhs._key.at(i))
			dbg.nospace() << '1';
		else
			dbg.nospace() << '0';

	return dbg.space();
}
