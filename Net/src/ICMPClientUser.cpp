//
// ICMPClientUser.cpp
//
// $Id: //poco/1.4/Net/src/ICMPClientUser.cpp#1 $
//
// Library: Net
// Package: ICMP
// Module:  ICMPClientUser
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Net/ICMPClientUser.h"


#if defined(POCO_OS_FAMILY_WINDOWS)
#include "ICMPClientUser_WIN32.cpp"
#else
#include "ICMPClientUser_DEFAULT.cpp"
#endif


namespace Poco {
namespace Net {


ICMPClientUser::ICMPClientUser(IPAddress::Family family): 
	ICMPClientUserImpl(family)
{
}


} } // namespace Poco::Net
