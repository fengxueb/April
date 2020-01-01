#include "log/log_msg.h"
#include "log/file_sink.h"

#include <experimental/filesystem>
#include <cstring>

namespace April {
namespace log
{

using namespace std::experimental::filesystem::v1;

file_sink::file_sink(std::string name, size_t max_log_size, size_t max_size, unsigned int max_files)
	: sink()
	, filename_(name.c_str())
	, max_log_size_(max_log_size)
	, max_size_(max_size)
	, max_files_(max_files)
{
	std::lock_guard<std::mutex> lock(mutex_);
	assert(max_size_ > max_log_size_);
	help_filename_ = "." + filename_.path_.filename().string();
	if ( !exists(filename_.path_.parent_path()) )
	{
		create_directory(filename_.path_.parent_path());
	}
	if( exists(path(filename_.path_.parent_path().string() + "\\" + help_filename_)) )
	{
		std::fstream help;
		help.open(filename_.path_.parent_path().string() + "\\" + help_filename_, std::ios::in);
		char delim;
		help >> current_file_ >> delim >> current_line_;
		filename_.update_fullname(current_file_);
	}
	else
	{
		current_file_ = 0;
		current_line_ = 0;
	}
	if( exists(path(filename_.fullname_)) )
	{
		fd_.open(filename_.fullname_, std::ios::in | std::ios::out);
		char* temp = new char[max_log_size_];
		for (unsigned int i = 0; i < current_line_; ++i)
		{
			memset(temp, 0, max_log_size_);
			fd_.getline(temp, max_log_size_);
		}
		delete[] temp;
		fd_.seekp(fd_.tellg());
	}
	else
	{
		fd_.open(filename_.fullname_, std::ios::in | std::ios::out | std::ios::trunc);
	}
	if ( fd_.is_open() )
	{
		current_size_ = (size_t)fd_.tellp();
		if (max_size_ - max_log_size_ < current_size_)
		{
			roll_();
		}
	}
	else
	{
		throw("open file fail");
		return;
	}
}

file_sink::~file_sink()
{
	std::lock_guard<std::mutex> lock(mutex_);
	fill_next_log();
	fd_.close();
}

void file_sink::log_it(std::shared_ptr<log_msg> msg_ptr)
{
	std::lock_guard<std::mutex> lock(mutex_);
	assert(((std::string)(*msg_ptr)).length() < max_log_size_);

	if ( current_size_ + ((std::string)(*msg_ptr)).length() + 2 > max_size_ )
	{
		fill_next_log();
		roll_();
	}
	current_line_ += 1;
	current_size_ += ((std::string)(*msg_ptr)).length() + 2;
	fd_ << *msg_ptr << '\n';
	std::fstream help;
	help.open(filename_.path_.parent_path().string() + "\\" + help_filename_, std::ios::out);
	help << current_file_ << ":" << current_line_;
	help.close();
}

void file_sink::flush()
{
	std::lock_guard<std::mutex> lock(mutex_);
	fd_.flush();
}

void file_sink::roll_()
{
	fd_.close();
	current_size_ = 0;
	current_line_ = 0;
	current_file_ = (current_file_ + 1 >= max_files_) ? 0 : current_file_ + 1;
	filename_.update_fullname(current_file_);
	if ( exists(path(filename_.fullname_)) )
	{
		fd_.open(filename_.fullname_, std::ios::in | std::ios::out);
	}
	else
	{
		fd_.open(filename_.fullname_, std::ios::in | std::ios::out | std::ios::trunc);
	}
	if ( !fd_.is_open() )
	{
		throw("open file fail");
		return;
	}
}

void file_sink::fill_next_log()
{
	char* temp = new char[max_log_size_];
	memset(temp, 0, max_log_size_);
	size_t pos = (size_t)fd_.tellp();
	fd_.seekg(pos);
	fd_.getline(temp, max_log_size_);
	size_t len = strlen(temp);
	delete[] temp;
	fd_.seekp(pos);
	while (len > 0)
	{
		fd_ << '-';
		--len;
	}
}

std::string file_sink::current_file_name()
{
	return filename_.fullname_.string();
}

} //namespace log
} //namespace April
