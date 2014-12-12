//
// SNMPRawEventArgs.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/SNMPRawEventArgs.h#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPRawEventArgs
//
// Definition of SNMPRawEventArgs.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_SNMPRawEventArgs_INCLUDED
#define Net_SNMPRawEventArgs_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/ASN1.h"


namespace Poco {
namespace Net {


class Net_API SNMPRawEventArgs
	/// The purpose of the ICMPEventArgs class is to be used as template parameter
	/// to instantiate event members in ICMPClient class.
	/// When clients register for an event notification, the reference to the class is 
	///	passed to the handler function to provide information about the event.
{
public:
	SNMPRawEventArgs(const SocketAddress& address);
		/// Creates ICMPEventArgs.

	virtual ~SNMPRawEventArgs();
		/// Destroys ICMPEventArgs.

	std::string hostName() const;
		/// Tries to resolve the target IP address into host name.
		/// If unsuccessful, all exceptions are silently ignored and 
		///	the IP address is returned.

	std::string hostAddress() const;
		/// Returns the target IP address.

	ASN1::Ptr response() const;
		/// Returns the number of repetitions for the ping operation.

	const std::string &error() const;
		/// Returns the number of repetitions for the ping operation.

private:
	SNMPRawEventArgs();

	void setResponse(ASN1::Ptr response);
	void setError(const std::string &error);

	SocketAddress _address;
	int _requestid;
	ASN1::Ptr _response;
	std::string _error;

	friend class SNMPClientRaw;
};


} } // namespace Poco::Net


#endif // Net_SNMPRawEventArgs_INCLUDED
