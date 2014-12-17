//
// SNMPClientRawTypes.cpp
//
// $Id: //poco/1.4/Net/src/SNMPClientRawTypes.cpp#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPClientRawTypes
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Net/SNMPClientRawTypes.h"
#include "Poco/Net/SNMPCore.h"
#include "Poco/Format.h"


namespace Poco {
namespace Net {
namespace ASN1Types {


///
/// IPAddress
///


IPAddress::IPAddress() : Poco::ASN1Types::OctetString(SNMP_ASN1::IPAddress)
{

}


IPAddress::IPAddress(const std::string &value) : Poco::ASN1Types::OctetString(SNMP_ASN1::IPAddress, value)
{

}


std::string IPAddress::toString() const
{
	if (getValue().size() == 4)
	{
		return Poco::format("%?d.%?d.%?d.%?d", Poco::UInt8(getValue()[0]), Poco::UInt8(getValue()[1]), Poco::UInt8(getValue()[2]), Poco::UInt8(getValue()[3]));
	}
	else if (getValue().size() > 0)
	{
		return "[INVALID IP ADDRESS]";
	}
	return "";
}


std::string IPAddress::typeName() const
{
	return "IPADDRESS";
}


///
/// Counter32
///


Counter32::Counter32() : Integer(SNMP_ASN1::Counter32)
{

}


Counter32::Counter32(Poco::UInt32 value) : Integer(SNMP_ASN1::Counter32, value)
{

}


std::string Counter32::typeName() const
{
	return "COUNTER32";
}


///
/// Gauge32
///


Gauge32::Gauge32() : Integer(SNMP_ASN1::Gauge32)
{

}


Gauge32::Gauge32(Poco::UInt32 value) : Integer(SNMP_ASN1::Gauge32, value)
{

}


std::string Gauge32::typeName() const
{
	return "GAUGE32";
}


///
/// TimeTicks
///


TimeTicks::TimeTicks() : Integer(SNMP_ASN1::TimeTicks)
{

}


TimeTicks::TimeTicks(Poco::UInt32 value) : Integer(SNMP_ASN1::TimeTicks, value)
{

}


std::string TimeTicks::typeName() const
{
	return "TIMETICKS";
}


} } } // namespace Poco::Net::ASN1Types
