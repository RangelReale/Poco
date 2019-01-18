//
// ByteRateLimiter.h
//
// $Id: //poco/1.4/Foundation/include/Poco/ByteRateLimiter.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  ByteRateLimiter
//
// Definition of the ByteRateLimiter class.
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_ByteRateLimiter_INCLUDED
#define Foundation_ByteRateLimiter_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/Stopwatch.h"

#include <iostream>

namespace Poco {


class Foundation_API ByteRateLimiter
	/// The ByteRateLimiter limits the byte rate
	/// by sleeping for the time needed to keep the
	/// target rate requested.
{
public:
	static const Poco::Clock::ClockDiff INTERVAL_SECOND = 1000 * 1000;
		/// Interval of one second.

	ByteRateLimiter(std::streamsize targetrate, Poco::Clock::ClockDiff interval = INTERVAL_SECOND);
		/// Creates the byte rate limiter for the target rate and interval.

	std::streamsize getTargetRate();
		/// Gets the requested target rate.

	Poco::Clock::ClockDiff getInterval();
		/// Gets the requested interval.

	void addBytes(std::streamsize bytes);
		/// Add bytes to the limiter. May sleep if above target rate.

private:
	std::streamsize _targetrate;
	Poco::Clock::ClockDiff _interval;
	Poco::Stopwatch _watch;
	std::streamsize _currentbytes;
};


} // namespace Poco


#endif // Foundation_ByteRateLimiter_INCLUDED
