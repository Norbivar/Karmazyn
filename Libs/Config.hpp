#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <map>
#include <exception>

#include "LibSettings.hpp"
#include "ConfigList.hpp"

namespace MyPI
{
	struct ConfigOrFileNotFoundException : public std::exception
	{
		ConfigOrFileNotFoundException(const std::string& msg) : msg(msg) { }
		const char* what() const throw ()
		{
			return msg.c_str();
		}
		
		const std::string msg;
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
				readFile(name);
			}
		}

		~Config();

		// Returns the first match of "configname" or the default value if not found any.
		// Wrong types will cause a boost::bad_cast exception (boost::any-based).
		template<typename config, typename T = config::type>
		T get(const T& defaultval)
		{
			const auto& configname = config::getValue();
			const auto& node = m_SettingsRootMap.find(configname);
			if (node != m_SettingsRootMap.end())
			{
				return boost::lexical_cast<T>(node->second);
			}

			set<config>(defaultval); // this will make sure that not found configs at first run will get printed out to .ini. TODO: think this through
			return defaultval;
		}

		template<typename config, typename T = config::type>
		T get()
		{
			const auto& configname = config::getValue();
			const auto& node = m_SettingsRootMap.find(configname);
			if (node != m_SettingsRootMap.end())
			{
				return boost::lexical_cast<T>(node->second);
			}
			throw ConfigOrFileNotFoundException(std::string("CONFIG: Could not find:" + std::string(configname)));
		}

		template<typename config>
		std::string getAsString()
		{
			return get<config, std::string>();
		}

		template<typename config, typename T = config::type>
		void set(const T& setto)
		{
			const auto& configname = config::getValue();
			m_SettingsRootMap[configname] = boost::lexical_cast<std::string>(setto);
		}

		void saveAllConfigTo(const char* filename);
		void saveAll();

	private:
		bool readFile(const char* filename);

		std::map<std::string, std::string> m_SettingsRootMap;
	};
}