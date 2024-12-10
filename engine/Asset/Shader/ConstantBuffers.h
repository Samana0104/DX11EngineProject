/*
author : 변한빛, 이지혁
description(변한빛) : 쉐이더 상수 버퍼 구조체 정의 모음
description(이지혁) : 기본 상수 버퍼에 빛 방향, 빛 위치값 추가

version: 1.0.9
date: 2024-12-10
*/

#pragma once
#include "glm/glm.hpp"

namespace HBSoft
{
    // default constant buffer
    struct DefaultCB0
    {
        mat4 world;
        mat4 normalWorld;
        mat4 view;
        mat4 proj;
        vec4 m_vLightDir;
        vec4 m_vLightPos;

        DefaultCB0()
            : world(mat4(1.f)), normalWorld(mat4(1.f)), view(mat4(1.f)), proj(mat4(1.f))
        {}
    };

}  // namespace HBSoft
