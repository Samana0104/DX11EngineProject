#include "pch.h"
#include "CollisionComponent.h"
using namespace HBSoft;

CollisionComponent::CollisionComponent(Transform3D& transform, bool isCollision)
    : m_transform(transform), m_isCollision(isCollision)
{}

void CollisionComponent::AddAABBRange(const AABB& aabb)
{
    m_colRanges.push_back(aabb);
}

bool CollisionComponent::IsCollision(const AABB& aabb)
{
    if (!m_isCollision)
        return false;

    for (size_t i = 0; i < m_colRanges.size(); i++)
    {
        AABB colRange    = m_colRanges[i];
        colRange.min[0] *= glm::abs(m_transform.m_scale[0]);
        colRange.min[1] *= glm::abs(m_transform.m_scale[1]);
        colRange.min[2] *= glm::abs(m_transform.m_scale[2]);
        colRange.min    += m_transform.m_pos;

        colRange.max[0] *= glm::abs(m_transform.m_scale[0]);
        colRange.max[1] *= glm::abs(m_transform.m_scale[1]);
        colRange.max[2] *= glm::abs(m_transform.m_scale[2]);
        colRange.max    += m_transform.m_pos;

        if (colRange.IsCollision(aabb))
            return true;
    }

    return false;
}

bool CollisionComponent::IsCollision(const CollisionComponent& component)
{
    if (!m_isCollision)
        return false;

    for (size_t i = 0; i < component.m_colRanges.size(); i++)
    {
        AABB colRange    = component.m_colRanges[i];
        colRange.min[0] *= glm::abs(m_transform.m_scale[0]);
        colRange.min[1] *= glm::abs(m_transform.m_scale[1]);
        colRange.min[2] *= glm::abs(m_transform.m_scale[2]);
        colRange.min    += m_transform.m_pos;

        colRange.max[0] *= glm::abs(m_transform.m_scale[0]);
        colRange.max[1] *= glm::abs(m_transform.m_scale[1]);
        colRange.max[2] *= glm::abs(m_transform.m_scale[2]);
        colRange.max    += m_transform.m_pos;

        if (IsCollision(colRange))
            return true;
    }

    return false;
}

void CollisionComponent::DrawBoundary(std::shared_ptr<LineObj> line)
{
    for (size_t i = 0; i < m_colRanges.size(); i++)
    {
        AABB colRange = m_colRanges[i];
        vec3 line1, line2;
        colRange.min[0] *= glm::abs(m_transform.m_scale[0]);
        colRange.min[1] *= glm::abs(m_transform.m_scale[1]);
        colRange.min[2] *= glm::abs(m_transform.m_scale[2]);
        colRange.min    += m_transform.m_pos;

        colRange.max[0] *= glm::abs(m_transform.m_scale[0]);
        colRange.max[1] *= glm::abs(m_transform.m_scale[1]);
        colRange.max[2] *= glm::abs(m_transform.m_scale[2]);
        colRange.max    += m_transform.m_pos;


        line1 = colRange.min;
        line2 = {colRange.min[0], colRange.min[1], colRange.max[2]};
        line->Draw(line1, line2, {1.f, 0.f, 0.f, 1.f});

        line2 = {colRange.max[0], colRange.min[1], colRange.min[2]};
        line->Draw(line1, line2, {1.f, 0.f, 0.f, 1.f});

        line2 = {colRange.min[0], colRange.max[1], colRange.min[2]};
        line->Draw(line1, line2, {1.f, 0.f, 0.f, 1.f});

        line1 = colRange.max;
        line2 = {colRange.max[0], colRange.max[1], colRange.min[2]};
        line->Draw(line1, line2, {1.f, 0.f, 0.f, 1.f});

        line2 = {colRange.max[0], colRange.min[1], colRange.max[2]};
        line->Draw(line1, line2, {1.f, 0.f, 0.f, 1.f});

        line2 = {colRange.min[0], colRange.max[1], colRange.max[2]};
        line->Draw(line1, line2, {1.f, 0.f, 0.f, 1.f});
    }
}
