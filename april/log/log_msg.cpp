#include "log/log_msg.h"

#include <sstream>

namespace April {
namespace log
{

log_msg::log_msg(time_point&& time, level_enum&& lvl, std::thread::id&& tid, location&& loc, std::initializer_list<msg_attr> args)
{
	using std::chrono::duration_cast;
	using std::chrono::seconds;
	using std::chrono::milliseconds;
	auto duration = time.time_since_epoch();
	auto secs = duration_cast<seconds>(duration);
	auto tt = std::chrono::system_clock::to_time_t(time);
#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&tm_, &tt);
#else
	std::tm* tm;
	tm = std::localtime(&tt);
	tm_ = *tm;
#endif
	auto millisec = duration_cast<milliseconds>(duration) - duration_cast<milliseconds>(secs);
	millisec_ = (unsigned int)millisec.count();

	std::stringstream temp;
	temp.str() = "";
	temp << tid;
	tid_ = std::stoll(temp.str());

	level_ = lvl;
	loc_ = loc;
	string = '[' + (std::string)msg_attr(std::move(tm_), millisec_) + ']' + ' ';
	string += '[' + (std::string)msg_attr(std::move(lvl)) + ']' + ' ';
	string += '[' + (std::string)msg_attr(tid_) + ']' + ' ';
	string += '[' + (std::string)msg_attr(std::move(loc)) + ']';
	for (msg_attr i : args)
	{
		string += ' ' + (std::string)i;
	}
}

level_enum log_msg::level()
{
	return level_;
}

template<typename T>
T msg_attr::parse(std::string&& str)
{
	T value;
	return std::move(value);
}

template<> unsigned int msg_attr::parse<unsigned int>(std::string&& str)
{
	return std::stoi(str);
};

template<> unsigned long long msg_attr::parse<unsigned long long>(std::string&& str)
{
	return std::stoll(str);
};

template<> std::tm msg_attr::parse<std::tm>(std::string&& str)
{
	std::tm value;
	size_t beg = 0, sz = 0;
	value.tm_year = std::stoi(str.substr(beg), &sz) - 1900;
	beg += sz + 1;
	value.tm_mon = std::stoi(str.substr(beg), &sz);
	beg += sz + 1;
	value.tm_mday = std::stoi(str.substr(beg), &sz);
	beg += sz + 1;
	value.tm_hour = std::stoi(str.substr(beg), &sz);
	beg += sz + 1;
	value.tm_min = std::stoi(str.substr(beg), &sz);
	beg += sz + 1;
	value.tm_sec = std::stoi(str.substr(beg), &sz);
	beg += sz + 1;
	return std::move(value);
}

template<> level_enum msg_attr::parse<level_enum>(std::string&& str)
{
	const static std::string level_names[] = { "trace", "debug", "info", "warning", "error", "critical", "off" };
	for (int i = 0; i < 7; ++i)
	{
		if (str == std::string(level_names[i]))
		{
			return std::move((level_enum)i);
		}
	}
	return level_enum::off;
}

template<> location msg_attr::parse<location>(std::string&& str)
{
	return location(
		str.substr(0, str.find('(')).c_str(),
		std::stoi(str.substr(str.find('(') + 1)),
		str.substr(str.find(':') + 1).c_str()
	);
}

log_msg::log_msg(std::string str)
{
	std::string sub;

	sub = str.substr(str.find('[') + 1, str.find('.') - 1);
	tm_ = parse<std::tm>(std::move(sub));

	str = str.substr(str.find('.'));
	sub = str.substr(str.find('.') + 1, str.find(']') - 1);
	millisec_ = parse<unsigned int>(std::move(sub));

	str = str.substr(str.find(']') + 2);
	sub = str.substr(str.find('[') + 1, str.find(']') - 1);
	level_ = parse<level_enum>(std::move(sub));

	str = str.substr(str.find(']') + 2);
	sub = str.substr(str.find('[') + 1, str.find(']') - 1);
	tid_ = parse<unsigned long long>(std::move(sub));

	str = str.substr(str.find(']') + 2);
	sub = str.substr(str.find('[') + 1, str.find(']') - 1);
	loc_ = parse<location>(std::move(sub));

	str = str.substr(str.find(']') + 1);
	string = '[' + (std::string)msg_attr(std::move(tm_), millisec_) + ']' + ' ';
	string += '[' + (std::string)msg_attr(std::move(level_)) + ']' + ' ';
	string += '[' + (std::string)msg_attr(tid_) + ']' + ' ';
	string += '[' + (std::string)msg_attr(std::move(loc_)) + ']';
	string += str;
}

} //namespace log
} //namespace April
