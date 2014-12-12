//
// SNMPClientRawFactory.cpp
//
// $Id: //poco/1.4/Net/src/SNMPClientRawFactory.cpp#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPClientRawFactory
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Net/SNMPClientRawFactory.h"
#include "Poco/Net/SNMPClientRawTypes.h"


namespace Poco {
namespace Net {


ASN1::Ptr SNMPClientRawFactory::create(ASN1::Type type)
{
	switch (type)
	{
	case ASN1Types::SNMP_ASN1::IPAddress: return new ASN1Types::IPAddress;
	case ASN1Types::SNMP_ASN1::Counter32: return new Poco::ASN1Types::Integer(type, 0);
	case ASN1Types::SNMP_ASN1::GetRequestPDU: 
	case ASN1Types::SNMP_ASN1::GetNextRequestPDU:
	case ASN1Types::SNMP_ASN1::GetResponsePDU:
		return new Poco::ASN1Types::Sequence(type);
	}
	return ASN1FactoryDefault::create(type);
}


} } // namespace Poco::Net
