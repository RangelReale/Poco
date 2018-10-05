//
// NumericSizeFormat.cpp
//
// $Id: //poco/1.4/Foundation/src/NumericSizeFormat.cpp#4 $
//
// Library: Foundation
// Package: Core
// Module:  NumericSizeFormat
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/NumericSizeFormat.h"
#include "Poco/Format.h"


namespace Poco {


std::string NumericSizeFormat::getUnit(unsigned int index)
{
	const static char* units[] = { "B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
	if (index >= sizeof(units))
		return "";
	return units[index];
}


std::string NumericSizeFormat::format(double size, unsigned int index)
{
	return Poco::format("%.2f %s", size, getUnit(index));
}


} // namespace Poco
