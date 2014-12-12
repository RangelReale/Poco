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
	return Poco::ASN1Types::OctetString::toString();
}


} } } // namespace Poco::Net::ASN1Types
