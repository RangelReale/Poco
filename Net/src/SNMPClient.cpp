//
// SNMPClient.cpp
//
// $Id: //poco/1.4/Net/src/SNMPClient.cpp#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPClient
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SNMPClient.h"
#include "Poco/Net/SNMPClientRaw.h"
#include "Poco/Net/SNMPClientRawTypes.h"
#include "Poco/Net/NetException.h"
#include "Poco/Exception.h"
#include <Poco/Delegate.h>

#include <sstream>


using Poco::InvalidArgumentException;
using Poco::NotImplementedException;
using Poco::TimeoutException;
using Poco::Exception;


namespace Poco {
namespace Net {


SNMPClient::SNMPClient()
{
}


SNMPClient::~SNMPClient()
{
}


void SNMPClient::send(const std::string& address, SNMPTypes::SNMPMessage::Ptr message)
{
	SocketAddress addr(address, 161);
	send(addr, message);
}


void SNMPClient::send(SocketAddress& address, SNMPTypes::SNMPMessage::Ptr message)
{
	SNMPClientRaw snmpClient;

	SNMPEventArgs eventArgs(address);
	snmpBegin.notify(this, eventArgs);

	std::string startoid;

	if (message->pdu().type() == ASN1Types::SNMP_ASN1::GetNextRequestPDU)
	{
		if (message->pdu().varBindList().list().size() != 1)
			throw Poco::IllegalStateException("For SNMP GET NEXT, only one VarBind must be requested");

		startoid = message->pdu().varBindList().list().at(0)->oid();
	}

	try
	{
		while (true)
		{
			Poco::ASN1::Ptr resp = snmpClient.query(address, message->encode());
			SNMPTypes::SNMPMessage::Ptr sresp(new SNMPTypes::SNMPMessage(resp));

			eventArgs.setMessage(sresp);
			snmpReply.notify(this, eventArgs);

			if (message->pdu().type() == ASN1Types::SNMP_ASN1::GetNextRequestPDU)
			{
				std::string curoid(sresp->pdu().varBindList().list().at(0)->oid());
				if (curoid.substr(0, startoid.size()) != startoid)
					break;

				message->pdu().varBindList().list()[0]->setOid(curoid);
			}
			else
				break;
		}
	}
	catch (TimeoutException&)
	{
		std::ostringstream os;
		os << address.host().toString() << ": Request timed out.";
		eventArgs.setError(os.str());
		snmpError.notify(this, eventArgs);
	}
	catch (Exception& ex)
	{
		std::ostringstream os;
		os << ex.displayText();
		eventArgs.setError(os.str());
		snmpError.notify(this, eventArgs);
	}
	catch (std::exception& ex)
	{
		std::ostringstream os;
		os << ex.what();
		eventArgs.setError(os.str());
		snmpError.notify(this, eventArgs);
	}

	snmpEnd.notify(this, eventArgs);
}


} } // namespace Poco::Net
