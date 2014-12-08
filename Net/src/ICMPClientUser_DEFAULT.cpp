//
// ICMPClient_DEFAULT.cpp
//
// $Id: //poco/1.4/Net/src/ICMPClient_DEFAULT.cpp#1 $
//
// Library: Net
// Package: ICMP
// Module:  ICMPClientUserImpl
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Net/ICMPClientUser_DEFAULT.h"


namespace Poco {
namespace Net {


ICMPClientUserImpl::ICMPClientUserImpl(IPAddress::Family family): 
	ICMPClient(family)
{
}


} } // namespace Poco::Net
