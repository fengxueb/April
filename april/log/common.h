#pragma once

#include "log/log.h"

#include <experimental/filesystem>

namespace April {
namespace log{

using namespace std::experimental::filesystem::v1;

class filename
{
public:
	path path_;
	path fullname_;

	filename() = default;
	filename(std::string&& p);
	filename(const char* p);
	void update_fullname(size_t current_file_);
};

class location
{
public:
	location() = default;
	location(const char *filename, int line, const char *funcname);

	filename filename_{ "" };
	unsigned int line_{ 0 };
	std::string funcname_{ "" };
};

} //namespace log
} //namespace April
