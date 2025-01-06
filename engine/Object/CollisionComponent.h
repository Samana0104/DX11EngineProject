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
        bool         m_isCollision;  // 콜리젼 할건지 말건지

        std::vector<std::string> m_colNames;
        std::vector<AABB>        m_colAreas;

    public:
        std::set<std::string> m_collidedAreaNames;
        // IsCollision에서 충돌나면 충돌체 이름 구하는 변수
        std::vector<AABB> m_collidedAreas;  // IsCollision에서 충돌나면 충돌 영역 저장하는 변수
        vec3 m_collidedNormal;              // IsCollision에서 충돌나면 노말값 구하는 변수

    private:
        bool IsCollided(const AABB& aabb, CollisionComponent& component);

    public:
        void Init();

        CollisionComponent(Transform3D& transform, bool isCollision = true);

        void AddAABBRange(const AABB& colArea, const stringV colName);
        void DeleteAABBRange(size_t idx);
        void SetAABBRange(const AABB& aabb, size_t idx);

        bool IsCollision(CollisionComponent& component);
        AABB GetTransformedBound(size_t idx) const;
        /*
        Debug용도
        */
        void DrawBoundary(std::shared_ptr<LineObj> line);
    };
}  // namespace HBSoft
