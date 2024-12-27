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

        void SetCenter(const AABB& aabb)
        {
            vec3 center = (aabb.min + aabb.max) * 0.5f;

            min = aabb.min - center;
            max = aabb.max - center;
        }

        bool IsCollision(const AABB& aabb)
        {
            vec3 colMin, colMax;
            colMin.x = glm::max<float>(min.x, aabb.min.x);
            colMin.y = glm::max<float>(min.y, aabb.min.y);
            colMin.z = glm::max<float>(min.z, aabb.min.z);

            colMax.x = glm::min<float>(max.x, aabb.max.x);
            colMax.y = glm::min<float>(max.y, aabb.max.y);
            colMax.z = glm::min<float>(max.z, aabb.max.z);

            if (colMax.x >= colMin.x && colMax.y >= colMin.y && colMax.z >= colMin.z)
                return true;
            else
                return false;
        }
    };

    // struct OBB
    //{
    //     vec3  center;
    //     vec3  axis[3];
    //     float distance[3];
    // };

    // struct Box
    //{
    //     AABB aabb;
    //     OBB  obb;
    // };

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

}  // namespace HBSoft
