#pragma once

#include "pch.h"
#include "3D/LineObj.h"
#include "3D/Transform3D.h"
#include "Collision.h"

namespace HBSoft
{
    class CollisionComponent
    {
    private:
        Transform3D& m_transform;

    public:
        std::vector<AABB> m_colRanges;

        bool m_isCollision;

    public:
        CollisionComponent(Transform3D& transform, bool isCollision = false);

        void AddAABBRange(const AABB& aabb);
        bool IsCollision(const AABB& aabb);
        bool IsCollision(const CollisionComponent& component);

        /*
        Debug¿ëµµ
        */
        void DrawBoundary(std::shared_ptr<LineObj> line);
    };
}  // namespace HBSoft
