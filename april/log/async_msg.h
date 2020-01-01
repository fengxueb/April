#pragma once

#include "log/log_msg.h"
#include "process/threadPool.h"

namespace April {

namespace log
{

using ITask = April::process::ITask;

class async_msg final : public log_msg, public ITask
{
public:
	friend class async_logger;

	enum class type
	{
		log_it,
		flush,
	};

	type msg_type{ type::log_it };

	async_msg() = default;
	~async_msg() = default;

	// should only be moved in or out of the queue..
	async_msg(const async_msg &) = delete;
	async_msg(type type);
	// construct from log_msg with given type
	async_msg(type type, const log_msg &m);

	virtual void Run() override;
};

} //namespace log
} //namespace April
