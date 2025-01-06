/*
author : 변한빛
description : collision component 소스파일

version: 1.0.5
date: 2025-01-02
*/

#include "pch.h"
#include "CollisionComponent.h"
#include "3D/LineObj.h"
using namespace HBSoft;

void CollisionComponent::Init()
{
    m_collidedNormal = vec3(0.f);
    m_collidedAreas.clear();
    m_collidedAreaNames.clear();
}

CollisionComponent::CollisionComponent(Transform3D& transform, bool isCollision)
    : m_transform(transform), m_isCollision(isCollision)
{
    m_collidedAreas.reserve(10);
    m_colNames.reserve(10);
    m_colAreas.reserve(10);
}

void CollisionComponent::AddAABBRange(const AABB& colArea, const stringV colName)
{
    m_colAreas.push_back(colArea);
    m_colNames.push_back(colName.data());
}

void CollisionComponent::DeleteAABBRange(size_t idx)
{
    if (idx >= m_colAreas.size())
        return;

    m_colAreas.erase(m_colAreas.begin() + idx);
}

void CollisionComponent::SetAABBRange(const AABB& aabb, size_t idx)
{
    if (idx >= m_colAreas.size())
        return;

    m_colAreas[idx] = aabb;
}

bool CollisionComponent::IsCollided(const AABB& aabb, CollisionComponent& component)
{
    if (!m_isCollision)
        return false;

    for (size_t i = 0; i < m_colAreas.size(); i++)
    {
        AABB colArea    = m_colAreas[i];
        colArea.min[0] *= glm::abs(m_transform.m_scale[0]);
        colArea.min[1] *= glm::abs(m_transform.m_scale[1]);
        colArea.min[2] *= glm::abs(m_transform.m_scale[2]);
        colArea.min    += m_transform.m_pos;

        colArea.max[0] *= glm::abs(m_transform.m_scale[0]);
        colArea.max[1] *= glm::abs(m_transform.m_scale[1]);
        colArea.max[2] *= glm::abs(m_transform.m_scale[2]);
        colArea.max    += m_transform.m_pos;

        if (colArea.IsCollision(aabb))
        {
            m_collidedNormal += colArea.ComputeNormal(aabb);
            component.m_collidedAreas.push_back(colArea);
            component.m_collidedAreaNames.insert(m_colNames[i]);
            return true;
        }
    }
    return false;
}

bool CollisionComponent::IsCollision(CollisionComponent& component)
{
    if (!m_isCollision)
        return false;

    m_collidedNormal = vec3(0.f);
    m_collidedAreas.clear();
    m_collidedAreaNames.clear();
    component.m_collidedAreas.clear();
    component.m_collidedAreaNames.clear();

    for (size_t i = 0; i < component.m_colAreas.size(); i++)
    {
        AABB colArea    = component.m_colAreas[i];
        colArea.min[0] *= glm::abs(component.m_transform.m_scale[0]);
        colArea.min[1] *= glm::abs(component.m_transform.m_scale[1]);
        colArea.min[2] *= glm::abs(component.m_transform.m_scale[2]);
        colArea.min    += component.m_transform.m_pos;

        colArea.max[0] *= glm::abs(component.m_transform.m_scale[0]);
        colArea.max[1] *= glm::abs(component.m_transform.m_scale[1]);
        colArea.max[2] *= glm::abs(component.m_transform.m_scale[2]);
        colArea.max    += component.m_transform.m_pos;

        if (IsCollided(colArea, component))
        {
            m_collidedAreaNames.insert(component.m_colNames[i]);
            m_collidedAreas.push_back(colArea);
        }
    }

    if (m_collidedAreas.size() >= 1)
    {
        m_collidedNormal = glm::normalize(m_collidedNormal);
        return true;
    }

    return false;
}

AABB CollisionComponent::GetTransformedBound(size_t idx) const
{
    AABB box;

    if (idx >= m_colAreas.size())
        return box;

    box.min[0] *= glm::abs(m_transform.m_scale[0]);
    box.min[1] *= glm::abs(m_transform.m_scale[1]);
    box.min[2] *= glm::abs(m_transform.m_scale[2]);
    box.min    += m_transform.m_pos;

    box.max[0] *= glm::abs(m_transform.m_scale[0]);
    box.max[1] *= glm::abs(m_transform.m_scale[1]);
    box.max[2] *= glm::abs(m_transform.m_scale[2]);
    box.max    += m_transform.m_pos;
    return box;
}

void CollisionComponent::DrawBoundary(std::shared_ptr<LineObj> line)
{
    for (size_t i = 0; i < m_colAreas.size(); i++)
    {
        AABB colArea = m_colAreas[i];
        vec3 line1, line2;
        colArea.min[0] *= glm::abs(m_transform.m_scale[0]);
        colArea.min[1] *= glm::abs(m_transform.m_scale[1]);
        colArea.min[2] *= glm::abs(m_transform.m_scale[2]);
        colArea.min    += m_transform.m_pos;

        colArea.max[0] *= glm::abs(m_transform.m_scale[0]);
        colArea.max[1] *= glm::abs(m_transform.m_scale[1]);
        colArea.max[2] *= glm::abs(m_transform.m_scale[2]);
        colArea.max    += m_transform.m_pos;


        line1 = colArea.min;
        line2 = {colArea.min[0], colArea.min[1], colArea.max[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line2 = {colArea.max[0], colArea.min[1], colArea.min[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line2 = {colArea.min[0], colArea.max[1], colArea.min[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line1 = colArea.max;
        line2 = {colArea.max[0], colArea.max[1], colArea.min[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line2 = {colArea.max[0], colArea.min[1], colArea.max[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line2 = {colArea.min[0], colArea.max[1], colArea.max[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});
    }
}
