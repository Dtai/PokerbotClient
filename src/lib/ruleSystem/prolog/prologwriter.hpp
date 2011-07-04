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

#ifndef PROLOGWRITER_HPP
#define PROLOGWRITER_HPP

#include <QString>
#include <QStringList>
#include "../util/macro.hpp"
#include <QCoreApplication>

namespace ruleSystem {

class Element;

namespace prolog {

	class ElementWriter;

} // namespace prolog

class PrologWriter
{
public:
	class CodeInformation
	{
	public:
		static const QString varPrefix() { return "X"; }

		CodeInformation(int ruleNumber);
		virtual ~CodeInformation() {}

		QString getUniqueVariable();
		void addPreDefinition(const QString & definition);
		void addPostDefinition(const QString & definition);

		int getRuleNumber();

		QString allPreDefinitions() const;
		QString allPostDefinitions() const;
		void clearAllPreDefinitions();
		void clearAllPostDefinitions();

	private:
		SimpleVarGet(int, ruleNumber);
		QStringList _preLst;
		QStringList _postLst;
		int _varNum;
	};

	PrologWriter(CodeInformation * information);
	~PrologWriter();

	QString writeSafeCode(Element * element, bool * success = 0, QString * errorMessage = 0);
	QString writeCode(Element * element);

	// static functions
	template <class T> static void RegisterWriter();
	static const prolog::ElementWriter & FindWriter(Element * element);
	static void RegisterWriter(prolog::ElementWriter * elementWriter);

private:
	CodeInformation * _information;
};

template <class T> void PrologWriter::RegisterWriter()
{
	RegisterWriter(new T);
}
} // namespace ruleSystem

#endif // PROLOGWRITER_HPP
