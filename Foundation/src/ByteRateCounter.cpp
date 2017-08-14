//
// ByteRateCounter.cpp
//
// $Id: //poco/1.4/Foundation/src/ByteRateCounter.cpp#4 $
//
// Library: Foundation
// Package: Core
// Module:  ByteRateCounter
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/ByteRateCounter.h"


namespace Poco {


ByteRateCounter::ByteRateCounter(Poco::Clock::ClockDiff interval) :
	_interval(interval), _watch(), _totalbytes(0)
{
	_watch.start();
}


Poco::Clock::ClockDiff ByteRateCounter::getInterval()
{
	return _interval;
}


void ByteRateCounter::addBytes(std::streamsize bytes)
{
	_totalbytes += bytes;
}


void ByteRateCounter::setBytes(std::streamsize bytes)
{
	_totalbytes = bytes;
}


std::streamsize ByteRateCounter::getTotalAverage()
{
	Poco::Clock::ClockDiff elapinterval = _watch.elapsed() / _interval;
	if (elapinterval > 0)
		return static_cast<Poco::UInt32>(_totalbytes / elapinterval);
	return 0;
}


std::streamsize ByteRateCounter::getTotalBytes()
{
	return _totalbytes;
}


} // namespace Poco
