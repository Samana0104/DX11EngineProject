#pragma once
#include "Component.h"

namespace MyProject
{
	template <typename V, typename K = UINT, 
		typename Alloc = std::unordered_map<K, std::shared_ptr<V>>>
	class ResourceHandler
	{
	private:
		Alloc mResourceDatas;
		K mKeyForRegister;

	protected:
		ResourceHandler() { mKeyForRegister = -1; }

		bool AddComponent(K _key, std::shared_ptr<V>& _value)
		{
			if (IsKeyContained(_key))
				return false;

			mResourceDatas.insert(std::make_pair(_key, _value));
			return true;
		}

	public:
		bool DeleteComponent(K _key) 
		{
			if (!IsKeyContained(_key))
				return false;

			mResourceDatas.erase(mResourceDatas.find(_key));
			return true;
		}

		bool IsKeyContained(K _key) const
		{
			return mResourceDatas.contains(_key);
		}

		std::shared_ptr<V> GetComponent(K _key) 
		{
			if (IsKeyContained(_key))
				return mResourceDatas[_key];
			else
				return nullptr;
		}

		K 

	};
}
