//
// NumericSizeFormatter.cpp
//
// $Id: //poco/1.4/Foundation/src/NumericSizeFormatter.cpp#4 $
//
// Library: Foundation
// Package: Core
// Module:  NumericSizeFormatter
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/NumericSizeFormatter.h"
#include "Poco/Format.h"


namespace Poco {


std::string NumericSizeFormatter::format(std::streamsize size, const std::string &suffix)
{
	return format(static_cast<double>(size), suffix);
}


std::string NumericSizeFormatter::format(double size, const std::string &suffix)
{
	static NumericSizeFormat defaultFormat;
	return format(defaultFormat, size, suffix);
}


std::string NumericSizeFormatter::format(NumericSizeFormat &format, std::streamsize size, const std::string &suffix)
{
	return NumericSizeFormatter::format(format, static_cast<double>(size), suffix);
}


std::string NumericSizeFormatter::format(NumericSizeFormat &format, double size, const std::string &suffix)
{
	unsigned int i = 0;
	while (size > 1024) {
		size /= 1024.0;
		i++;
	}
	std::string ret = format.format(size, i);
	if (!suffix.empty())
		ret.append(suffix);
	return ret;
}


} // namespace Poco