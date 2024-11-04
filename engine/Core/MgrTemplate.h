/*
author : ���Ѻ�
description : ���ҽ��� �����ϱ� ���� ǥ�� ���ø�

version: 1.0.0
date: 2024-11-04
*/
#pragma once

namespace HBSoft
{
#define TEMPLATE_VKA template <typename V, typename K, typename A>

    // ���ø��� ����ϱ� ���� �ۼ�

    template <typename V, typename K = std::wstring, typename Alloc = std::map<K, std::unique_ptr<V>>>
    class MgrTemplate
    {
    private:
        Alloc m_resourceDatas;

    public:
        bool Add(const K& key, std::unique_ptr<V> value);
        bool Delete(const K key);
        bool IsKeyContained(const K key) const;

        void Clear();

        /*
        description : ��� Resource�� ���� ������ ��ȯ�Ѵ�.
        */
        typename const Alloc& GetAll() const;

        const std::unique_ptr<V>& Get(const K key);
        const std::unique_ptr<V>& operator[](const K key);
    };

    /*
    --------------------------------------------------------------
    */

    TEMPLATE_VKA
    bool MgrTemplate<V, K, A>::Add(const K& key, std::unique_ptr<V> value)
    {
        return m_resourceDatas.insert(std::make_pair(key, std::move(value))).second;
    }

    TEMPLATE_VKA
    bool MgrTemplate<V, K, A>::Delete(const K key)
    {
        if (!IsKeyContained(key))
            return false;

        m_resourceDatas.erase(key);
        return true;
    }

    TEMPLATE_VKA
    bool MgrTemplate<V, K, A>::IsKeyContained(const K key) const
    {
        return m_resourceDatas.contains(key);
    }

    TEMPLATE_VKA
    inline void MgrTemplate<V, K, A>::Clear()
    {
        m_resourceDatas.clear();
    }

    TEMPLATE_VKA
    const std::unique_ptr<V>& MgrTemplate<V, K, A>::Get(const K key)
    {
        return m_resourceDatas.at(key);
    }

    TEMPLATE_VKA
    typename const A& MgrTemplate<V, K, A>::GetAll() const
    {
        return m_resourceDatas;
    }

    TEMPLATE_VKA
    const std::unique_ptr<V>& MgrTemplate<V, K, A>::operator[](const K key)
    {
        return m_resourceDatas[key];
    }
}  // namespace HBSoft
