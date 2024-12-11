/*
author : 변한빛
description : 리소스를 관리하기 위한 표준 템플릿

version: 1.0.0
date: 2024-11-04
*/
#pragma once

namespace HBSoft
{
#define TEMPLATE_VKA template <typename V, typename K, typename A>

    // 템플릿을 축약하기 위해 작성

    template <typename V, typename K = std::wstring, typename Alloc = std::map<K, std::shared_ptr<V>>>
    class MgrTemplate
    {
    private:
        Alloc m_resourceDatas;

    public:
        bool Add(const K& key, std::shared_ptr<V> value);
        bool Delete(const K& key);
        bool IsKeyContained(const K& key) const;
        void Clear();

        /*
        description : 모든 Resource를 담은 변수를 반환한다.
        */
        typename Alloc& GetAll();

        std::shared_ptr<V> Get(const K& key);
        std::shared_ptr<V> operator[](const K& key);
    };

    /*
    --------------------------------------------------------------
    */

    TEMPLATE_VKA
    bool MgrTemplate<V, K, A>::Add(const K& key, std::shared_ptr<V> value)
    {
        return m_resourceDatas.insert(std::make_pair(key, std::move(value))).second;
    }

    TEMPLATE_VKA
    bool MgrTemplate<V, K, A>::Delete(const K& key)
    {
        if (!IsKeyContained(key))
            return false;

        m_resourceDatas.erase(key);
        return true;
    }

    TEMPLATE_VKA
    bool MgrTemplate<V, K, A>::IsKeyContained(const K& key) const
    {
        return m_resourceDatas.contains(key);
    }

    TEMPLATE_VKA
    inline void MgrTemplate<V, K, A>::Clear()
    {
        m_resourceDatas.clear();
    }

    TEMPLATE_VKA
    std::shared_ptr<V> MgrTemplate<V, K, A>::Get(const K& key)
    {
        return m_resourceDatas.at(key);
    }

    TEMPLATE_VKA
    typename A& MgrTemplate<V, K, A>::GetAll()
    {
        return m_resourceDatas;
    }

    TEMPLATE_VKA
    std::shared_ptr<V> MgrTemplate<V, K, A>::operator[](const K& key)
    {
        assert(IsKeyContained(key));
        return m_resourceDatas[key];
    }
}  // namespace HBSoft
