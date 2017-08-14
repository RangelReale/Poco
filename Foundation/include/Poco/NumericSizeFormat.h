//
// NumericSizeFormat.h
//
// $Id: //poco/1.4/Foundation/include/Poco/NumericSizeFormat.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  NumericSizeFormat
//
// Definition of the NumericSizeFormat class.
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_NumericSizeFormat_INCLUDED
#define Foundation_NumericSizeFormat_INCLUDED


#include "Poco/Foundation.h"
#include <string>


namespace Poco {


class Foundation_API NumericSizeFormat
	/// The NumericSizeFormat class provides static methods
	/// for formatting numeric (byte) sizes into strings.
	/// This class is meant to be used internally in the 
	/// NumericSizeFormatter class.
{
public:
	virtual ~NumericSizeFormat() {}

	virtual std::string getUnit(unsigned int index);
		/// Returns the unit string for the specified index (b, kB, MB, GB, etc)

	virtual std::string format(double value, unsigned int index);
		/// Formats an float value in the specified index

};


} // namespace Poco


#endif // Foundation_NumericSizeFormat_INCLUDED
