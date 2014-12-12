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


class SNMP_ASN1
{
public:
	enum BERType {
		IPAddress = 0x40,
		Counter32 = 0x41,

		GetRequestPDU = 0xa0,
		GetNextRequestPDU = 0xa1,
		GetResponsePDU = 0xa2
	};
};


class IPAddress : public OctetString
{
public:
	IPAddress();
	IPAddress(const std::string &value);

	std::string toString() const;
};


} } } // namespace Poco::Net::ASN1Types


#endif // Net_SNMPClientRawTypes_INCLUDED
