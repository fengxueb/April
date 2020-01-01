#include "log/async_msg.h"
#include "log/async_logger.h"

namespace April {
namespace log
{

async_msg::async_msg(type type, const log_msg &m)
	: log_msg{ m }
	, msg_type{ type }
{}

// construct from log_msg with given type
async_msg::async_msg(type type)
	: log_msg()
	, msg_type{ type }
{}

void async_msg::Run()
{
	switch (msg_type)
	{
	case type::log_it: {
		async_logger::instance()->backend_sink_it_((std::shared_ptr<async_msg>)this);
		break;
	}
	case type::flush: {
		async_logger::instance()->backend_flush_();
		break;
	}
	default: {
		break;
	}
	}
}

} //namespace log
} //namespace April
