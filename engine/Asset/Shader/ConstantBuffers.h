/*
author : ���Ѻ�
description : ���̴� ��� ���� ����ü ���� ����

version: 1.0.8
date: 2024-11-30
*/

#pragma once
#include "glm/glm.hpp"

namespace HBSoft
{
    // default constant buffer
    struct DefaultVSCB0
    {
        mat4 world;
        mat4 normalWorld;
        mat4 view;
        mat4 proj;

        DefaultVSCB0()
            : world(mat4(1.f)), normalWorld(mat4(1.f)), view(mat4(1.f)), proj(mat4(1.f))
        {}
    };

    struct DefaultPSCB0
    {
        vec3  lightDir;
        float lightPower;
        vec3  eyePos;
        float dummy;  // ������۴� 16����Ʈ ������ ���������

        DefaultPSCB0()
            : lightDir(0.f), lightPower(1.f), eyePos(0.f), dummy(0.f)
        {}
    };

}  // namespace HBSoft
