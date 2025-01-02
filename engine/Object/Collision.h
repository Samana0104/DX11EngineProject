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

        AABB()
        {
            min = vec3(0.f);
            max = vec3(0.f);
        }

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

        AABB GetCollisionArea(const AABB& aabb)
        {
            AABB colAABB;
            vec3 colMin, colMax;
            colMin.x = glm::max<float>(min.x, aabb.min.x);
            colMin.y = glm::max<float>(min.y, aabb.min.y);
            colMin.z = glm::max<float>(min.z, aabb.min.z);

            colMax.x = glm::min<float>(max.x, aabb.max.x);
            colMax.y = glm::min<float>(max.y, aabb.max.y);
            colMax.z = glm::min<float>(max.z, aabb.max.z);

            colAABB.min[0] = colMin[0];
            colAABB.min[1] = colMin[1];
            colAABB.min[2] = colMin[2];

            colAABB.max[0] = colMax[0];
            colAABB.max[1] = colMax[1];
            colAABB.max[2] = colMax[2];

            return colAABB;
        }

        vec3 ComputeNormal(const vec3& moveVec, const vec3& pos)
        {
            float dx1 = std::fabs(pos.x - min.x);
            float dx2 = std::fabs(pos.x - max.x);
            float dy1 = std::fabs(pos.y - min.y);
            float dy2 = std::fabs(pos.y - max.y);
            float dz1 = std::fabs(pos.z - min.z);
            float dz2 = std::fabs(pos.z - max.z);

            // Determine closest face
            float minDist = std::min({dx1, dx2, dy1, dy2, dz1, dz2});
            if (minDist == dx1)
                return {-1, 0, 0};  // Left
            if (minDist == dx2)
                return {1, 0, 0};  // Right
            if (minDist == dy1)
                return {0, -1, 0};  // Bottom
            if (minDist == dy2)
                return {0, 1, 0};  // Top
            if (minDist == dz1)
                return {0, 0, -1};  // Front
            if (minDist == dz2)
                return {0, 0, 1};  // Back
            return {0, 0, 0};
        }
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

    struct Plane
    {
        float a, b, c, d;
        void  Set(vec3 v0, vec3 v1, vec3 v2);
        void  Set(vec3 v0, vec3 vNormal);
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
}  // namespace HBSoft
