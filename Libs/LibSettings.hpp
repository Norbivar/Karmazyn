#pragma once
#include <array>
#include <regex>

namespace Karmazyn
{
	namespace LoggerSettings
	{
		constexpr const char* const cLogFile = "./debug_log.txt";
	}
	namespace ConfigSettings
	{
		// Holds the file names (relative to executable) to open and read settings from.
		// Settings in latter files will always overwrite settings from earlier files.
		constexpr std::array<const char* const, 1> cConfigFilesToReadInOrder = {
			"./conf.ini"
		};
		
		const std::regex cConfigRootRegex       ("^\\[[a-zA-Z]+\\]$");
		const std::regex cConfigValidLineRegex  ("^[a-zA-Z_]+\\=.*");

		constexpr bool cLogUnsuccessfulConfigGets = false;
	}
}