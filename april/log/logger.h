#pragma once

#include "log/common.h"

#include <mutex>

namespace April {
namespace log
{

class sink;
using err_handler = std::function<void(const std::string &err_msg)>;

class logger
{
public:
	friend class factory;

	static logger* instance();

	void set_level(level_enum lvl);
	level_enum level() const;
	void set_flush_level(level_enum lvl);
	level_enum flush_level() const;

	void log_it(level_enum lvl, location&& loc, std::initializer_list<msg_attr>&& args);
	void flush();

	// error handler
//	void set_error_handler(err_handler);

protected:
	template<typename L, typename... S>
	static std::shared_ptr<L> create(S... args)
	{
		return std::make_shared<L>(std::forward<S>(args)...);
	}

	logger(level_enum level, level_enum flush_level, std::initializer_list<std::shared_ptr<sink>>&& sinks);
	~logger();

	level_enum level_{ level_enum::info };
	level_enum flush_level_{ level_enum::err };
	std::vector<std::shared_ptr<sink>> sinks_;
	err_handler custom_err_handler_{ nullptr };
	static std::shared_ptr<logger> instance_;
	static std::mutex mutex_;

	// log the given message (if the given log level is high enough),
	virtual void sink_it_(std::shared_ptr<log_msg> msg_ptr);
	virtual void flush_();

	// handle errors during logging.
	// default handler prints the error to stderr at max rate of 1 message/sec.
//	void err_handler_(const std::string &msg);

};

} //namespace log
} //namespace April
