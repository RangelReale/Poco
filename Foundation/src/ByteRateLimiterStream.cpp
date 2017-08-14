//
// ByteRateLimiterStream.cpp
//
// $Id: //poco/1.4/Foundation/src/ByteRateLimiterStream.cpp#1 $
//
// Library: Foundation
// Package: Streams
// Module:  ByteRateLimiterStream
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/ByteRateLimiterStream.h"


namespace Poco {


ByteRateLimiterStreamBuf::ByteRateLimiterStreamBuf(std::istream& istr, std::streamsize targetrate, Poco::Clock::ClockDiff interval):
	BufferedStreamBuf(1024, std::ios::in),
	_pIstr(&istr),
	_pOstr(0),
	_limiter(targetrate, interval)
{
}


ByteRateLimiterStreamBuf::ByteRateLimiterStreamBuf(std::ostream& ostr, std::streamsize targetrate, Poco::Clock::ClockDiff interval):
	BufferedStreamBuf(1024, std::ios::out),
	_pIstr(0),
	_pOstr(&ostr),
	_limiter(targetrate, interval)
{
}


ByteRateLimiterStreamBuf::~ByteRateLimiterStreamBuf()
{
}


int ByteRateLimiterStreamBuf::readFromDevice(char* buffer, std::streamsize length)
{
	if (_pIstr)
	{
		int n = 0;
		if (_pIstr->good())
		{
			_pIstr->read(buffer, length);
			n = static_cast<int>(_pIstr->gcount());
		}
		_limiter.addBytes(n);
		return n;
	}
	return -1;
}


int ByteRateLimiterStreamBuf::writeToDevice(const char* buffer, std::streamsize length)
{
	if (_pOstr)
	{
		int n = 0;
		if (_pOstr->good())
		{
			_pOstr->write(buffer, length);
			n = length;
		}
		_limiter.addBytes(n);
		return n;
	}
	return -1;
}


ByteRateLimiterIOS::ByteRateLimiterIOS(std::istream& istr, std::streamsize targetrate, Poco::Clock::ClockDiff interval) :
	_buf(istr, targetrate, interval)
{
	poco_ios_init(&_buf);
}


ByteRateLimiterIOS::ByteRateLimiterIOS(std::ostream& ostr, std::streamsize targetrate, Poco::Clock::ClockDiff interval) :
	_buf(ostr, targetrate, interval)
{
	poco_ios_init(&_buf);
}


ByteRateLimiterIOS::~ByteRateLimiterIOS()
{

}


ByteRateLimiterStreamBuf* ByteRateLimiterIOS::rdbuf()
{
	return &_buf;
}


ByteRateLimiterOutputStream::ByteRateLimiterOutputStream(std::ostream& ostr, std::streamsize targetrate, Poco::Clock::ClockDiff interval) :
	std::ostream(&_buf),
	ByteRateLimiterIOS(ostr, targetrate, interval)
{
}


ByteRateLimiterOutputStream::~ByteRateLimiterOutputStream()
{
}


ByteRateLimiterInputStream::ByteRateLimiterInputStream(std::istream& istr, std::streamsize targetrate, Poco::Clock::ClockDiff interval) :
	std::istream(&_buf),
	ByteRateLimiterIOS(istr, targetrate, interval)
{
}


ByteRateLimiterInputStream::~ByteRateLimiterInputStream()
{
}


} // namespace Poco
