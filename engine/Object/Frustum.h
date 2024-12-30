/*
author : ���Ѻ�
description : view frustum culling�� ���� frustumŬ���� �������

version: 1.0.0
date: 2024-12-29
*/
#pragma once

#include "pch.h"
#include "Collision.h"

namespace HBSoft
{
    class Frustum
    {
    public:
        vec3  m_frustum[8];
        Plane m_plane[6];

    public:
        void Set(const mat4& viewMat, const mat4& projMat);

    public:
        bool IsFrustumInBox(const Box& box);
    };
}  // namespace HBSoft
