#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <unordered_map>
#include <exception>

#include "LibSettings.hpp"

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
		T get(const char* root, const char* configname, T defaultval)
		{
			auto& foundroot = m_SettingsRootMap.find(root);
			if(foundroot != m_SettingsRootMap.end())
			{
				auto& node = foundroot->second.find(configname);
				if (node != foundroot->second.end())
				{
					return boost::lexical_cast<T>(node->second);
				}
			}
			if (ConfigSettings::cLogUnsuccessfulConfigGets)
				theLog->warn("Config: Lookup for [{}]: {} was UNSUCCESSFUL!", root, configname);

			return defaultval;
		}

		template<typename T>
		T get(const char* root, const char* configname)
		{
			auto& foundroot = m_SettingsRootMap.find(root);
			if (foundroot != m_SettingsRootMap.end())
			{
				auto& node = foundroot->second.find(configname);
				if (node != foundroot->second.end())
				{
					return boost::lexical_cast<T>(node->second);
				}
			}
			throw ConfigNotFoundException(std::string("CONFIG: Could not find: [") + std::string(root) + std::string("] ") + std::string(configname));
		}

		template<typename T>
		bool set(const char* root, const char* configname, const T& setto)
		{
			auto& foundroot = m_SettingsRootMap.find(root);
			if (foundroot != m_SettingsRootMap.end())
			{
				auto& node = foundroot->second.find(configname);
				if (node != foundroot->second.end())
				{
					node->second = boost::lexical_cast<std::string>(setto);
					return true;
				}
			}
			return false; // TODO: consider throwing?
		}

		void saveAllConfigTo(const char* filename);
		void saveAll();

	private:
		bool readFile(const char* filename);

		std::unordered_map<
			std::string, 
			std::unordered_map<
				std::string, 
				std::string
			>
		> m_SettingsRootMap;
	};
}