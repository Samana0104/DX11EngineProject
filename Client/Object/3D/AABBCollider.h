#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/Transform3D.h"
#include "Shader/ConstantBuffers.h"

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
        AABB CalculateAABB(AABB aabb, vec3 center, vec3 size);

        bool CheckAABBCollision(const AABB& a, const AABB& b);

        void UpdateAABB(AABB& aabb, const vec3& position, const vec3& size);

        vec3 GetCollisionDepth(const AABB& a, const AABB& b);

        vec3 GetMinimum(const vec3& collisionDepth);

        void ResolveCollision(const AABB& a, const AABB& b);
    };
}  // namespace HBSoft