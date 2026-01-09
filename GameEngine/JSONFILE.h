#pragma once

#include "string"
#include "fstream"
#include "iostream"

class JSONOBJECT;

class JSONFILE
{
private:
	std::string filepath;
public:
	JSONFILE(std::string filepath);

	JSONFILE& write(const JSONOBJECT& json);

	const std::string& get_filepath() const;
};
