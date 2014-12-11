//
// ASN1FactoryDefault.cpp
//
// $Id: //poco/1.4/Foundation/src/ASN1FactoryDefault.cpp#1 $
//
// Library: Foundation
// Package: Streams
// Module:  ASN1FactoryDefault
//
// Copyright (c) 2010, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/ASN1FactoryDefault.h"
#include "Poco/ASN1Types.h"


namespace Poco {


ASN1::Ptr ASN1FactoryDefault::create(ASN1::Type type)
{
	switch (type)
	{
	case ASN1::None: return new ASN1Types::Null;
    case ASN1::Boolean: return new ASN1Types::Boolean;
    case ASN1::Integer: return new ASN1Types::Integer;
    case ASN1::OctetString: return new ASN1Types::OctetString;
    case ASN1::Null: return new ASN1Types::Null;
    case ASN1::ObjectIdentifier: return new ASN1Types::ObjectIdentifier;
    case ASN1::Sequence: return new ASN1Types::Sequence;
    default:
        //assert(false, "factory method", Poco::format("Unknown type: %d", type));
		return new ASN1Types::Unknown(type);
    };

    //return NullObject::Instance();
}


} // namespace Poco
