#pragma once
#include "spdlog/spdlog.h"
#include "LibSettings.hpp"

#define theLog Karmazyn::Logger::GetLogger()
namespace Karmazyn
{
	class Logger
	{
	public:

		static Logger* GetLogger();
		Logger() :
			RotatedTxtLogger  (spdlog::rotating_logger_mt("txtlogger", LoggerSettings::cLogFile, 1024 * 1024 * 20, 3))
		#ifndef NDEBUG
			, ConsoleLogger   (spdlog::stdout_color_mt("console"))
		#endif
		{
			spdlog::set_async_mode(8192);
			spdlog::set_pattern("[%H:%M:%S] %v");
			spdlog::drop_all();
			RotatedTxtLogger->info("\n============================================================================================================");
			RotatedTxtLogger->info("Log started.");
		}
		~Logger()
		{
			RotatedTxtLogger->info("Log stopped.");
			RotatedTxtLogger->info("============================================================================================================");
		}

		template<typename Arg1, typename... Args>
		inline void info(const char *fmt, const Arg1 &arg1, const Args &... args)
		{
			RotatedTxtLogger->info(fmt, arg1, args...);
		#ifndef NDEBUG
			ConsoleLogger->info(fmt, arg1, args...);
		#endif
		}

		template<typename Arg1, typename... Args>
		inline void warn(const char *fmt, const Arg1 &arg1, const Args &... args)
		{
			RotatedTxtLogger->warn(fmt, arg1, args...);
		#ifndef NDEBUG
			ConsoleLogger->warn(fmt, arg1, args...);
		#endif
		}

		template<typename Arg1, typename... Args>
		inline void error(const char *fmt, const Arg1 &arg1, const Args &... args)
		{
			RotatedTxtLogger->error(fmt, arg1, args...);
		#ifndef NDEBUG
			ConsoleLogger->error(fmt, arg1, args...);
		#endif
		}

		template<typename T>
		inline void info(const T& msg)
		{
			RotatedTxtLogger->info(msg);
		#ifndef NDEBUG
			ConsoleLogger->info(msg);
		#endif
		}

		template<typename T>
		inline void warn(const T& msg)
		{
			RotatedTxtLogger->warn(msg);
		#ifndef NDEBUG
			ConsoleLogger->warn(msg);
		#endif
		}

		template<typename T>
		inline void error(const T& msg)
		{
			RotatedTxtLogger->error(msg);
		#ifndef NDEBUG
			ConsoleLogger->error(msg);
		#endif
		}

	private:
		std::shared_ptr<spdlog::logger> RotatedTxtLogger;
	#ifndef NDEBUG
		std::shared_ptr<spdlog::logger> ConsoleLogger;
	#endif
	};
}