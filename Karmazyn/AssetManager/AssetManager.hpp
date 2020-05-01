#pragma once

namespace Karmazyn
{
	// Asset must have a "loadFromFile" method.
	template<typename AssetType>
	class AssetContainer
	{
		friend class AssetManager;
		AssetContainer() {};

		std::shared_ptr<AssetType> acquire(const std::string& asset_file_name) // TODO: make threadsafe, as the potential for fucking up is huge
		{
			const auto AssetIterator = m_AssetContainer.find(asset_file_name);
			if (AssetIterator != m_AssetContainer.end())
			{
				return AssetIterator->second;
			}
			else
			{
				std::shared_ptr<AssetType> asset = std::make_shared<AssetType>();
				asset->loadFromFile(asset_file_name);
				m_AssetContainer.emplace(asset_file_name, asset);
				return asset;
			}
			return nullptr;
		}

		size_t onRequestFlushUnused();

		std::map< std::string, std::shared_ptr<AssetType> > m_AssetContainer;
	};

	class AssetManager
	{
	public:
		AssetManager();

		template<typename T>
		std::shared_ptr<T> acquire(const std::string& asset_file_name)
		{
			static_assert(false, "AssetManager::acquire instantiated with NOT SUPPORTED type!");
		}

		template<>
		std::shared_ptr<sf::Texture> acquire<sf::Texture>(const std::string& asset_file_name)
		{
			return m_TextureAssets.acquire(asset_file_name);
		}

		size_t requestUnusedCacheFlush();

	private:
		AssetContainer<sf::Texture> m_TextureAssets;
	};
}