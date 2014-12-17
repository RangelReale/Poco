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
#include "Poco/Net/SNMPCore.h"
#include "Poco/Net/SNMPEventArgs.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SNMPClientTypes.h"
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
	mutable Poco::BasicEvent<SNMPEventArgs> snmpBegin;
	mutable Poco::BasicEvent<SNMPEventArgs> snmpReply;
	mutable Poco::BasicEvent<SNMPEventArgs> snmpError;
	mutable Poco::BasicEvent<SNMPEventArgs> snmpEnd;

	SNMPClient();

	~SNMPClient();
		/// Destroys the ICMP client.

	void send(SocketAddress& address, SNMPTypes::SNMPMessage::Ptr message);
		/// Pings the specified address [repeat] times.
		/// Notifications are posted for events.
		/// 
		/// Returns the number of valid replies.

	void send(const std::string& address, SNMPTypes::SNMPMessage::Ptr message);
		/// Calls ICMPClient::ping(SocketAddress&, int) and
		/// returns the result.
		/// 
		/// Returns the number of valid replies.

	void get(SocketAddress& address, const std::string &oid, int requestId = 0, 
		SNMPVersion::Version version = SNMPVersion::SNMPv1);
		/// Pings the specified address [repeat] times.
		/// Notifications are posted for events.
		/// 
		/// Returns the number of valid replies.

	void get(const std::string& address, const std::string &oid, int requestId = 0,
		SNMPVersion::Version version = SNMPVersion::SNMPv1);
		/// Calls ICMPClient::ping(SocketAddress&, int) and
		/// returns the result.
		/// 
		/// Returns the number of valid replies.

	void walk(SocketAddress& address, const std::string &oid, int requestId = 0,
		SNMPVersion::Version version = SNMPVersion::SNMPv1);
		/// Pings the specified address [repeat] times.
		/// Notifications are posted for events.
		/// 
		/// Returns the number of valid replies.

	void walk(const std::string& address, const std::string &oid, int requestId = 0,
		SNMPVersion::Version version = SNMPVersion::SNMPv1);
		/// Calls ICMPClient::ping(SocketAddress&, int) and
		/// returns the result.
		/// 
		/// Returns the number of valid replies.
};


} } // namespace Poco::Net


#endif // Net_SNMPClient_INCLUDED
