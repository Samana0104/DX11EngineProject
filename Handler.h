#pragma once
#include "Component.h"

namespace MyProject
{
	template <typename V, typename K = std::string, typename Alloc = std::unordered_map<K, V>>
	class Handler
	{
	private:
		std::map<K, std::shared_ptr<V>> mHandle;

	protected:
		bool AddComponent(K _key, std::shared_ptr<V>& _value)
		{
			if (mHandle.contains(_key))
				return false;


			mHandle.insert(std::make_pair(_key, _value));
			return true;
		}

		bool DeleteComponent(K _key) 
		{
			if (!mHandle.contains(_key))
				return false;

			mHandle.erase(mHandle.find(_key));
			return true;
		}

		std::shared_ptr<V>& GetComponent(K _key) 
		{
			return mHandle[_key];
		}
	};
}
