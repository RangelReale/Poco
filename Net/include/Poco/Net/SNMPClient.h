//
// SNMPClient.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/SNMPClient.h#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPClient
//
// Definition of the SNMPClient class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_SNMPClient_INCLUDED
#define Net_SNMPClient_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/SNMPRawEventArgs.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/ASN1.h"
#include "Poco/BasicEvent.h"


namespace Poco {
namespace Net {


class Net_API SNMPClient
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

	SNMPClient();

	explicit SNMPClient(const SocketAddress& listenAddr);
		/// Creates an ICMP client.
		///
		/// If using raw socket, most operating systems requires root access.
		/// Non-raw sockets are not available in all platforms, if not available
		/// NotImplementedException is thrown.

	~SNMPClient();
		/// Destroys the ICMP client.

	ASN1::Ptr query(SocketAddress& address, ASN1::Ptr query);
		/// Pings the specified address [repeat] times.
		/// Notifications are posted for events.
		/// 
		/// Returns the number of valid replies.

	ASN1::Ptr query(const std::string& address, ASN1::Ptr query);
		/// Calls ICMPClient::ping(SocketAddress&, int) and
		/// returns the result.
		/// 
		/// Returns the number of valid replies.

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


#endif // Net_SNMPClient_INCLUDED
