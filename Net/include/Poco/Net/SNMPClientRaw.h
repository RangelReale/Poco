//
// SNMPClientRaw.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/SNMPClientRaw.h#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPClientRaw
//
// Definition of the SNMPClientRaw class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_SNMPClientRaw_INCLUDED
#define Net_SNMPClientRaw_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/SNMPRawEventArgs.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/ASN1.h"
#include "Poco/BasicEvent.h"


namespace Poco {
namespace Net {


class Net_API SNMPClientRaw
	/// This class provides ICMP Ping functionality.
	///
	/// The events are available when class is instantiated
	///	and non-static member functions are called.
	/// 
	///	A "lightweight" alternative is direct (without instantiation)
	///	use of static member functions.
{
public:
	mutable Poco::BasicEvent<SNMPRawEventArgs> snmpReply;
	mutable Poco::BasicEvent<SNMPRawEventArgs> snmpError;

	SNMPClientRaw();

	explicit SNMPClientRaw(const SocketAddress& listenAddr);
		/// Creates an ICMP client.
		///
		/// If using raw socket, most operating systems requires root access.
		/// Non-raw sockets are not available in all platforms, if not available
		/// NotImplementedException is thrown.

	~SNMPClientRaw();
		/// Destroys the ICMP client.

	void send(SocketAddress& address, ASN1::Ptr query);
		/// Pings the specified address [repeat] times.
		/// Notifications are posted for events.
		/// 
		/// Returns the number of valid replies.

	void send(const std::string& address, ASN1::Ptr query);
		/// Calls ICMPClient::ping(SocketAddress&, int) and
		/// returns the result.
		/// 
		/// Returns the number of valid replies.

private:
	Poco::Net::DatagramSocket _socket;
};


} } // namespace Poco::Net


#endif // Net_ICMPClient_INCLUDED
