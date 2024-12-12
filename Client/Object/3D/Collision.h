#pragma once

#include "pch.h"

namespace HBSoft
{
    struct AABB
    {
        vec3 min;
        vec3 max;
    };

    struct OBB
    {
        vec3  center;
        vec3  axis[3];
        float distance[3];
    };

    struct Box
    {
        AABB aabb;
        OBB  obb;
    };

    struct Sphere
    {
        vec3  center;
        float radius;
    };

    // struct T_Plane
    //{
    //     float a, b, c, d;
    //     void  Set(T::TVector3 v0, T::TVector3 v1, T::TVector3 v2);
    //     void  Set(T::TVector3 v0, T::TVector3 vNormal);
    // };
}  // namespace HBSoft
