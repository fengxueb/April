#pragma once

#include "log/logger.h"
#include "process/threadPool.h"

#include <memory>

namespace April {
namespace log
{

class sink;
class async_msg;

using thread_pool = April::process::ThreadPool;
using ITask = April::process::ITask;

class async_logger final : public logger
{
public:

	static async_logger* instance();
	async_logger(unsigned int size, level_enum level, level_enum flush_level, std::initializer_list<std::shared_ptr<sink>>&& sinks);
	~async_logger();

private:
	friend class async_msg;

	std::recursive_mutex tp_mutex_;
	static int queue_size;
	static std::shared_ptr<thread_pool> tp_;

	void sink_it_(std::shared_ptr<async_msg> msg_ptr);
	void flush_() override;
	void backend_sink_it_(std::shared_ptr<async_msg> msg_ptr);
	void backend_flush_();
	void post_msg_(std::shared_ptr<async_msg> msg_ptr);
};

} //namespace log
} //namespace April
