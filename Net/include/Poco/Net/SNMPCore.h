//
// SNMPCore.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/SNMPCore.h#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPCore
//
// Definition of the SNMPCore class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_SNMPCore_INCLUDED
#define Net_SNMPCore_INCLUDED


#include "Poco/Net/Net.h"


namespace Poco {
namespace Net {


class Net_API SNMPVersion
{
public:
	enum Version {
		SNMPv1 =	0,
		SNMPv2c =	2
	};
};


class Net_API SNMP_ASN1
	/// This class provides ICMP Ping functionality.
	///
	/// The events are available when class is instantiated
	///	and non-static member functions are called.
	/// 
	///	A "lightweight" alternative is direct (without instantiation)
	///	use of static member functions.
{
public:
	enum BERType {
		IPAddress = 0x40,
		Counter32 = 0x41,
		Gauge32 = 0x42,
		TimeTicks = 0x43,

		GetRequestPDU = 0xa0,
		GetNextRequestPDU = 0xa1,
		GetResponsePDU = 0xa2
	};
};


} } // namespace Poco::Net


#endif // Net_SNMPCore_INCLUDED
