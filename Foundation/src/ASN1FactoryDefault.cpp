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


namespace Poco {


ASN1::Ptr ASN1FactoryDefault::create(ASN1::Type type)
{
	return ASN1::Ptr();
}


} // namespace Poco
