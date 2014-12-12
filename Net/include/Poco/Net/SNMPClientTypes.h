//
// SNMPClientTypes.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/SNMPClientTypes.h#1 $
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


#ifndef Net_SNMPClientTypes_INCLUDED
#define Net_SNMPClientTypes_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/ASN1.h"
#include "Poco/RefCountedObject.h"

#include <vector>

namespace Poco {
namespace Net {
namespace SNMPTypes {


class Net_API VarBind : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<VarBind> Ptr;

	VarBind();
	VarBind(ASN1::Ptr data);
	VarBind(const std::string oid, ASN1::Ptr data);

	const std::string &oid() const;
	void setOid(const std::string &value);

	ASN1::Ptr value() const;
	void setValue(ASN1::Ptr value);

	void decode(ASN1::Ptr data);
	ASN1::Ptr encode();
private:
	std::string _oid;
	ASN1::Ptr _value;
};


class Net_API VarBindList : public Poco::RefCountedObject
{
public:
	typedef std::vector<VarBind::Ptr> list_t;

	VarBindList();
	VarBindList(ASN1::Ptr data);

	void clear();
	void add(VarBind::Ptr value);

	list_t &list();

	void decode(ASN1::Ptr data);
	ASN1::Ptr encode();
private:
	list_t _list;
};


class Net_API PDU : public Poco::RefCountedObject
{
public:
	PDU();
	PDU(ASN1::Ptr data);

	ASN1::Type type() const;
	void setType(ASN1::Type value);

	int requestId() const;
	void setRequestId(int value);

	int error() const;
	void setError(int value);

	int errorIndex() const;
	void setErrorIndex(int value);

	VarBindList &varBindList();

	void decode(ASN1::Ptr data);
	ASN1::Ptr encode();
private:
	ASN1::Type _type;
	int _requestid;
	int _error;
	int _errorindex;
	VarBindList _varbindlist;
};


class Net_API SNMPMessage : public Poco::RefCountedObject
{
public:
	typedef Poco::AutoPtr<SNMPMessage> Ptr;

	SNMPMessage();
	SNMPMessage(ASN1::Ptr data);

	int version() const;
	void setVersion(int value);

	const std::string &community() const;
	void setCommunity(const std::string &value);

	PDU &pdu();

	void decode(ASN1::Ptr data);
	ASN1::Ptr encode();
private:
	int _version;
	std::string _community;
	PDU _pdu;
};


} } } // namespace Poco::Net::SNMPTypes


#endif // Net_SNMPClientTypes_INCLUDED
