/*
author : 변한빛
description : collision component 헤더파일

version: 1.0.5
date: 2025-01-02
*/

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

        std::vector<AABB> m_collidedAreas;  // IsCollision에서 충돌나면 충돌 영역 저장하는 함수
        bool m_isCollision;

    public:
        CollisionComponent(Transform3D& transform, bool isCollision = true);

        void AddAABBRange(const AABB& aabb);
        void DeleteAABBRange(size_t idx);
        void SetAABBRange(const AABB& aabb, size_t idx);
        bool IsCollision(const AABB& aabb);
        bool IsCollision(const CollisionComponent& component);

        /*
        Debug용도
        */
        void DrawBoundary(std::shared_ptr<LineObj> line);
    };
}  // namespace HBSoft
