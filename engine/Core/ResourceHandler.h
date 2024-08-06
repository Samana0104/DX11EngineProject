#pragma once

namespace MyProject
{
	#define TEMPLATE_VKA template<typename V, typename K, typename A>

	template <typename V, typename K = std::wstring, 
		typename Alloc = std::map<K, std::shared_ptr<V>>>
	class ResourceHandler
	{
	private:
		Alloc mResourceDatas;

	public:
		bool AddResource(const K& _key, const std::shared_ptr<V>& _value);
		bool DeleteResource(const K _key);
		bool IsKeyContained(const K _key) const;
		
		void ClearResources();

		typename const Alloc&	GetAllResources() const;

		const std::shared_ptr<V> GetResource(const K _key);
		const std::shared_ptr<V>& operator[](const K _key);

	};

	/*
	--------------------------------------------------------------
	*/

	TEMPLATE_VKA
	bool ResourceHandler<V, K, A>::AddResource(const K& _key, const std::shared_ptr<V>& _value)
	{
		return mResourceDatas.insert(std::make_pair(_key, _value)).second;
	}

	TEMPLATE_VKA
	bool ResourceHandler<V, K, A>::DeleteResource(const K _key)
	{
		if (!IsKeyContained(_key))
			return false;

		mResourceDatas.erase(_key);
		return true;
	}

	TEMPLATE_VKA
	bool ResourceHandler<V, K, A>::IsKeyContained(const K _key) const
	{
		return mResourceDatas.contains(_key);
	}

	TEMPLATE_VKA
	inline void ResourceHandler<V, K, A>::ClearResources()
	{
		mResourceDatas.clear();
	}

	TEMPLATE_VKA
	const std::shared_ptr<V> ResourceHandler<V, K, A>::GetResource(const K _key)
	{
		try
		{
			return mResourceDatas.at(_key);
		}
		catch (std::out_of_range e)
		{
			MessageBoxA(NULL, e.what(), "[Key Error]", MB_OK);
			return nullptr;
		}
	}

	TEMPLATE_VKA
	typename const A& ResourceHandler<V, K, A>::GetAllResources() const
	{
		return mResourceDatas;
	}

	TEMPLATE_VKA
	const std::shared_ptr<V>& ResourceHandler<V, K, A>::operator[](const K _key)
	{
		return mResourceDatas[_key];
	}
}
