#pragma once

#include "pch.h"
#include "3D/Transform3D.h"
#include "Collision.h"

namespace HBSoft
{
    class LineObj;

    class CollisionComponent
    {
    private:
        Transform3D& m_transform;

    public:
        std::vector<AABB> m_colRanges;

        AABB m_collidedArea;  // IsCollision���� �浹���� �浹 ���� �����ϴ� �Լ�
        bool m_isCollision;

    public:
        CollisionComponent(Transform3D& transform, bool isCollision = true);

        void AddAABBRange(const AABB& aabb);
        void DeleteAABBRange(size_t idx);
        void SetAABBRange(const AABB& aabb, size_t idx);
        bool IsCollision(const AABB& aabb);
        bool IsCollision(const CollisionComponent& component);

        /*
        Debug�뵵
        */
        void DrawBoundary(std::shared_ptr<LineObj> line);
    };
}  // namespace HBSoft
