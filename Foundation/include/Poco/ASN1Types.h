//
// ASN1Types.h
//
// $Id: //poco/1.4/Foundation/include/Poco/ASN1Types.h#1 $
//
// Library: Foundation
// Package: Streams
// Module:  ASN1Types
//
// Definition of the ASN1Types class.
//
// Copyright (c) 2010, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_ASN1Types_INCLUDED
#define Foundation_ASN1Types_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/ASN1.h"
#include "Poco/SharedPtr.h"

#include <vector>

namespace Poco {
namespace ASN1Types {


class Foundation_API Unknown : public ASN1
{
public:
	Unknown(ASN1::Type type);

	std::string toString() const;
	std::string typeName() const;

	const std::string &getValue() const;

	void dump(std::ostream &stream, int ident) const;
protected:
	Poco::UInt32 getDataLength() const;
    void encodeData(Poco::BinaryWriter &stream) const;
	void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length);
private:
	std::string _value;
};


class Foundation_API Null : public ASN1
	/// 
{
public:
	Null();

	std::string toString() const;
	std::string typeName() const;

	void dump(std::ostream &stream, int ident) const;
protected:
	Poco::UInt32 getDataLength() const;
    void encodeData(Poco::BinaryWriter &stream) const;
	void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length);
};


class Foundation_API NullObject : public ASN1
{
public:
    static NullObject *Instance();

	std::string toString() const;
	std::string typeName() const;
protected:
	NullObject();

	Poco::UInt32 getDataLength() const;
    void encodeData(Poco::BinaryWriter &stream) const;
	void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length);
};


class Foundation_API Boolean : public ASN1
{
public:
	Boolean();
	Boolean(bool value);

	bool getValue() const;

	std::string toString() const;
	std::string typeName() const;
protected:
	Poco::UInt32 getDataLength() const;
    void encodeData(Poco::BinaryWriter &stream) const;
	void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length);
private:
	bool _value;
};


class Foundation_API Integer : public ASN1
{
public:
	Integer();
	Integer(Poco::UInt32 value);
	Integer(ASN1::Type type, Poco::UInt32 value);

	Poco::UInt32 getValue() const;

	std::string toString() const;
	std::string typeName() const;

	void dump(std::ostream &stream, int ident) const;
protected:
	Poco::UInt32 getDataLength() const;
    void encodeData(Poco::BinaryWriter &stream) const;
	void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length);
private:
	Poco::UInt32 _value;
};


class Foundation_API OctetString : public ASN1
{
public:
	OctetString();
	OctetString(const std::string &value);
	OctetString(ASN1::Type type, const std::string &value = "");

	std::string getValue() const;

	std::string toString() const;
	std::string typeName() const;

	void dump(std::ostream &stream, int ident) const;
protected:
	Poco::UInt32 getDataLength() const;
    void encodeData(Poco::BinaryWriter &stream) const;
	void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length);
private:
	std::string _value;
};


class Foundation_API ObjectIdentifier : public ASN1
{
public:
	ObjectIdentifier();
	ObjectIdentifier(const std::string &value);

	std::string toString() const;
	std::string typeName() const;

	void dump(std::ostream &stream, int ident) const;
protected:
	Poco::UInt32 getDataLength() const;
    void encodeData(Poco::BinaryWriter &stream) const;
	void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length);
private:
	std::vector<Poco::UInt32> _value;
};


class SequenceData : public std::vector<ASN1::Ptr>
{
public:
	SequenceData();
	SequenceData(ASN1::Ptr v1, ASN1::Ptr v2 = NULL, ASN1::Ptr v3 = NULL);
};


class Sequence : public ASN1
{
public:
	Sequence();
	Sequence(ASN1::Type type);
	Sequence(const SequenceData &value);
	Sequence(ASN1::Type type, const SequenceData &value);

	const SequenceData &getSequenceData() const;

	std::string typeName() const;

	void dump(std::ostream &stream, int ident) const;
protected:
	ASN1::Ptr getDataType(int pos) const;

	Poco::UInt32 getDataLength() const;
    void encodeData(Poco::BinaryWriter &stream) const;
	void decodeData(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream, Poco::UInt32 length);

	SequenceData _value;
};


} } // namespace Poco::ASN1Types


#endif // Foundation_ASN1Types_INCLUDED