#include "log/sink.h"
#include "log/file_sink.h"
#include "log/console_sink.h"
#include "log/logger.h"
#include "log/async_logger.h"
#include "log/log.h"

namespace April {
namespace log
{
	bool factory::console_out_ = false;
	unsigned int factory::queue_size_ = 4;
	level_enum factory::level_ = level_enum::info;
	level_enum factory::flush_level_ = level_enum::err;
	std::string factory::filename_ = "logs/log.txt";
	size_t factory::max_log_size_ = 1024;
	size_t factory::max_size_ = 4 * 1024;
	unsigned int factory::max_files_ = 1;

void factory::init(bool console_out, unsigned int queue_size, std::string filename,
	size_t max_size, unsigned int max_files,
	level_enum level, level_enum flush_level, size_t max_log_size)
{
	console_out_ = console_out;
	queue_size_ = queue_size;
	level_ = level;
	flush_level_ = flush_level;
	filename_ = filename;
	max_size_ = max_size;
	max_files_ = max_files;
	max_log_size_ = max_log_size;
}

void factory::onoff(bool onoff)
{
	if (onoff)
	{
		logger::instance()->set_level(level_);
		logger::instance()->set_flush_level(flush_level_);
	}
	else
	{
		logger::instance()->set_level(level_enum::off);
		logger::instance()->set_flush_level(level_enum::off);
	}
}

void factory::log_it(level_enum lvl, const char* file, int line, const char* func, std::initializer_list<msg_attr>&& args)
{
	logger::instance()->log_it(lvl, location(file, line, func), std::move(args));
}

std::shared_ptr<logger> factory::create()
{
	if (console_out_)
	{
		return logger::create<async_logger>(queue_size_, level_, flush_level_, 
			std::initializer_list<std::shared_ptr<sink>>{
			sink::create<file_sink>(filename_, max_log_size_, max_size_, max_files_),
			sink::create<console_sink>() });
	}
	else
	{
		return logger::create<async_logger>(queue_size_, level_, flush_level_,
			std::initializer_list<std::shared_ptr<sink>>{
			sink::create<file_sink>(filename_, max_log_size_, max_size_, max_files_) });
	}
}

} //namespace log
} //namespace April
