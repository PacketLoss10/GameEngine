#include "JSONOBJECT.h"
#include "JSONFILE.h"

JSONOBJECT::JSONOBJECT(JSON data) :data(data) {}

void JSONOBJECT::set(const std::string& key, const JSONOBJECT& value)
{
	data[key] = value.data;
}

void JSONOBJECT::set(const std::string& key, const JSON& value)
{
	data[key] = value;
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