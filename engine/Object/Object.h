/*
author : 변한빛
description : Object의 기본 정의

version: 1.0.4
date: 2024-12-13
*/

#pragma once

#include "Camera/Camera.h"
#include "Renderable.h"
#include "EasyRender.h"

namespace HBSoft
{
    class Object : public Renderable
    {
    public:
        DefaultVSCB0 m_vsCB0;

        EasyRender              m_easyRender;
        std::shared_ptr<Camera> m_camera;

    protected:
        Object()  = default;
        ~Object() = default;

    public:
        void SetCamera(std::shared_ptr<Camera> camera);

        virtual void UpdateDefaultCB() = 0;

        virtual void Init()                        = 0;
        virtual void Release()                     = 0;
        virtual void Update(const float deltaTime) = 0;
        virtual void Render()                      = 0;
    };
}  // namespace HBSoft
