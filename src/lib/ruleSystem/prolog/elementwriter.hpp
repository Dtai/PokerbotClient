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


#ifndef ELEMENTWRITER_HPP
#define ELEMENTWRITER_HPP

#include "../element.hpp"
#include "prologwriter.hpp"

namespace ruleSystem {
namespace prolog {

class ElementWriter
{
public:
	virtual float scoreElement(Element * element) const = 0;
	virtual QString writeCode(Element * element, PrologWriter::CodeInformation & info) const = 0;
};

template <class T> struct TElementWriterRegisterer
{
	TElementWriterRegisterer()
	{
		PrologWriter::RegisterWriter(new T);
	}
};

struct ElementWriterRegisterer
{
	ElementWriterRegisterer(ElementWriter * writer)
	{
		PrologWriter::RegisterWriter(writer);
	}
};

} // namespace prolog
} // namespace ruleSystem

#endif // ELEMENTWRITER_HPP
