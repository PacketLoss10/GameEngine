#pragma once

#include "string"

class NormalMap
{
public:
	static std::string empty;
	std::string filepath = empty;
	NormalMap() = default;
	NormalMap(std::string filepath);
};