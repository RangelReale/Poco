//
// NumericSizeFormatter.h
//
// $Id: //poco/1.4/Foundation/include/Poco/NumericSizeFormatter.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  NumericSizeFormatter
//
// Definition of the NumericSizeFormatter class.
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_NumericSizeFormatter_INCLUDED
#define Foundation_NumericSizeFormatter_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/NumericSizeFormat.h"

#include <iostream>

namespace Poco {


class Foundation_API NumericSizeFormatter
	/// The NumericSizeFormatter class provides static methods
	/// for formatting numeric (byte) values into strings.
{
public:
	static std::string format(std::streamsize size, const std::string &suffix = "");
		/// Formats an integer value in byte notation, with an optional suffix.

	static std::string format(double size, const std::string &suffix = "");
		/// Formats an float value in byte notation, with an optional suffix.

	static std::string format(NumericSizeFormat &format, std::streamsize size, const std::string &suffix = "");
		/// Formats an integer value in byte notation, with an optional suffix, using the passed format.

	static std::string format(NumericSizeFormat &format, double size, const std::string &suffix = "");
		/// Formats an integer value in byte notation, with an optional suffix, using the passed format.

};


}


#endif // Foundation_NumericSizeFormatter_INCLUDED
