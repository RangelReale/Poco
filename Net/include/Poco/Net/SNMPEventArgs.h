//
// SNMPEventArgs.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/SNMPEventArgs.h#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPEventArgs
//
// Definition of SNMPEventArgs.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_SNMPEventArgs_INCLUDED
#define Net_SNMPEventArgs_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SNMPClientTypes.h"


namespace Poco {
namespace Net {


class Net_API SNMPEventArgs
	/// The purpose of the ICMPEventArgs class is to be used as template parameter
	/// to instantiate event members in ICMPClient class.
	/// When clients register for an event notification, the reference to the class is 
	///	passed to the handler function to provide information about the event.
{
public:
	SNMPEventArgs(const SocketAddress& address);
		/// Creates ICMPEventArgs.

	virtual ~SNMPEventArgs();
		/// Destroys ICMPEventArgs.

	std::string hostName() const;
		/// Tries to resolve the target IP address into host name.
		/// If unsuccessful, all exceptions are silently ignored and 
		///	the IP address is returned.

	std::string hostAddress() const;
		/// Returns the target IP address.

	SNMPTypes::SNMPMessage::Ptr message() const;
		/// Returns the number of repetitions for the ping operation.

	Poco::ASN1::Ptr rawMessage() const;
		/// Returns the number of repetitions for the ping operation.

	const std::string &error() const;
		/// Returns the number of repetitions for the ping operation.

	bool abort() const;

	void setAbort(bool value);

private:
	SNMPEventArgs();

	void setMessage(SNMPTypes::SNMPMessage::Ptr message);
	void setRawMessage(Poco::ASN1::Ptr rawmessage);
	void setError(const std::string &error);

	SocketAddress _address;
	int _requestid;
	SNMPTypes::SNMPMessage::Ptr _message;
	Poco::ASN1::Ptr _rawmessage;
	std::string _error;
	bool _abort;

	friend class SNMPClient;
};


} } // namespace Poco::Net


#endif // Net_SNMPEventArgs_INCLUDED
