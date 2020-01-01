#pragma once

#include <mutex>

namespace April {
namespace log
{

class log_msg;

class sink
{
public:
	template<typename S, typename... T>
	static std::shared_ptr<S> create(T... args)
	{
		return std::make_shared<S>(std::forward<T>(args)...);
	}

	sink() = default;
	virtual ~sink() = default;
	sink(const sink&) = delete;
	virtual void log_it(std::shared_ptr<log_msg> msg_ptr) = 0;
	virtual void flush() = 0;

protected:
	std::mutex mutex_;
};

} //namespace log
} //namespace April
