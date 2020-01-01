#pragma once

#include "log/common.h"
#include "log/sink.h"

#include <fstream>
#include <cassert>

namespace April {
namespace log
{

class file_sink final : public sink
{
public:
	file_sink(std::string filename, size_t max_log_size, size_t max_size, unsigned int max_files);
	file_sink() = default;
	~file_sink();

	virtual void log_it(std::shared_ptr<log_msg> msg_ptr) override;
	virtual void flush() override;
	std::string current_file_name();

private:
	void roll_();
	void fill_next_log();

	filename filename_;
	size_t max_log_size_ = 0;
	size_t max_size_ = 0;
	size_t current_size_ = 0;
	size_t current_line_ = 0;
	unsigned int max_files_ = 0;
	unsigned int current_file_ = 0;
	std::string help_filename_{".log"};

	std::fstream fd_;
};

} //namespace log
} //namespace April
