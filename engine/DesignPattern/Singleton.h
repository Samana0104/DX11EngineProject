/*
author : ���Ѻ�
description : �̱��� ������ ���� Ŭ���� ����
��� �̱��� Ŭ������ �� ������ ����Ѵ�

version: 1.0.0
date: 2024-11-04
*/
#pragma once

namespace HBSoft
{
    /*
        �Ļ�Ŭ�������� �ݵ�� ������ ��
    private:
        friend class Singleton<T>;
        T() = default;
    */
    template <typename T>
    class Singleton
    {
    private:
        inline static T*   m_singleton     = nullptr;
        inline static bool m_isConstructed = false;  // template���� �����Ǵ� static�� �ٸ�

    private:
        Singleton(const Singleton&)            = delete;
        Singleton(Singleton&&)                 = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&)      = delete;

    protected:
        Singleton() = default;

    public:
        static T& GetInstance()
        {
            if (!m_isConstructed)
            {
                m_singleton     = new T;
                m_isConstructed = true;
            }

            return *m_singleton;
        }

        static void Release()
        {
            if (m_singleton != nullptr)
                delete m_singleton;
        }
    };
}  // namespace HBSoft
