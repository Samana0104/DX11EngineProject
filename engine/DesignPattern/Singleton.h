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
        Singleton(const Singleton&)            = delete;
        Singleton(Singleton&&)                 = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&)      = delete;

    protected:
        Singleton() = default;

    public:
        static T& GetInstance()
        {
            static T instance;
            return instance;
        }

        ~Singleton() {}
    };
}  // namespace HBSoft
