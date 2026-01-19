#pragma once

#include "string"

class Texture
{
public:
	static std::string empty;
	std::string filepath = empty;
	Texture() = default;
	Texture(std::string filepath);
};