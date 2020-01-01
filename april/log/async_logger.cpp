#include "log/sink.h"
#include "log/logger.h"
#include "log/async_msg.h"
#include "log/async_logger.h"

#include <mutex>

namespace April {
namespace log
{

std::shared_ptr<thread_pool> async_logger::tp_{ nullptr };

int async_logger::queue_size = 4;

async_logger* async_logger::instance()
{
	return (async_logger*)logger::instance();
}

async_logger::async_logger(unsigned int size, level_enum level, level_enum flush_level, std::initializer_list<std::shared_ptr<sink>>&& sinks)
	: logger(level, flush_level, std::move(sinks))
{
	queue_size = size;
	std::lock_guard<std::recursive_mutex> lock(tp_mutex_);
	if (tp_ == nullptr)
	{
		tp_ = std::make_shared<thread_pool>(queue_size);
	}
}

async_logger::~async_logger()
{
	tp_ = nullptr;
}

// send the log message to the thread pool
void async_logger::sink_it_(std::shared_ptr<async_msg> msg_ptr)
{
	post_msg_(msg_ptr);
}

// send flush request to the thread pool
void async_logger::flush_()
{
	post_msg_(std::make_shared<async_msg>(async_msg::type::flush));
}

void async_logger::post_msg_(std::shared_ptr<async_msg> msg_ptr)
{
	if (tp_ != nullptr)
	{
		tp_->enqueue(std::static_pointer_cast<async_msg, ITask>(msg_ptr));
	}
	else
	{
		throw(("async log: thread pool doesn't exist anymore"));
	}
}

//
// backend functions - called from the thread pool to do the actual job
//
void async_logger::backend_sink_it_(std::shared_ptr<async_msg> msg_ptr)
{
	for (auto &sink : sinks_)
	{
		try
		{
			sink->log_it(std::static_pointer_cast<async_msg, log_msg>(msg_ptr));
		}
		catch (...)
		{
		}
	}

	if (msg_ptr->level() > level_)
	{
		backend_flush_();
	}
}

void async_logger::backend_flush_()
{
	for (auto &sink : sinks_)
	{
		try
		{
			sink->flush();
		}
		catch (...)
		{
		}
	}
}

} //namespace log
} //namespace April
