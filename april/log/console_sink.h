#pragma once

#include "log/sink.h"

#include <memory>

namespace April {
namespace log
{
class log_msg;

class console_sink final : public sink
{
public:
	console_sink() = default;
	~console_sink() = default;

	virtual void log_it(std::shared_ptr<log_msg> msg_ptr) override;
	virtual void flush() override;
};

} //namespace log
} //namespace April
