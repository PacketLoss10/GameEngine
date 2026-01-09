#include "JSONOBJECT.h"
#include "JSONFILE.h"

JSONOBJECT::JSONOBJECT(JSON data) :data(data) {}

void JSONOBJECT::set(const std::string& key, const JSONOBJECT& value)
{
	if (data[key].is_array())
	{
		std::cerr << "Could not set value at key [" << key << "], as array was found there." << std::endl;
		return;
	}
	data[key] = value.data;
}

void JSONOBJECT::set(const std::string& key, const JSON& value)
{
	if (data[key].is_array())
	{
		std::cerr << "Could not set value at key [" << key << "], as array was found there." << std::endl;
		return;
	}
	data[key] = value;
}

void JSONOBJECT::add(const std::string& key, const JSONOBJECT& value)
{
	if (!data[key].is_null() && !data[key].is_array())
	{
		std::cerr << "No array found at key [" << key << "]" << std::endl;
		return;
	}
	data[key].push_back(value.data);
}

void JSONOBJECT::add(const std::string& key, const JSON& value)
{
	if (!data[key].is_null() && !data[key].is_array())
	{
		std::cerr << "No array found at key [" << key << "]" << std::endl;
		return;
	}
	data[key].push_back(value);
}

JSONOBJECT JSONOBJECT::get(const std::string& key) const
{
	static const JSONOBJECT nulljson(nullptr);

	if (!data.contains(key))
	{
		std::cerr << "Key [" << key << "] was not found in JSON" << std::endl;
		return nulljson;
	}

	return JSONOBJECT(data[key]);
}

std::vector<JSONOBJECT> JSONOBJECT::collect(const std::string& key) const
{
	std::vector<JSONOBJECT> arr;

	if (!data.contains(key))
	{
		std::cerr << "Key [" << key << "] was not found in JSON" << std::endl;
		return arr;
	}

	if (!data[key].is_array())
	{
		std::cerr << "No array found at key [" << key << "]" << std::endl;
		return arr;
	}

	for (JSONOBJECT obj : data[key])
	{
		arr.push_back(obj);
	}

	return arr;
}

JSONOBJECT& JSONOBJECT::read(const JSONFILE& file)
{
	std::string filepath = file.get_filepath();
	std::ifstream is(filepath);
	if (!is)
	{
		std::cerr << "Failed to open file for reading: " << filepath << std::endl;
		return *this;
	}
	is >> *this;
	is.close();
	return *this;
}