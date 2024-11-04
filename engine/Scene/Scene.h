/*
author : ���Ѻ�
description : ���� �⺻ ���Ǹ� ���� ��� ���� ��� ���� �� ������ ����Ѵ�

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    class Scene
    {
    private:
        Scene(Scene&&)                 = delete;
        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&)      = delete;

    public:
        Scene() = default;

        virtual void Render()                = 0;
        virtual void Release()               = 0;
        virtual void Reset()                 = 0;
        virtual void Start()                 = 0;
        virtual void End()                   = 0;
        virtual void Update(float deltaTime) = 0;
    };
}  // namespace HBSoft
