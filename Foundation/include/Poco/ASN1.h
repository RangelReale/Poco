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

#include <iostream>
#include <utility>


namespace Poco {


class ASN1Factory;


class Foundation_API ASN1Type
{
public:
	enum ClassType {
		Universal = 0x0,
		Application = 0x1,
		ContextSpecific = 0x2,
		Private = 0x3,
	};

	enum UniversalType {
		None = 0x00,
		Boolean = 0x01,
		Integer = 0x02,
		OctetString = 0x04,
		Null = 0x05,
		ObjectIdentifier = 0x06,
		Sequence = 0x10,
	};

	ASN1Type();
	ASN1Type(Poco::UInt8 aclass, bool primitive, Poco::UInt32 tag);
	explicit ASN1Type(UniversalType utype, bool universalMarker);
	ASN1Type(Poco::UInt8 simpleclass);

	Poco::UInt8 aclass() const;
	bool primitive() const;
	Poco::UInt32 tag() const;

	Poco::UInt8 rawValue() const;
	Poco::UInt8 universalValue() const;

	Poco::UInt32 getDataLength() const;
    void encodeData(Poco::BinaryWriter &stream) const;
	Poco::UInt8 decodeData(Poco::BinaryReader &stream);
private:
	Poco::UInt8 _aclass;
	bool _primitive;
	Poco::UInt32 _tag;
};


class Foundation_API ASN1 : public Poco::RefCountedObject
	/// This is the base class for ASN.1 types.
{
public:
	typedef Poco::AutoPtr<ASN1> Ptr;

	typedef Poco::UInt8 Type;

	ASN1(ASN1Type type);

	virtual ~ASN1();
	
	const ASN1Type &getType() const;

    void encode(Poco::BinaryWriter &stream) const;

    Poco::UInt32 decode(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream);

	Poco::UInt32 getLength() const;

	virtual std::string toString() const;
	virtual std::string typeName() const;

	virtual void dump(std::ostream &stream, int ident = 0) const;

	static std::pair<Poco::UInt32, Poco::UInt32> parseBase128Int(Poco::BinaryReader &stream);
	static void writeBase128Int(Poco::UInt32 value, Poco::BinaryWriter &stream);
	static Poco::UInt32 sizeBase128Int(Poco::UInt32 value);
protected:
	virtual Poco::UInt32 getDataLength() const = 0;
    virtual void encodeData(Poco::BinaryWriter &stream) const = 0;
	virtual void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length) = 0;
private:
	ASN1Type _type;
};


class Foundation_API ASN1Factory
	/// This class is a factory for ASN1 objects.
{
public:
	typedef Poco::SharedPtr<ASN1Factory> Ptr;

	virtual ~ASN1Factory() {}

	virtual ASN1::Ptr create(ASN1Type type) = 0;
};


} // namespace Poco


#endif // Foundation_ASN1_INCLUDED
