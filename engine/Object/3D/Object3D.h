/*
author : 변한빛
description : 3D상으로 그려질 오브젝트를 정의하기 위한 헤더 파일

version: 1.0.8
date: 2024-11-29
*/

#pragma once
#include "Core.h"
#include "Object.h"
#include "Transform3D.h"
#include "Shader/ConstantBuffers.h"
#include "3D/DirectionalLight.h"

namespace HBSoft
{
    class Object3D : public Object
    {
    protected:
        Transform3D  m_transform;
        DefaultPSCB0 m_psCB0;

        std::shared_ptr<DirectionalLight> m_light;

    protected:
        Object3D()  = default;
        ~Object3D() = default;

    public:
        void SetLight(std::shared_ptr<DirectionalLight> light);

        virtual void UpdateDefaultCB() override;

        virtual void Init()                        = 0;
        virtual void Release()                     = 0;
        virtual void Update(const float deltaTime) = 0;
        virtual void Render()                      = 0;
    };
}  // namespace HBSoft