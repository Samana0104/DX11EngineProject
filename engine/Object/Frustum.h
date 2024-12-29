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
