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

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <boost/shared_ptr.hpp>


template <class T> class Singleton
{
private:
	static boost::shared_ptr<T>_instance;

	struct deleter
	{
		void operator() (T * t)
		{
			delete t;
		}
	};

protected:
	Singleton() {}

public:
	static T * Instance()
	{
		if(_instance == 0)
			_instance = boost::shared_ptr<T>(new T, deleter());

		return _instance.get();

	}

	static void Destroy()
	{

		if(_instance != 0)
			_instance = boost::shared_ptr<T>(0);

	}
};

template <class T> boost::shared_ptr<T> Singleton<T>::_instance = boost::shared_ptr<T>();

#endif
