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

vec3 AABBCollider::GetCollisionDepth(const AABB& a, const AABB& b)
{
    float overLapX = min(a.max.x, b.max.x) - max(a.min.x, b.min.x);
    float overLapY = min(a.max.y, b.max.y) - max(a.min.y, b.min.y);
    float overLapZ = min(a.max.z, b.max.z) - max(a.min.z, b.min.z);

    return {overLapX, overLapY, overLapZ};
}

vec3 AABBCollider::GetMinimum(const vec3& collisionDepth)
{
    float minDepth = std::min({collisionDepth.x, collisionDepth.y, collisionDepth.z});
    if (minDepth == collisionDepth.x)
        return {collisionDepth.x, 0.0f, 0.0f};
    if (minDepth == collisionDepth.z)
        return {0.0f, 0.0f, collisionDepth.z};
}

void AABBCollider::UpdateAABB(AABB& aabb, const vec3& position, const vec3& size)
{
    aabb.min = position - (size * 0.5f);
    aabb.max = position + (size * 0.5f);
}

void AABBCollider::ResolveCollision(const AABB& a, const AABB& b)
{
    vec3 collisionDepth = GetCollisionDepth(a, b);
    vec3 minimum        = GetMinimum(collisionDepth);

    vec3 b_center;

    b_center.x = (b.min.x + b.max.x) / 2;
    b_center.y = (b.min.y + b.max.y) / 2;
    b_center.z = (b.min.z + b.max.z) / 2;

    vec3 a_center;

    a_center.x = (a.min.x + a.max.x) / 2;
    a_center.y = (a.min.y + a.max.y) / 2;
    a_center.z = (a.min.z + a.max.z) / 2;


    if ((b_center.x - a_center.x) < 0)
        minimum.x = -minimum.x;
    if (b_center.y - a_center.y < 0)
        minimum.y = -minimum.y;
    if (b_center.z - a_center.z < 0)
        minimum.z = -minimum.z;

    b_center.x += minimum.x;
    b_center.y += minimum.y;
    b_center.z += minimum.z;
}
