//
// ASN1.h
//
// $Id: //poco/1.4/Foundation/include/Poco/ASN1.h#1 $
//
// Library: Foundation
// Package: Streams
// Module:  ASN1
//
// Definition of the ASN1 class.
//
// Copyright (c) 2010, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_ASN1_INCLUDED
#define Foundation_ASN1_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/AutoPtr.h"
#include "Poco/SharedPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"


namespace Poco {


class ASN1Factory;


class Foundation_API ASN1 : public Poco::RefCountedObject
	/// This is the base class for ASN.1 types.
{
public:
	typedef Poco::AutoPtr<ASN1> Ptr;

	typedef Poco::UInt8 Type;

	enum BERType {
		None = 0x00,
		Boolean = 0x01,
		Integer = 0x02,
		OctetString = 0x04,
		Null = 0x05,
		ObjectIdentifier = 0x06,
		Sequence = 0x30,

		NullObject = 0xff
	};

	ASN1(Type type);

	virtual ~ASN1();
	
	Type getType() const;

    void encode(Poco::BinaryWriter &stream) const;

    Poco::UInt32 decode(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream);

	Poco::UInt32 getLength() const;

	virtual std::string toString() const;
protected:
	virtual Poco::UInt32 getDataLength() const = 0;
    virtual void encodeData(Poco::BinaryWriter &stream) const = 0;
	virtual void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length) = 0;
private:
	Type _type;
};


class Foundation_API ASN1Factory
	/// This class is a factory for ASN1 objects.
{
public:
	typedef Poco::SharedPtr<ASN1Factory> Ptr;

	virtual ~ASN1Factory() {}

	virtual ASN1::Ptr create(ASN1::Type type) = 0;
};


} // namespace Poco


#endif // Foundation_ASN1_INCLUDED
