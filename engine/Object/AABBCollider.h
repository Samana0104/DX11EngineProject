#pragma once
#pragma once

#include "3D/Object3D.h"
#include "3D/Transform3D.h"

namespace HBSoft
{
    struct AABB
    {
        vec3 min;
        vec3 max;
    };

    class AABBCollider
    {
    public:
        vec3 m_center;
        vec3 m_size;

    public:
        AABB CalculateAABB(AABB aabb, vec3 center, vec3 size);

        bool CheckAABBCollision(const AABB& a, const AABB& b);

        void UpdateAABB(AABB& aabb, const vec3& position, const vec3& size);
    };
}  // namespace HBSoft