/*
author : ���Ѻ�
description : 2D������ �׷��� ������Ʈ�� �����ϱ� ���� ��� ����

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
