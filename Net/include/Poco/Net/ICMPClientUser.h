//
// ICMPClientUser.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/ICMPClientUser.h#1 $
//
// Library: Net
// Package: ICMP
// Module:  ICMPClientUser
//
// Definition of the ICMPClientUser class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_ICMPClientUser_INCLUDED
#define Net_ICMPClientUser_INCLUDED


#include "Poco/Net/Net.h"


#if defined(POCO_OS_FAMILY_WINDOWS)
#include "Poco/Net/ICMPClientUser_WIN32.h"
#else
#include "Poco/Net/ICMPClientUser_DEFAULT.h"
#endif


namespace Poco {
namespace Net {


class Net_API ICMPClientUser : public ICMPClientUserImpl
	/// This class provides ICMP Ping functionality, without 
	/// requiring root permission if possible.
	///
	/// The events are available when class is instantiated
	///	and non-static member functions are called.
	/// 
	///	A "lightweight" alternative is direct (without instantiation)
	///	use of static member functions.
{
public:
	explicit ICMPClientUser(IPAddress::Family family);
		/// Creates an ICMP client.
};


} } // namespace Poco::Net


#endif // Net_ICMPClientUser_INCLUDED
