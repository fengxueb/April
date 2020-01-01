#pragma once

#include <string>

namespace April {
namespace log
{
	class location;
	class logger;

	enum class level_enum
	{
		trace = 0,
		debug = 1,
		info = 2,
		warn = 3,
		err = 4,
		critical = 5,
		off = 6,
	};

	class msg_attr
	{
	protected:
		std::string string;

	public:
		msg_attr() = default;
		template<typename T>
		inline msg_attr(T v)
		{
			string = std::to_string(v);
		}
		inline msg_attr(const char* str) : string(str) {};
		inline msg_attr(std::string str) : string(str) {};
		msg_attr(std::tm&& tm, unsigned int millisec);
		msg_attr(level_enum&& lvl);
		msg_attr(location&& loc);

		template<typename T>
		T parse(std::string&& str);

		friend std::ostream& operator<< (std::ostream &out, msg_attr &attr);
		operator std::string();
	};

	class factory
	{
		friend class logger;
	public:
		static void init(bool console_out = false, unsigned int queue_size = 4,
			std::string filename = "logs/log.txt", size_t max_size = 4 * 1024, unsigned int max_files = 1,
			level_enum level = level_enum::info, level_enum flush_level = level_enum::err, size_t max_log_size = 1024);

		static void onoff(bool onoff);

		static void log_it(level_enum lvl, const char* file, int line, const char* func, std::initializer_list<msg_attr>&& args = {});

	private:
		static std::shared_ptr<logger> create();

		static bool console_out_;
		static unsigned int queue_size_;
		static level_enum level_;
		static level_enum flush_level_;
		static std::string filename_;
		static size_t max_log_size_;
		static size_t max_size_;
		static unsigned int max_files_;
	};

} //namespace log
} //namespace April

