/*
author : 변한빛
description : 쉐이더 상수 버퍼 구조체 정의 모음

version: 1.0.0
date: 2024-11-11
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    struct VSShaderCB
    {
        mat4 model;
        mat4 view;
        mat4 proj;
    };
}  // namespace HBSoft
