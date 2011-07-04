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

#include "dbwrapper.hpp"

namespace ruleSystem
{
	namespace
	{
		QMap<QString, IDB*> & dbdb()
		{
			static QMap<QString, IDB*> types;
			return types;
		}
	}

	DBWrapper::DBWrapper(IDB * db)
		: _db(db)
	{
	}

	void DBWrapper::RegisterDB(IDB * db)
	{
		if(db == 0)
			return;

		dbdb()[db->name()] = db;
	}

	IDB * DBWrapper::FindDB(const QString & name)
	{
		QMap<QString, IDB*>::iterator i = dbdb().find(name);
		if(i == dbdb().end())
			return 0;
		else
			return i.value();
	}

	QDataStream & operator<<(QDataStream & stream, const DBWrapper & wrapper)
	{
		QString name = wrapper.db() ? wrapper.db()->name() : QString();

		stream << name;
		return stream;
	}

	QDataStream & operator>>(QDataStream & stream, DBWrapper & wrapper)
	{
		QString name;
		stream >> name;

		if(!name.isEmpty())
			wrapper.setDB(DBWrapper::FindDB(name));

		return stream;
	}
}
