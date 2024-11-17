/*
author : ���Ѻ�
description : ���̴� ��� ���� ����ü ���� ����

version: 1.0.5
date: 2024-11-17
*/

#pragma once
#include "glm/glm.hpp"

namespace HBSoft
{
    struct DefaultCB0
    {
        mat4   world;
        mat4   invWorld;
        mat4   view;
        mat4   proj;

        DefaultCB0()
            : world(mat4(1.f)), invWorld(mat4(1.f)), view(mat4(1.f)), proj(mat4(1.f))
        {}
    };

    // struct LineVSCB
    //{
    //     mat4 model;
    //     mat4 view;
    //     mat4 proj;

    //    LineVSCB()
    //        : model(mat4(1.f)), view(mat4(1.f)), proj(mat4(1.f))
    //    {}
    //};
}  // namespace HBSoft
