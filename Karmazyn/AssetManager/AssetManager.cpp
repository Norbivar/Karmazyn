#include "AssetManager.hpp"

namespace Karmazyn
{
	template<typename AssetType>
	size_t AssetContainer<AssetType>::onRequestFlushUnused()
	{
		size_t deleted { 0 };
		for (auto it = m_AssetContainer.begin(); it != m_AssetContainer.end(); ++it)
		{
			if (it->second.use_count() == 1)
			{
				m_AssetContainer.erase(it);
				++deleted;
			}
		}
		return deleted;
	}


	
	AssetManager::AssetManager()
	{

	}

	size_t AssetManager::requestUnusedCacheFlush()
	{
		return
			m_TextureAssets.onRequestFlushUnused()

			;
	}
}