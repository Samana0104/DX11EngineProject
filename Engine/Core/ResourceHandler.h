#pragma once
#include "Component.h"

namespace MyProject
{
	template <typename V, typename K = std::wstring, 
		typename Alloc = std::map<K, std::shared_ptr<V>>>
	class ResourceHandler
	{
	private:
		Alloc mResourceDatas;

	public:
		bool AddResource(K _key, std::shared_ptr<V>& _value);
		bool DeleteResource(K _key);
		bool IsKeyContained(K _key) const;
		
		typename Alloc&		GetAllResources() const;
		std::shared_ptr<V>	GetResource(K _key);
		std::shared_ptr<V>& operator[](K _key);

		std::wstring GetKeyAsFileName(wstringV _filePath) const;
	};

	/*
	--------------------------------------------------------------
	*/

	template< typename V, typename K, typename A>
	bool ResourceHandler<V, K, A>::AddResource(K _key, std::shared_ptr<V>& _value)
	{
		return mResourceDatas.insert(std::make_pair(_key, _value)).second;
	}

	template< typename V, typename K, typename A>
	std::wstring ResourceHandler<V, K, A>::GetKeyAsFileName(wstringV _filePath) const
	{
		std::wstring fileNameKey;
		wchar_t  szDrive[MAX_PATH] = { 0, };
		wchar_t  szDir[MAX_PATH] = { 0, };
		wchar_t  szFileName[MAX_PATH] = { 0, };
		wchar_t  szFileExt[MAX_PATH] = { 0, };

		_tsplitpath_s(_filePath.data(), szDrive, szDir, szFileName, szFileExt);
		fileNameKey = szFileName;
		fileNameKey += szFileExt;

		return fileNameKey;
	}

	template< typename V, typename K, typename A>
	bool ResourceHandler<V, K, A>::DeleteResource(K _key)
	{
		if (!IsKeyContained(_key))
			return false;

		mResourceDatas.erase(_key);
		return true;
	}

	template< typename V, typename K, typename A>
	bool ResourceHandler<V, K, A>::IsKeyContained(K _key) const
	{
		return mResourceDatas.contains(_key);
	}

	template< typename V, typename K, typename A>
	std::shared_ptr<V> ResourceHandler<V, K, A>::GetResource(K _key)
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

	template< typename V, typename K, typename A>
	typename A& ResourceHandler<V, K, A>::GetAllResources() const
	{
		return mResourceDatas;
	}

	template< typename V, typename K, typename A>
	std::shared_ptr<V>& ResourceHandler<V, K, A>::operator[](K _key)
	{
		return mResourceDatas[_key];
	}
}
