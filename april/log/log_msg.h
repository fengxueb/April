#pragma once

#include "log/common.h"

#include <thread>

namespace April {
namespace log
{

using time_point = std::chrono::system_clock::time_point;

class log_msg : public msg_attr
{
protected:
	std::tm tm_;
	unsigned int millisec_;
	level_enum level_ = level_enum::off;
	unsigned long long tid_;
	location loc_;

public:
	log_msg() = default;
	log_msg(time_point&& time, level_enum&& lvl, std::thread::id&& tid, location&& loc, std::initializer_list<msg_attr> args);
	log_msg(std::string str);
	level_enum level();
};

} //namespace log
} //namespace April
