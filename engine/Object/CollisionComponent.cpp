#include "pch.h"
#include "CollisionComponent.h"
#include "3D/LineObj.h"
using namespace HBSoft;

CollisionComponent::CollisionComponent(Transform3D& transform, bool isCollision)
    : m_transform(transform), m_isCollision(isCollision)
{
    m_collidedArea.min = vec3(0.f);
    m_collidedArea.max = vec3(0.f);
}

void CollisionComponent::AddAABBRange(const AABB& aabb)
{
    m_colRanges.push_back(aabb);
}

void CollisionComponent::DeleteAABBRange(size_t idx)
{
    if (idx >= m_colRanges.size())
        return;

    m_colRanges.erase(m_colRanges.begin() + idx);
}

void CollisionComponent::SetAABBRange(const AABB& aabb, size_t idx)
{
    if (idx >= m_colRanges.size())
        return;

    m_colRanges[idx] = aabb;
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
        {
            m_collidedArea = colRange.GetCollisionArea(aabb);
            return true;
        }
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
        colRange.min[0] *= glm::abs(component.m_transform.m_scale[0]);
        colRange.min[1] *= glm::abs(component.m_transform.m_scale[1]);
        colRange.min[2] *= glm::abs(component.m_transform.m_scale[2]);
        colRange.min    += component.m_transform.m_pos;

        colRange.max[0] *= glm::abs(component.m_transform.m_scale[0]);
        colRange.max[1] *= glm::abs(component.m_transform.m_scale[1]);
        colRange.max[2] *= glm::abs(component.m_transform.m_scale[2]);
        colRange.max    += component.m_transform.m_pos;

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
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line2 = {colRange.max[0], colRange.min[1], colRange.min[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line2 = {colRange.min[0], colRange.max[1], colRange.min[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line1 = colRange.max;
        line2 = {colRange.max[0], colRange.max[1], colRange.min[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line2 = {colRange.max[0], colRange.min[1], colRange.max[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});

        line2 = {colRange.min[0], colRange.max[1], colRange.max[2]};
        line->Draw(line1, line2, {glm::abs(cos(i)), glm::abs(sin(i)), glm::abs(cos(i)), 1.f});
    }
}
