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


#include "prologwriter.hpp"
#include <QList>
#include <QStringList>
#include <boost/shared_ptr.hpp>
#include "../action.hpp"
#include "../constant.hpp"
#include "../exception.hpp"
#include "elementwriter.hpp"

namespace ruleSystem {

namespace
{
typedef boost::shared_ptr<prolog::ElementWriter> writer;
typedef QList<writer>  writerList;
}

namespace
{
	writerList & allWriters() { static writerList w; return w; }
}

PrologWriter::CodeInformation::CodeInformation(int ruleNumber)
  : _ruleNumber(ruleNumber),
	 _varNum(0)
{
}

QString PrologWriter::CodeInformation::getUniqueVariable()
{
	return QString("%1%2").arg(varPrefix()).arg(_varNum++);
}

void PrologWriter::CodeInformation::addPreDefinition(const QString & definition)
{
	_preLst << definition;
}

void PrologWriter::CodeInformation::addPostDefinition(const QString & definition)
{
	_postLst << definition;
}

void PrologWriter::CodeInformation::clearAllPreDefinitions()
{
	_preLst.clear();
}

void PrologWriter::CodeInformation::clearAllPostDefinitions()
{
	_postLst.clear();
}

QString PrologWriter::CodeInformation::allPreDefinitions() const
{
	return _preLst.join(", ");
}

QString PrologWriter::CodeInformation::allPostDefinitions() const
{
	return _postLst.join(", ");
}

PrologWriter::PrologWriter(CodeInformation * information)
	: _information(information)
{
	Q_ASSERT(information);
}

PrologWriter::~PrologWriter()
{
	delete _information;
}

QString PrologWriter::writeSafeCode(Element * element, bool * success, QString * errorMessage)
{
	CleanErrorMsg(errorMessage);
	CleanSuccess(success);

	try
	{
		return writeCode(element);
	}
	catch(Exception e)
	{
		ErrorMsg(errorMessage, e.what());
		SuccessVal(success, false);
	}
	catch(...)
	{
		ErrorMsg(errorMessage, Exception::tr("Undefined error occured"));
		SuccessVal(success, false);
	}


	return QString();
}

QString PrologWriter::writeCode(Element * element)
{
	return PrologWriter::FindWriter(element).writeCode(element, *_information);
}

const prolog::ElementWriter & PrologWriter::FindWriter(Element * element)
{
	if(element == 0)
		throw Exception(Exception::tr("Unable to find a prolog code writer for an undefined element"), "PrologWriter::writeCode");

	float val = 0;
	writer curw;

	foreach(writer w, allWriters())
	{
		float curVal = w.get()->scoreElement(element);
		if(curVal > val)
		{
			val = curVal;
			curw = w;
		}
	}

	if(!curw.get())
		throw Exception(Exception::tr("Unable to find a prolog code writer for element '%1'").arg(element->name()), "PrologWriter::writeCode");

	return *(curw);
}

void PrologWriter::RegisterWriter(prolog::ElementWriter * elementWriter)
{
	allWriters().push_back(writer(elementWriter));
}

} // namespace ruleSystem
