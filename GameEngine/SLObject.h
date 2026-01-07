#pragma once

#include "nlohmann/json.hpp"

using namespace nlohmann;

class SLBase
{
public:
	virtual ~SLBase() = default;
};

template<typename T>
class SLObject :public SLBase
{
	T* load_from_file(const std::string& filepath)
	{
		std::ifstream file = std::ifstream(filepath);
		json data;
		file >> data;
		return T::load_from_file(data);
	}
	virtual T* load_from_file(const json& data) = 0;

	template<typename... Args>
	void save_to_file(const std::string& filepath, Args&&... args)
	{

	}
};