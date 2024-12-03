#include "pch.h"
#include "AABBCollider.h"

using namespace HBSoft;

AABB AABBCollider::CalculateAABB(AABB aabb, vec3 center, vec3 size)
{

    aabb.min = center - size * 0.5f;
    aabb.max = center + size * 0.5f;

    return aabb;
}

bool AABBCollider::CheckAABBCollision(const AABB& a, const AABB& b)
{
    if (a.max.x < b.min.x || a.min.x > b.max.x)
        return false;
    if (a.max.y < b.min.y || a.min.y > b.max.y)
        return false;
    if (a.max.z < b.min.z || a.min.z > b.max.z)
        return false;

    return true;
}

void AABBCollider::UpdateAABB(AABB& aabb, const vec3& position, const vec3& size)
{
    aabb.min = position - (size * 0.5f);
    aabb.max = position + (size * 0.5f);
}
