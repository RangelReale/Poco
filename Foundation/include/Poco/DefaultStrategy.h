//
// DefaultStrategy.h
//
// $Id: //poco/svn/Foundation/include/Poco/DefaultStrategy.h#2 $
//
// Library: Foundation
// Package: Events
// Module:  DefaultStrategy
//
// Implementation of the DefaultStrategy template.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef  Foundation_DefaultStrategy_INCLUDED
#define  Foundation_DefaultStrategy_INCLUDED


#include "Poco/NotificationStrategy.h"
#include <memory>
#include <set>
#include <vector>


namespace Poco {


template <class TArgs, class TDelegate, class TCompare> 
class DefaultStrategy//: public NotificationStrategy<TArgs, TDelegate>
	/// Default notification strategy. Allows one observer
	///	to register exactly once. The observer must provide an
	/// < (less-than) operator.
{
public:
	typedef std::set<TDelegate*, TCompare>     Delegates;
	typedef typename Delegates::iterator       Iterator;
	typedef typename Delegates::const_iterator ConstIterator;

public:
	DefaultStrategy()
	{
	}

	DefaultStrategy(const DefaultStrategy& s)
	{
		operator = (s);
	}

	~DefaultStrategy()
	{
		clear();
	}

	void notify(const void* sender, TArgs& arguments)
	{
		std::vector<Iterator> delMe;

		for (Iterator it = _observers.begin(); it != _observers.end(); it++)
		{
			if (!(*it)->notify(sender, arguments))
			{
				// schedule for deletion
				delMe.push_back(it);
			}
		}
		
		while (!delMe.empty())
		{
			typename std::vector<Iterator>::iterator vit = delMe.end();
			--vit;
			delete **vit;
			_observers.erase(*vit);
			delMe.pop_back();
		}
	}

	void add(const TDelegate& delegate)
	{
		Iterator it = _observers.find(const_cast<TDelegate*>(&delegate));
		if (it != _observers.end())
		{
			delete *it;
			_observers.erase(it);
		}
		std::auto_ptr<TDelegate> pDelegate(delegate.clone());
		bool tmp = _observers.insert(pDelegate.get()).second;
		poco_assert (tmp);
		pDelegate.release();
	}

	void remove(const TDelegate& delegate)
	{
		Iterator it = _observers.find(const_cast<TDelegate*>(&delegate));
		if (it != _observers.end())
		{
			delete *it;
			_observers.erase(it);
		}
	}

	DefaultStrategy& operator = (const DefaultStrategy& s)
	{
		if (this != &s)
		{
			for (ConstIterator it = s._observers.begin(); it != s._observers.end(); ++it)
			{
				add(**it);
			}
		}
		return *this;
	}

	void clear()
	{
		for (Iterator it = _observers.begin(); it != _observers.end(); ++it)
		{
			delete *it;
		}
		_observers.clear();
	}

	bool empty() const
	{
		return _observers.empty();
	}

protected:
	Delegates _observers;
};


} // namespace Poco


#endif
