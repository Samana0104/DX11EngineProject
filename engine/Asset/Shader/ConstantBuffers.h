/*
author : ���Ѻ�
description : ���̴� ��� ���� ����ü ���� ����

version: 1.0.0
date: 2024-11-11
*/

#pragma once
#include "glm/glm.hpp"

namespace HBSoft
{
    struct VSShaderCB
    {
        mat4   model;
        mat4   view;
        mat4   proj;
        float4 color;

        VSShaderCB()
            : model(mat4(1.f)), view(mat4(1.f)), proj(mat4(1.f)), color(1.f)
        {}
    };

    struct LineVSCB
    {
        mat4 model;
        mat4 view;
        mat4 proj;

        LineVSCB()
            : model(mat4(1.f)), view(mat4(1.f)), proj(mat4(1.f))
        {}
    };
}  // namespace HBSoft
