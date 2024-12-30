/*
author : 변한빛
description : 디버그 카메라를 정의하기 위한 헤더 파일

version: 1.0.0
date: 2024-12-30
*/

#pragma once

#include "Core.h"
#include "Camera.h"

namespace HBSoft
{
    class DebugCamera : public Camera
    {
    private:
        float m_speed;
        float m_accel;

    public:
        DebugCamera();

        virtual void Update(const float deltaTime) override;
        virtual void Move(const vec3 pos) override;
    };
}  // namespace HBSoft
