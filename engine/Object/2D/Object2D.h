/*
author : 변한빛
description : 2D상으로 그려질 오브젝트를 정의하기 위한 헤더 파일

version: 1.0.5
date: 2024-11-30
*/

#pragma once
#include "Core.h"
#include "Object.h"
#include "Transform2D.h"
#include "Shader/ConstantBuffers.h"

namespace HBSoft
{
    class Object2D : public Object
    {
    protected:
        Transform2D m_transform;
        DefaultCB0  m_cb0;


    protected:
        Object2D()  = default;
        ~Object2D() = default;

    public:
        virtual void UpdateDefaultCB() override;

        virtual void Update(const float deltaTime) = 0;
        virtual void Render()                      = 0;
        virtual void Init()                        = 0;
        virtual void Release()                     = 0;
    };
}  // namespace HBSoft
