#pragma once
#include "Component.h"

namespace MyProject
{
	template <typename V, typename K = std::string, 
		typename Alloc = std::unordered_map<K, std::shared_ptr<V>>>
	class Handler
	{
	private:
		Alloc mHandle;

	protected:
		bool AddComponent(K _key, std::shared_ptr<V>& _value)
		{
			if (mHandle.contains(_key))
				return false;

			mHandle.insert(std::make_pair(_key, _value));
			return true;
		}

	public:
		bool DeleteComponent(K _key) 
		{
			if (!mHandle.contains(_key))
				return false;

			mHandle.erase(mHandle.find(_key));
			return true;
		}

		bool IsContainKey(K _key) const
		{
			if (!mHandle.contains(_key))
				return false;

			return true;
		}

		std::shared_ptr<V>& GetComponent(K _key) 
		{
			return mHandle[_key];
		}
	};
}
