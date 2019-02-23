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
				output << "[" << roots.first.c_str() << "]\n";
				for (const auto& settings : roots.second)
					output << settings.first.c_str() << "=" << settings.second.c_str() << "\n";

				output << "\n";
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
			std::string last_root;
			while (std::getline(input, line))
			{
				if (std::regex_match(line, ConfigSettings::cConfigValidLineRegex))
				{
					if (last_root.empty())
					{
						theLog->error("Config: line found with no appropriate root in file {}! Interrupting read!", filename);
						break;
					}

					auto rootmap = m_SettingsRootMap.find(last_root);
					if (rootmap != m_SettingsRootMap.end())
					{
						const auto eqpos = line.find_first_of('=');
						const std::string key = line.substr(0, eqpos);
						const std::string valueText = line.substr(eqpos + 1);

						rootmap->second.emplace(key, valueText);
					}
				}
				else if (std::regex_match(line, ConfigSettings::cConfigRootRegex)) // we should have much fewer roots than actual settings
				{
					const std::string rootname = line.substr(line.find_first_of('[') + 1, line.length() - 2);
					m_SettingsRootMap.emplace(
						rootname, // TODO: consider refactor, maybe with regex
						std::unordered_map<std::string, std::string>()
					);
					last_root = rootname;
				}
			}
			return true;
		}
		else return false;
	}
}