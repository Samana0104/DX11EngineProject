/*
author : 변한빛
description : 쉐이더 상수 버퍼 구조체 정의 모음

version: 1.0.8
date: 2024-11-30
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

        DefaultCB0()
            : world(mat4(1.f)), normalWorld(mat4(1.f)), view(mat4(1.f)), proj(mat4(1.f))
        {}
    };

}  // namespace HBSoft
