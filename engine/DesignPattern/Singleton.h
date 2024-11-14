/*
author : 변한빛
description : 싱글톤 패턴을 위한 클래스 파일
모든 싱글톤 클래스는 이 파일을 상속한다

version: 1.0.5
date: 2024-11-14
*/
#pragma once

namespace HBSoft
{
    /*
        파생클래스에서 반드시 선언할 것
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
