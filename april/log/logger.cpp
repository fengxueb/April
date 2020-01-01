#include "log/log.h"
#include "log/sink.h"
#include "log/log_msg.h"
#include "log/logger.h"

namespace April {
namespace log
{

std::shared_ptr<logger> logger::instance_ = nullptr;
std::mutex logger::mutex_;

logger::logger(level_enum level, level_enum flush_level, std::initializer_list<std::shared_ptr<sink>>&& sinks)
{
	level_ = level;
	flush_level_ = flush_level;
	for( std::shared_ptr<sink> s: sinks )
	{
		sinks_.push_back(s);
	}
}

logger::~logger()
{
	//	set_level(level_enum::off);
	for (auto i : sinks_)
	{
		i = nullptr;
	}
	custom_err_handler_ = nullptr;
	instance_ = nullptr;
}

logger* logger::instance()
{
	if (instance_ == nullptr)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		if (instance_ == nullptr)
		{
			instance_ = factory::create();
		}
	}

	return instance_.get();
}

void logger::log_it(level_enum lvl, location&& loc, std::initializer_list<msg_attr>&& args)
{
	if (lvl < level_)
	{
		return;
	}
	try
	{
		std::shared_ptr<log_msg> msg_ptr = std::make_shared<log_msg>(std::chrono::system_clock::now(), 
			std::move(lvl), std::this_thread::get_id(), std::move(loc), std::move(args));
		sink_it_(msg_ptr);
	}
	catch (...)
	{
	}
}

void logger::set_level(level_enum lvl)
{
	level_ = lvl;
}

level_enum logger::level() const
{
	return level_;
}

void logger::set_flush_level(level_enum lvl)
{
	flush_level_ = lvl;
}

level_enum logger::flush_level() const
{
	return flush_level_;
}

// flush functions
void logger::flush()
{
	flush_();
}

void logger::sink_it_(std::shared_ptr<log_msg> msg_ptr)
{
	for (auto &sink : sinks_)
	{
		try
		{
			sink->log_it(msg_ptr);
		}
		catch (...)
		{
			return;
		}
	}

	if (msg_ptr->level() >= flush_level_)
	{
		flush_();
	}
}

void logger::flush_()
{
	for (auto &sink : sinks_)
	{
		try
		{
			sink->flush();
		}
		catch (...)
		{
			return;
		}
	}
}

} //namespace log
} //namespace April
