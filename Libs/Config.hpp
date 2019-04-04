#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <map>
#include <exception>

#include "Logger.hpp"
#include "LibSettings.hpp"
#include "ConfigList.hpp"

#define theConfig Karmazyn::Config::GetConfig()
namespace Karmazyn
{
	struct ConfigNotFoundException : public std::exception
	{
		ConfigNotFoundException(const std::string& msg) : msg(msg) { }
		const char* what() const throw ()
		{
			return msg.c_str();
		}
		
		std::string msg;
	};
	class Config
	{
	public:
		static Config* GetConfig();

		template<typename Iterable>
		Config(const Iterable& file_name_list)
		{
			for (const auto& name : file_name_list)
			{
				if (readFile(name))
					theLog->info("Config: {} succesfully read!", name);
				else
					theLog->warn("Config: Failed to read {}!", name);
			}
		}

		~Config();

		// Returns the first match of "configname" or the default value if not found any.
		// Wrong types will cause a boost::bad_cast exception (boost::any-based).
		template<typename T>
		T get(const char* configname, T defaultval)
		{
			const auto& node = m_SettingsRootMap.find(configname);
			if (node != m_SettingsRootMap.end())
			{
				return boost::lexical_cast<T>(node->second);
			}
			if (ConfigSettings::cLogUnsuccessfulConfigGets)
				theLog->warn("Config: Lookup for: '{}' was UNSUCCESSFUL, returning default!", configname);

			set<T>(configname, defaultval); // this will make sure that not found configs at first run will get printed out to .ini. TODO: think this through
			return defaultval;
		}

		template<typename T>
		T get(const char* configname)
		{
			const auto& node = m_SettingsRootMap.find(configname);
			if (node != m_SettingsRootMap.end())
			{
				return boost::lexical_cast<T>(node->second);
			}
			throw ConfigNotFoundException(std::string("CONFIG: Could not find:" + std::string(configname)));
		}

		template<typename T>
		void set(const char* configname, const T& setto)
		{
			m_SettingsRootMap[configname] = boost::lexical_cast<std::string>(setto);
		}

		void saveAllConfigTo(const char* filename);
		void saveAll();

	private:
		bool readFile(const char* filename);

		std::map<std::string, std::string> m_SettingsRootMap;
	};
}