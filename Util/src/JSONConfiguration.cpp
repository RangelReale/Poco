//
// JSONConfiguration.cpp
//
// $Id$
//
// Library: Util
// Package: JSON
// Module:  JSONConfiguration
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//



#include "Poco/Util/JSONConfiguration.h"


#ifndef POCO_UTIL_NO_JSONCONFIGURATION


#include "Poco/FileStream.h"
#include "Poco/StringTokenizer.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Query.h"
#include "Poco/RegularExpression.h"
#include "Poco/NumberParser.h"


namespace Poco {
namespace Util {


JSONConfiguration::JSONConfiguration() : _object(new JSON::Object())
{
}


JSONConfiguration::JSONConfiguration(const std::string& path)
{
	load(path);
}


JSONConfiguration::JSONConfiguration(std::istream& istr)
{
	load(istr);
}


JSONConfiguration::JSONConfiguration(const JSON::Object::Ptr& object) : _object(object)
{
}


JSONConfiguration::~JSONConfiguration()
{
}


void JSONConfiguration::load(const std::string& path)
{
	Poco::FileInputStream fis(path);
	load(fis);
}


void JSONConfiguration::load(std::istream& istr)
{
	JSON::Parser parser;
	parser.parse(istr);
	DynamicAny result = parser.result();
	if ( result.type() == typeid(JSON::Object::Ptr) )
	{
		_object = result.extract<JSON::Object::Ptr>();
	}
}


void JSONConfiguration::loadEmpty(const std::string& root)
{
	_object = new JSON::Object();
	JSON::Object::Ptr rootObject = new JSON::Object();
	_object->set(root, rootObject);
}


bool JSONConfiguration::getRaw(const std::string & key, std::string & value) const
{
	JSON::Query query(_object);
	Poco::DynamicAny result = query.find(key);
	if ( ! result.isEmpty() )
	{
		value = result.convert<std::string>();
		return true;
	}
	return false;
}


void JSONConfiguration::getIndexes(std::string& name, std::vector<int>& indexes)
{
	indexes.clear();

	RegularExpression::MatchVec matches;
	int firstOffset = -1;
	int offset = 0;
	RegularExpression regex("\\[([0-9]+)\\]");
	while(regex.match(name, offset, matches) > 0 )
	{
		if ( firstOffset == -1 )
		{
			firstOffset = matches[0].offset;
		}
		std::string num = name.substr(matches[1].offset, matches[1].length);
		indexes.push_back(NumberParser::parse(num));
		offset = matches[0].offset + matches[0].length;
	}

	if ( firstOffset != -1 )
	{
		name = name.substr(0, firstOffset);
	}
}


JSON::Object::Ptr JSONConfiguration::findStart(const std::string& key, std::string& lastPart)
{
	JSON::Object::Ptr currentObject = _object;

	StringTokenizer tokenizer(key, ".");
	lastPart = tokenizer[tokenizer.count() - 1];

	for(int i = 0; i < tokenizer.count() - 1; ++i)
	{
		std::vector<int> indexes;
		std::string name = tokenizer[i];
		getIndexes(name, indexes);

		DynamicAny result = currentObject->get(name);

		if ( result.isEmpty() ) // Not found
		{
			if ( indexes.empty() ) // We want an object, create it
			{
				JSON::Object::Ptr newObject = new JSON::Object();
				currentObject->set(name, newObject);
				currentObject = newObject;
			}
			else // We need an array
			{
				JSON::Array::Ptr newArray;
				JSON::Array::Ptr parentArray;
				JSON::Array::Ptr topArray;
				for(std::vector<int>::iterator it = indexes.begin(); it != indexes.end(); ++it)
				{
					newArray = new JSON::Array();
					if ( topArray.isNull() )
					{
						topArray = newArray;
					}

					if ( ! parentArray.isNull() )
					{
						parentArray->add(newArray);
					}

					for(int i = 0; i <= *it - 1; ++i)
					{
						Poco::DynamicAny nullValue;
						newArray->add(nullValue);
					}

					parentArray = newArray;
				}

				currentObject->set(name, topArray);
				currentObject = new JSON::Object();
				newArray->add(currentObject);
			}
		}
		else // We have a value
		{
			if ( indexes.empty() ) // We want an object
			{
				if ( result.type() == typeid(JSON::Object::Ptr) )
				{
					currentObject = result.extract<JSON::Object::Ptr>();
				}
				else
				{
					throw SyntaxException("Expected a JSON object");
				}
			}
			else
			{
				if ( result.type() == typeid(JSON::Array::Ptr) )
				{
					JSON::Array::Ptr arr = result.extract<JSON::Array::Ptr>();

					for(std::vector<int>::iterator it = indexes.begin(); it != indexes.end() - 1; ++it)
					{
						JSON::Array::Ptr currentArray = arr;
						arr = arr->getArray(*it);
						if ( arr.isNull() )
						{
							arr = new JSON::Array();
							currentArray->add(arr);
						}
					}

					result = arr->get(*indexes.rbegin());
					if ( result.isEmpty() ) // Index doesn't exist
					{
						JSON::Object::Ptr newObject = new JSON::Object();
						arr->add(newObject);
						currentObject = newObject;
					}
					else // Index is available
					{
						if ( result.type() == typeid(JSON::Object::Ptr) )
						{
							currentObject = result.extract<JSON::Object::Ptr>();
						}
						else
						{
							throw SyntaxException("Expected a JSON object");
						}
					}
				}
				else
				{
					throw SyntaxException("Expected a JSON array");
				}
			}
		}
	}
	return currentObject;
}


void JSONConfiguration::setValue(const std::string& key, const Poco::DynamicAny& value)
{

	std::string sValue;
	
	value.convert<std::string>(sValue);
	KeyValue kv(key, sValue);
	
	if (eventsEnabled())
	
	{

		propertyChanging(this, kv);
	}
	
	std::string lastPart;
	JSON::Object::Ptr parentObject = findStart(key, lastPart);

	std::vector<int> indexes;
	getIndexes(lastPart, indexes);

	if ( indexes.empty() ) // No Array
	{
		parentObject->set(lastPart, value);
	}
	else
	{
		DynamicAny result = parentObject->get(lastPart);
		if ( result.isEmpty() )
		{
			result = JSON::Array::Ptr(new JSON::Array());
			parentObject->set(lastPart, result);
		}
		else if ( result.type() != typeid(JSON::Array::Ptr) )
		{
			throw SyntaxException("Expected a JSON array");
		}

		JSON::Array::Ptr arr = result.extract<JSON::Array::Ptr>();
		for(std::vector<int>::iterator it = indexes.begin(); it != indexes.end() - 1; ++it)
		{
			JSON::Array::Ptr nextArray = arr->getArray(*it);
			if ( nextArray.isNull()  )
			{
				for(int i = arr->size(); i <= *it; ++i)
				{
					Poco::DynamicAny nullValue;
					arr->add(nullValue);
				}
				nextArray = new JSON::Array();
				arr->add(nextArray);
			}
			arr = nextArray;
		}
		arr->add(value);
	}

	if (eventsEnabled())

	{

		propertyChanged(this, kv);
	}
}


void JSONConfiguration::setString(const std::string& key, const std::string& value)
{
	setValue(key, value);
}


void JSONConfiguration::setRaw(const std::string& key, const std::string& value)
{
	setValue(key, value);
}


void JSONConfiguration::setInt(const std::string& key, int value)
{
	setValue(key, value);
}


void JSONConfiguration::setBool(const std::string& key, bool value)
{
	setValue(key, value);
}


void JSONConfiguration::setDouble(const std::string& key, double value)
{
	setValue(key, value);
}


void JSONConfiguration::enumerate(const std::string& key, Keys& range) const
{
	JSON::Query query(_object);
	Poco::DynamicAny result = query.find(key);
	if ( result.type() == typeid(JSON::Object::Ptr) )
	{
		JSON::Object::Ptr object = result.extract<JSON::Object::Ptr>();
		object->getNames(range);
	}
}


void JSONConfiguration::save(std::ostream& ostr, unsigned int indent) const
{
	_object->stringify(ostr, indent);
}


void JSONConfiguration::removeRaw(const std::string& key)

{
	
	std::string lastPart;
	JSON::Object::Ptr parentObject = findStart(key, lastPart);
	std::vector<int> indexes;
	getIndexes(lastPart, indexes);

	if ( indexes.empty() ) // No Array
	{
		parentObject->remove(lastPart);
	}
	else
	{
		DynamicAny result = parentObject->get(lastPart);
		if (!result.isEmpty() && result.type() == typeid(JSON::Array::Ptr))
		{

			JSON::Array::Ptr arr = result.extract<JSON::Array::Ptr>();
			for(std::vector<int>::iterator it = indexes.begin(); it != indexes.end() - 1; ++it)
			{
				arr = arr->getArray(*it);
			}
			arr->remove(indexes.back());
		}
	}

}


} } // namespace Poco::Util


#endif // POCO_UTIL_NO_JSONCONFIGURATION
