/*
author : ���Ѻ�
description : �̱��� ������ ���� Ŭ���� ����
��� �̱��� Ŭ������ �� ������ ����Ѵ�

version: 1.0.5
date: 2024-11-14
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
        inline static T* m_singleton = nullptr;

    private:
        Singleton(const Singleton&)            = delete;
        Singleton(Singleton&&)                 = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&)      = delete;

    protected:
        Singleton() = default;

    public:
        ~Singleton()
        {
            if (m_singleton)
                delete m_singleton;
        }

        static T& GetInstance()
        {
            if (!m_singleton)
                m_singleton = new T;

            return *m_singleton;
        }

        static void Release()
        {
            if (!m_singleton)
                delete m_singleton;
        }
    };
}  // namespace HBSoft
