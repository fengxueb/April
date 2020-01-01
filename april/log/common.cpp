#include "log/common.h"

namespace April {
namespace log
{

filename::filename(std::string&& p)
{
	path_ = path(std::move(p));
	fullname_ = path_;
}

filename::filename(const char* p)
	: filename(std::string(p))
{}

void filename::update_fullname(size_t current_file_)
{
	fullname_ = path_.parent_path().string() + '/' + path_.stem().string()
		+ ((current_file_ > 0) ? '.' + std::to_string(current_file_) : "") + path_.extension().string();
}

location::location(const char *filename, int line, const char *funcname)
	: filename_(filename)
	, line_(line)
	, funcname_(funcname)
{}

std::ostream& operator<< (std::ostream &os, msg_attr &attr)
{
	os << attr.string;
	return os;
}

msg_attr::operator std::string()
{
	return string;
}

msg_attr::msg_attr(std::tm&& tm, unsigned int millisec)
{
	string = std::to_string(tm.tm_year + 1900) + '-'
		+ std::to_string(tm.tm_mon + 1) + '-'
		+ std::to_string(tm.tm_mday) + ' '
		+ std::to_string(tm.tm_hour) + ':'
		+ std::to_string(tm.tm_min) + ':'
		+ std::to_string(tm.tm_sec) + '.'
		+ std::to_string(millisec);
}

msg_attr::msg_attr(level_enum&& lvl)
{
	const static std::string level_names[] = { "trace", "debug", "info", "warning", "error", "critical", "off" };
	string = level_names[(int)lvl];
}

msg_attr::msg_attr(location&& loc)
{
	string =
		loc.filename_.path_.filename().string() + '('
		+ std::to_string(loc.line_) + ')' + ':'
		+ std::string(loc.funcname_);
}

} //namespace log
} //namespace April
