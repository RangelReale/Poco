//
// ICMPClientUser_WIN32.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/ICMPClientUser_WIN32.h#1 $
//
// Library: Net
// Package: ICMP
// Module:  ICMPClientUserImpl
//
// Definition of the ICMPClientUserImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_ICMPClientUser_WIN32_INCLUDED
#define Net_ICMPClientUser_WIN32_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/ICMPClientImpl.h"
#include "Poco/Net/ICMPEventArgs.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/BasicEvent.h"


namespace Poco {
namespace Net {


class Net_API ICMPClientUserImpl : public ICMPClientImpl
{
public:
	explicit ICMPClientUserImpl(IPAddress::Family family);
		/// Creates an ICMP client.

	~ICMPClientUserImpl();
		/// Destroys the ICMP client.

	int ping(SocketAddress& address, int repeat = 1) const;
		/// Pings the specified address [repeat] times.
		/// Notifications are posted for events.
		/// 
		/// Returns the number of valid replies.

	int ping(const std::string& address, int repeat = 1) const;
		/// Calls ICMPClient::ping(SocketAddress&, int) and
		/// returns the result.
		/// 
		/// Returns the number of valid replies.

private:
	mutable IPAddress::Family _family;
};


} } // namespace Poco::Net


#endif // Net_ICMPClientUser_WIN32_INCLUDED
