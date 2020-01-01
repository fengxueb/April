#include "log/log_msg.h"
#include "log/console_sink.h"

#include <iostream>

namespace April {
namespace log
{

void console_sink::log_it(std::shared_ptr<log_msg> msg_ptr)
{
	std::lock_guard<std::mutex> lock(mutex_);
	std::cout << *msg_ptr << std::endl;
	// log_msg temp((std::string)(*msg_ptr));
	// std::cout << temp << std::endl;
}

void console_sink::flush()
{
	std::lock_guard<std::mutex> lock(mutex_);
	std::cout << std::flush;
}

} //namespace log
} //namespace April
