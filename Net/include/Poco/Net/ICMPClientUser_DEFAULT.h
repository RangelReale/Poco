//
// ICMPClient_DEFAULT.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/ICMPClient_DEFAULT.h#1 $
//
// Library: Net
// Package: ICMP
// Module:  ICMPClientUserImpl
//
// Definition of the ICMPClientUserImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_ICMPClientUser_DEFAULT_INCLUDED
#define Net_ICMPClientUser_DEFAULT_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/ICMPClient.h"


namespace Poco {
namespace Net {


class Net_API ICMPClientUserImpl : public ICMPClient
{
public:
	explicit ICMPClientUserImpl(IPAddress::Family family);
		/// Creates an ICMP client.
};


} } // namespace Poco::Net


#endif // Net_ICMPClientUser_DEFAULT_INCLUDED
