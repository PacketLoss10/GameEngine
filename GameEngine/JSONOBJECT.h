#pragma once

#include "nlohmann/json.hpp"
#include "fstream"
#include "iostream"
#include "string"
#include "vector"
#include "type_traits"

class JSONFILE;
class SLObject;

using JSON = nlohmann::json;

template<typename T>
concept IsSLObject = std::is_base_of<SLObject, T>::value;

class JSONOBJECT
{
private:
	JSON data;
public:
	JSONOBJECT() = default;
	JSONOBJECT(JSON data);

	void set(const std::string& key, const JSONOBJECT& value);
	void set(const std::string& key, const JSON& value);
	void add(const std::string& key, const JSONOBJECT& value);
	void add(const std::string& key, const JSON& value);

	JSONOBJECT get(const std::string& key) const;
	std::vector<JSONOBJECT> collect(const std::string& key) const;
	operator int() const
	{
		return data.get<int>();
	}
	operator float() const
	{
		return data.get<float>();
	}
	operator bool() const
	{
		return data.get<bool>();
	}
	operator std::string() const
	{
		return data.get<std::string>();
	}

	JSONOBJECT& read(const JSONFILE& file);

	operator JSON() const
	{
		return data;
	}

	friend inline std::ostream& operator<<(std::ostream& os, const JSONOBJECT& json);
	friend inline std::istream& operator>>(std::istream& is, JSONOBJECT& json);
};

inline std::ostream& operator<<(std::ostream& os, const JSONOBJECT& json)
{
	os << json.data.dump(2);
	return os;
}

inline std::istream& operator>>(std::istream& is, JSONOBJECT& json)
{
	nlohmann::json temp;
	is >> temp;
	json.data = std::move(temp);
	return is;
}