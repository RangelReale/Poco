//
// SNMPClientRawTypes.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/SNMPClientRawTypes.h#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPClientRawTypes
//
// Definition of the SNMPClientRawTypes class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_SNMPClientRawTypes_INCLUDED
#define Net_SNMPClientRawTypes_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/ASN1Types.h"

using namespace Poco::ASN1Types;

namespace Poco {
namespace Net {
namespace ASN1Types {


class Net_API IPAddress : public OctetString
{
public:
	IPAddress();
	IPAddress(const std::string &value);

	std::string toString() const;
	std::string typeName() const;
};


class Net_API Counter32 : public Integer
{
public:
	Counter32();
	Counter32(Poco::UInt32 value);

	std::string typeName() const;
};


class Net_API Gauge32 : public Integer
{
public:
	Gauge32();
	Gauge32(Poco::UInt32 value);

	std::string typeName() const;
};


class Net_API TimeTicks : public Integer
{
public:
	TimeTicks();
	TimeTicks(Poco::UInt32 value);

	std::string typeName() const;
};


} } } // namespace Poco::Net::ASN1Types


#endif // Net_SNMPClientRawTypes_INCLUDED
