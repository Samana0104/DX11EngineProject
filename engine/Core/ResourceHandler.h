#pragma once

namespace HBSoft
{
#define TEMPLATE_VKA template <typename V, typename K, typename A>

    template <typename V, typename K = std::wstring, typename Alloc = std::map<K, std::shared_ptr<V>>>
    class ResourceHandler
    {
    private:
        Alloc mResourceDatas;

    public:
        bool Add(const K& key, const std::shared_ptr<V>& value);
        bool Delete(const K key);
        bool IsKeyContained(const K key) const;

        void Clear();

        typename const Alloc& GetAllResources() const;

        const std::shared_ptr<V>  Get(const K key);
        const std::shared_ptr<V>& operator[](const K key);
    };

    /*
    --------------------------------------------------------------
    */

    TEMPLATE_VKA
    bool ResourceHandler<V, K, A>::Add(const K& key, const std::shared_ptr<V>& value)
    {
        return mResourceDatas.insert(std::make_pair(key, value)).second;
    }

    TEMPLATE_VKA
    bool ResourceHandler<V, K, A>::Delete(const K key)
    {
        if (!IsKeyContained(key))
            return false;

        mResourceDatas.erase(key);
        return true;
    }

    TEMPLATE_VKA
    bool ResourceHandler<V, K, A>::IsKeyContained(const K key) const
    {
        return mResourceDatas.contains(key);
    }

    TEMPLATE_VKA
    inline void ResourceHandler<V, K, A>::Clear()
    {
        mResourceDatas.clear();
    }

    TEMPLATE_VKA
    const std::shared_ptr<V> ResourceHandler<V, K, A>::Get(const K key)
    {
        try
        {
            return mResourceDatas.at(key);
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
    const std::shared_ptr<V>& ResourceHandler<V, K, A>::operator[](const K key)
    {
        return mResourceDatas[key];
    }
}  // namespace HBSoft
