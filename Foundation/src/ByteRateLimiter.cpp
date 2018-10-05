//
// ByteRateLimiter.cpp
//
// $Id: //poco/1.4/Foundation/src/ByteRateLimiter.cpp#4 $
//
// Library: Foundation
// Package: Core
// Module:  ByteRateLimiter
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/ByteRateLimiter.h"
#include "Poco/Thread.h"


namespace Poco {


ByteRateLimiter::ByteRateLimiter(std::streamsize targetrate, Poco::Clock::ClockDiff interval) :
	_targetrate(targetrate), _interval(interval), _watch(), _currentbytes(0)
{
	_watch.start();
}


std::streamsize ByteRateLimiter::getTargetRate()
{
	return _targetrate;
}


Poco::Clock::ClockDiff ByteRateLimiter::getInterval()
{
	return _interval;
}


void ByteRateLimiter::addBytes(std::streamsize bytes)
{
	_currentbytes += bytes;

	if (_currentbytes >= _targetrate)
	{
		double prop = (_currentbytes / (double)_targetrate);

		Poco::Clock::ClockDiff diff = _interval - _watch.elapsed();
		if (diff > 0)
		{
			long slp = static_cast<long>((diff * prop) / 1000.0);
			Poco::Thread::sleep(slp);
		}
		_currentbytes = 0;
		_watch.restart();
	}
}


} // namespace Poco
