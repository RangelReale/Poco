//
// Ascii.cpp
//
// $Id: //poco/1.4/Foundation/src/Ascii.cpp#1 $
//
// Library: Foundation
// Package: Core
// Module:  Ascii
//
// Copyright (c) 2010, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/ASN1.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"


namespace Poco {


static const Poco::UInt8 TYPE_SIZE = 1;


ASN1::ASN1(Type type) : _type(type)
{

}


ASN1::~ASN1()
{

}

	
ASN1::Type ASN1::getType() const
{
	return _type;
}


void ASN1::encode(Poco::BinaryWriter &stream) const
{
	Poco::UInt32 dataLength = getDataLength();

	stream << static_cast<Poco::UInt8>(_type);

	if (dataLength > 127)
	{
		Poco::UInt8 numBytes = 1;
		Poco::UInt32 ll = dataLength;
		while (ll > 255)
		{
			numBytes++;
			ll >>= 8;
		}
		stream << (Poco::UInt8)(0x80 | numBytes);

		for (ll=numBytes; ll>0; ll--)
		{
			stream << (Poco::UInt8)(dataLength >> Poco::UInt32((ll-1)*8));
		}
	}
	else
		stream << (Poco::UInt8)dataLength;

	encodeData(stream);
}


Poco::UInt32 ASN1::decode(Poco::SharedPtr<ASN1Factory> factory, Poco::BinaryReader &stream)
{
	Poco::UInt32 length = 0;
    Poco::UInt8 dataLength = 0;
	Poco::UInt8 lengthSize = 1;
    stream >> dataLength;

	int tag = int(dataLength & 0x1f);
	if (tag == 0x1f)
		throw DataFormatException("Base128 encoded, cannot parse");

	if ((dataLength & 0x80) == 0)
	{
		length = dataLength;
	}
	else
	{
		// Bottom 7 bits give the number of length bytes to follow.
		int numBytes = dataLength & 0x7f;
		if (numBytes == 0)
			throw DataFormatException("indefinite length found (not DER)");

		lengthSize += numBytes;

		for (int i=0; i < numBytes; i++)
		{
			stream >> dataLength;
			
			if (length >= 1<<23)
				throw DataFormatException("length too large");

			length <<= 8;
			length |= int(dataLength);

			//if (length == 0)
				//throw DataFormatException("superfluous leading zeros in length");
		}
	}

	decodeData(factory, stream, length);

	return lengthSize + length;
}


Poco::UInt32 ASN1::getLength() const
{
	Poco::UInt32 dataLength = getDataLength();
	Poco::UInt8 lengthSize = 1;

	if (dataLength > 127)
	{
		lengthSize++;
		while (dataLength > 255)
		{
			lengthSize++;
			dataLength >>= 8;
		}
	}

    return TYPE_SIZE + lengthSize + getDataLength();
}


std::string ASN1::toString() const
{
	return Poco::format("[item type 0x%s]", Poco::NumberFormatter::formatHex(_type));
}


std::string ASN1::typeName() const
{
	return Poco::format("0x%s", Poco::NumberFormatter::formatHex(_type));
}


struct Whitespace
{
    Whitespace(int n)
        : n(n)
    {
    }
    int n;
};

std::ostream& operator<<(std::ostream& stream, const Whitespace &ws)
{
    for(int i = 0; i < ws.n; i++)
    {
        stream << "   ";
    }
    return stream;
}


void ASN1::dump(std::ostream &stream, int ident) const
{
	stream << Whitespace(ident) << "ASN.1 0x" << Poco::NumberFormatter::formatHex(_type) << " " << getDataLength() << " BYTES" << std::endl;
}


} // namespace Poco
