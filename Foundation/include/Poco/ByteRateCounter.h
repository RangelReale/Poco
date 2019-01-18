//
// ByteRateCounter.h
//
// $Id: //poco/1.4/Foundation/include/Poco/ByteRateCounter.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  ByteRateCounter
//
// Definition of the ByteRateCounter class.
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_ByteRateCounter_INCLUDED
#define Foundation_ByteRateCounter_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/Stopwatch.h"

#include <iostream>

namespace Poco {


class Foundation_API ByteRateCounter
	/// The ByteRateCounter class calculates the byte rate 
	/// (e.g. bytes/second).
{
public:
	static const Poco::Clock::ClockDiff INTERVAL_SECOND = 1000 * 1000;
		/// Interval of one second.

	ByteRateCounter(Poco::Clock::ClockDiff interval = INTERVAL_SECOND);
		/// Creates the byte counter with the indicated interval 
		/// (default is "per second")

	Poco::Clock::ClockDiff getInterval();
		/// Gets the interval passed on the constructor.

	void addBytes(std::streamsize bytes);
		/// Add bytes to the counter.

	void setBytes(std::streamsize bytes);
		/// Set the current total bytes.

	std::streamsize getTotalAverage();
		/// Gets the average bytes per interval.

	std::streamsize getTotalBytes();
		/// Gets the total bytes added.

private:
	Poco::Clock::ClockDiff _interval;
	Poco::Stopwatch _watch;
	std::streamsize _totalbytes;
};


} // namespace Poco


#endif // Foundation_ByteRateCounter_INCLUDED
