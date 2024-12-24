/*
author : º¯ÇÑºû
description : collision ¸ðÀ½

version: 1.0.0
date: 2024-12-24
*/
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

        void SetRangeFromAABB(const AABB& aabbCollision)
        {
            vec3  minToMax = aabbCollision.max - aabbCollision.min;
            float maxLength;

            maxLength = glm::max<float>(glm::max<float>(glm::abs(minToMax.x), glm::abs(minToMax.y)),
                                        glm::abs(minToMax.z));

            radius = maxLength * 0.5f;
            center = (aabbCollision.max + aabbCollision.min) * 0.5f;
        }
    };

    // struct T_Plane
    //{
    //     float a, b, c, d;
    //     void  Set(T::TVector3 v0, T::TVector3 v1, T::TVector3 v2);
    //     void  Set(T::TVector3 v0, T::TVector3 vNormal);
    // };
}  // namespace HBSoft
