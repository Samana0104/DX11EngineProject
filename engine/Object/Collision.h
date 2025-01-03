/*
author : 변한빛
description : 기본 collision 모음

version: 1.0.5
date: 2025-01-03
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

        AABB GetIntersectArea(const AABB& aabb)
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

        vec3 ComputeNormal(const AABB& box1)
        {
            float overlapX = glm::min(box1.max.x, max.x) - glm::max(box1.min.x, min.x);
            float overlapY = glm::min(box1.max.y, max.y) - glm::max(box1.min.y, min.y);
            float overlapZ = glm::min(box1.max.z, max.z) - glm::max(box1.min.z, min.z);

            if (overlapX < overlapY && overlapX < overlapZ)
            {
                return {box1.max.x > max.x ? -1.0f : 1.0f, 0.0f, 0.0f};  // X축 노말
            }
            else if (overlapY < overlapX && overlapY < overlapZ)
            {
                return {0.0f, box1.max.y > max.y ? -1.0f : 1.0f, 0.0f};  // Y축 노말
            }
            else
            {
                return {0.0f, 0.0f, box1.max.z > max.z ? -1.0f : 1.0f};  // Z축 노말
            }
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

        void Set(vec3 v0, vec3 v1, vec3 v2)
        {
            vec3 e0 = v1 - v0;
            vec3 e1 = v2 - v0;
            vec3 normal;
            normal = glm::cross(e0, e1);
            normal = glm::normalize(normal);

            a = normal.x;
            b = normal.y;
            c = normal.z;
            d = -glm::dot(normal, v0);
        }

        void Set(vec3 v0, vec3 normal)
        {
            a = normal.x;
            b = normal.y;
            c = normal.z;
            d = -glm::dot(normal, v0);
        }
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
