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

		std::shared_ptr<V> GetResource(K _key) 
		{
			if (IsKeyContained(_key))
				return mResourceDatas[_key];
			else
				return nullptr;
		}
		
		typename Alloc& GetAllResources() const
		{
			return mResourceDatas;
		}
	};
}
