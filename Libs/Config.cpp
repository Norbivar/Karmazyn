#include <fstream>

#include "Config.hpp"
#include "Logger.hpp"

namespace Karmazyn
{
	Config::~Config()
	{
		saveAll();
	}

	void Config::saveAllConfigTo(const char* filename)
	{
		std::ofstream output(filename, std::ios::out);
		if (output.good())
		{
			for (const auto& roots : m_SettingsRootMap)
			{
				output << roots.first.c_str() << "=" << roots.second.c_str() << "\n";
			}
		}
	}
	void Config::saveAll()
	{
		if (!ConfigSettings::cConfigFilesToReadInOrder.empty())
		{
			const char* filename = *ConfigSettings::cConfigFilesToReadInOrder.begin();
			saveAllConfigTo(filename);
		}
	}

	bool Config::readFile(const char* filename)
	{
		std::ifstream input(filename);
		if (input.good())
		{
			std::string line;
			while (std::getline(input, line))
			{
				if (std::regex_match(line, ConfigSettings::cConfigValidLineRegex))
				{
					const auto eqpos = line.find_first_of('=');
					const std::string key = line.substr(0, eqpos);
					const std::string valueText = line.substr(eqpos + 1);

					if (m_SettingsRootMap.find(key) != m_SettingsRootMap.end())
					{
						theLog->warn("Config: Duplicate key in config ({}), skipping!", key.c_str());
						continue;
					}

					m_SettingsRootMap.emplace(key, valueText);
				}
				else
				{
					theLog->warn("Config: invalid line detected, skipping!");
				}
			}
			return true;
		}
		else return false;
	}
}