#pragma once
#include "Component.h"

namespace MyProject
{
	template <typename V, typename K = std::string, 
		typename Alloc = std::unordered_map<K, std::shared_ptr<V>>>
	class ResourceHandler
	{
	private:
		Alloc mResourceDatas;

	public:
		virtual ~ResourceHandler() = default;

		bool AddResource(K _key, std::shared_ptr<V>& _value)
		{
			return mResourceDatas.insert(std::make_pair(_key, _value)).second;
		}

		bool DeleteResource(K _key) 
		{
			if (!IsKeyContained(_key))
				return false;

			mResourceDatas.erase(_key);
			return true;
		}

		bool IsKeyContained(K _key) const
		{
			return mResourceDatas.contains(_key);
		}

#pragma warning(push)
#pragma warning(disable:4715)
		std::shared_ptr<V>& GetResource(K _key) 
		{
			try
			{
				return mResourceDatas.at(_key);
			}
			catch (std::out_of_range e)
			{
				MessageBoxA(NULL, e.what(), "[Key Error]", MB_OK);
			}
		}
#pragma warning(pop)
		
		typename Alloc& GetAllResources() const
		{
			return mResourceDatas;
		}
	};
}
