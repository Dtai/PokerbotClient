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


#ifndef UTIL_HPP
#define UTIL_HPP

#define SimpleVarGetSet(type, name, capitalisedName)							\
public:																			\
			type name() const { return _##name; }					\
			void set##capitalisedName(type name) { _##name = name; }			\
private:																		\
	type _##name

#define SimpleVarGet(type, name)							\
public:																			\
			type name() const { return _##name; }					\
private:																		\
	type _##name

#define SimpleVarGetAcc(type, name)							\
public:																			\
			type name() const { return _##name; }					\
			type & name() { return _##name; }                             \
private:																		\
	type _##name


#define RefVarGetSet(type, name, capitalisedName)								\
public:																			\
			const type & name() const { return _##name; }			\
			void set##capitalisedName(const type & name) { _##name = name; }	\
private:																		\
	type _##name

#define RefVarGetAcc(type, name)								\
public:																			\
			const type & name() const { return _##name; }						\
			type & name() { return _##name; }									\
private:																		\
	type _##name


#define RefVarGetAccSet(type, name, capitalisedName)								\
public:																			\
			const type & name() const { return _##name; }						\
			type & name() { return _##name; }									\
			void set##capitalisedName(const type & name) { _##name = name; }	\
private:																		\
	type _##name



#define RefVarGet(type, name)								\
public:																			\
			const type & name() const { return _##name; }			\
private:																		\
	type _##name

#define PtrVarGetSet(type, name, capitalisedName)								\
public:																			\
			type * name() const { return _##name; }					\
			void set##capitalisedName(type * name) { _##name = name; }			\
private:																		\
	type * _##name

#define PtrVarGetAcc(type, name)								\
public:																			\
			type * name() const { return _##name; }					\
			type* & name() { return _##name; }					\
private:																		\
	type * _##name


#define PtrVarGetAccSet(type, name, capitalisedName)								\
public:																			\
			type * name() const { return _##name; }					\
			type* & name() { return _##name; }					\
			void set##capitalisedName(type * name) { _##name = name; }			\
private:																		\
	type * _##name

#define PtrVarGet(type, name)								\
public:																			\
			type * name() const { return _##name; }					\
private:																		\
	type * _##name















#define SimpleVarGetProtectedSet(type, name, capitalisedName)							\
public:																			\
			type name() const { return _##name; }					\
protected:\
			void set##capitalisedName(type name) { _##name = name; }			\
private:																		\
	type _##name

#define SimpleVarGetProtectedAcc(type, name, capitalisedName)							\
public:																			\
			type name() const { return _##name; }					\
		protected: \
			type & r##capitalisedName() { return _##name; }                             \
private:																		\
	type _##name


#define RefVarGetProtectedSet(type, name, capitalisedName)								\
public:																			\
			const type & name() const { return _##name; }			\
		protected: \
			void set##capitalisedName(const type & name) { _##name = name; }	\
private:																		\
	type _##name

#define RefVarGetProtectedAcc(type, name, capitalisedName)								\
public:																			\
			const type & name() const { return _##name; }						\
		protected: \
			type & r##capitalisedName() { return _##name; }									\
private:																		\
	type _##name


#define RefVarGetProtectedAccSet(type, name, capitalisedName)								\
public:																			\
			const type & name() const { return _##name; }						\
		protected: \
			type & r##capitalisedName() { return _##name; }									\
			void set##capitalisedName(const type & name) { _##name = name; }	\
private:																		\
	type _##name



#define PtrVarGetProtectedSet(type, name, capitalisedName)								\
public:																			\
			type * name() const { return _##name; }					\
		protected: \
			void set##capitalisedName(type * name) { _##name = name; }			\
private:																		\
	type * _##name

#define PtrVarGetProtectedAcc(type, name, capitalisedName)								\
public:																			\
			type * name() const { return _##name; }					\
		protected: \
			type* & r##capitalisedName() { return _##name; }					\
private:																		\
	type * _##name


#define PtrVarGetProtectedAccSet(type, name, capitalisedName)								\
public:																			\
			type * name() const { return _##name; }					\
		protected: \
			type* & r##capitalisedName() { return _##name; }					\
			void set##capitalisedName(type * name) { _##name = name; }			\
private:																		\
	type * _##name


#endif // UTIL_HPP
