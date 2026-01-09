#include "JSONFILE.h"
#include "JSONOBJECT.h"

JSONFILE::JSONFILE(std::string filepath) :filepath(filepath + ".json") {}

JSONFILE& JSONFILE::write(const JSONOBJECT& json)
{
	std::ofstream os(filepath);
	if (!os)
	{
		std::cerr << "Failed to open file for writing: " << filepath << std::endl;
		return *this;
	}
	os << json;
	os.flush();
	os.close();
	return *this;
}

const std::string& JSONFILE::get_filepath() const
{
	return filepath;
}