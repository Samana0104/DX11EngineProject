/*
author : 변한빛
description : 싱글톤 패턴을 위한 클래스 파일
모든 싱글톤 클래스는 이 파일을 상속한다

version: 1.0.0
date: 2024-11-04
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
        inline static T*   m_singleton     = nullptr;
        inline static bool m_isConstructed = false;  // template마다 생성되는 static이 다름

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
