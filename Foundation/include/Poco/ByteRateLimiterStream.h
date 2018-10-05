//
// CountingStream.h
//
// $Id: //poco/1.4/Foundation/include/Poco/ByteRateLimiterStream.h#1 $
//
// Library: Foundation
// Package: Streams
// Module:  ByteRateLimiterStream
//
// Definition of the ByteRateLimiterStreamBuf, ByteRateLimiterInputStream and ByteRateLimiterOutputStream classes.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_ByteRateLimiterStream_INCLUDED
#define Foundation_ByteRateLimiterStream_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/BufferedStreamBuf.h"
#include "Poco/ByteRateLimiter.h"
#include <istream>
#include <ostream>


namespace Poco {


class Foundation_API ByteRateLimiterStreamBuf: public BufferedStreamBuf
	/// This stream limits the byte rate of data
	/// going through it.
{
public:

	ByteRateLimiterStreamBuf(std::istream& istr, std::streamsize targetrate, Poco::Clock::ClockDiff interval = ByteRateLimiter::INTERVAL_SECOND);
		/// Creates the ByteRateLimiterStreamBuf and connects it
		/// to the given input stream, limiting the rate to the
		/// target rate by the interval.

	ByteRateLimiterStreamBuf(std::ostream& ostr, std::streamsize targetrate, Poco::Clock::ClockDiff interval = ByteRateLimiter::INTERVAL_SECOND);
		/// Creates the ByteRateLimiterStreamBuf and connects it
		/// to the given output stream, limiting the rate to the
		/// target rate by the interval.

	~ByteRateLimiterStreamBuf();
		/// Destroys the ByteRateLimiterStreamBuf.

protected:
	int readFromDevice(char* buffer, std::streamsize length);
	int writeToDevice(const char* buffer, std::streamsize length);

private:
	std::istream* _pIstr;
	std::ostream* _pOstr;
	Poco::ByteRateLimiter _limiter;
};


class Foundation_API ByteRateLimiterIOS : public virtual std::ios
	/// The base class for ByteRateLimiterInputStream and
	/// ByteRateLimiterOutputStream.
	///
	/// This class is needed to ensure the correct initialization
	/// order of the stream buffer and base classes.
{
public:
	ByteRateLimiterIOS(std::istream& istr, std::streamsize targetrate, Poco::Clock::ClockDiff interval = ByteRateLimiter::INTERVAL_SECOND);
		/// Creates the basic stream and connects it
		/// to the given input stream.

	ByteRateLimiterIOS(std::ostream& ostr, std::streamsize targetrate, Poco::Clock::ClockDiff interval = ByteRateLimiter::INTERVAL_SECOND);
		/// Creates the basic stream and connects it
		/// to the given output stream.

	~ByteRateLimiterIOS();
		/// Destroys the stream.

	ByteRateLimiterStreamBuf* rdbuf();
		/// Returns a pointer to the underlying streambuf.

protected:
	ByteRateLimiterStreamBuf _buf;
};


class Foundation_API ByteRateLimiterOutputStream : public std::ostream, public ByteRateLimiterIOS
	/// This stream limits the byte rate of data
	/// going through it.
{
public:
	ByteRateLimiterOutputStream(std::ostream& ostr, std::streamsize targetrate, Poco::Clock::ClockDiff interval = ByteRateLimiter::INTERVAL_SECOND);
		/// Creates the ByteRateLimiterOutputStream and connects it
		/// to the given output stream.

	~ByteRateLimiterOutputStream();
		/// Destroys the stream.

};


class Foundation_API ByteRateLimiterInputStream : public std::istream, public ByteRateLimiterIOS
	/// This stream limits the byte rate of data
	/// going through it.
{
public:
	ByteRateLimiterInputStream(std::istream& istr, std::streamsize targetrate, Poco::Clock::ClockDiff interval = ByteRateLimiter::INTERVAL_SECOND);
		/// Creates the ByteRateLimiterInputStream and connects it
		/// to the given input stream.

	~ByteRateLimiterInputStream();
		/// Destroys the ByteRateLimiterInputStream.

};


} // namespace Poco


#endif // Foundation_ByteRateLimiterStream_INCLUDED
