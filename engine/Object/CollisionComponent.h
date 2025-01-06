/*
author : ���Ѻ�
description : collision component �������

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
        bool         m_isCollision;  // �ݸ��� �Ұ��� ������

        std::vector<std::string> m_colNames;
        std::vector<AABB>        m_colAreas;

    public:
        std::set<std::string> m_collidedAreaNames;
        // IsCollision���� �浹���� �浹ü �̸� ���ϴ� ����
        std::vector<AABB> m_collidedAreas;  // IsCollision���� �浹���� �浹 ���� �����ϴ� ����
        vec3 m_collidedNormal;              // IsCollision���� �浹���� �븻�� ���ϴ� ����

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
        Debug�뵵
        */
        void DrawBoundary(std::shared_ptr<LineObj> line);
    };
}  // namespace HBSoft
