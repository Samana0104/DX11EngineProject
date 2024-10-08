#include "pch.h"
#include "CollisionComponent.h"
#include "Actor.h"
using namespace HBSoft;

CollisionComponent::CollisionComponent(Actor& obj) : m_obj(obj)
{
    m_collisionAreas.reserve(5);
}

void CollisionComponent::AddCollisionArea(const RECT_F collisionArea)
{
    m_collisionAreas.push_back(collisionArea);
}

void CollisionComponent::AddCollisionArea(const vec2 scaleVec)
{
    RECT_F rt = {-scaleVec.x * 0.5f, scaleVec.y * 0.5f, scaleVec.x * 0.5f, -scaleVec.y * 0.5f};

    m_collisionAreas.push_back(rt);
}

void CollisionComponent::SetCollisionable(bool isCollisionable)
{
    m_isCollisionable = isCollisionable;
}

void CollisionComponent::ClearCollisionAreas()
{
    m_collisionAreas.clear();
}

bool CollisionComponent::IsCollision(const RECT_F& target)
{
    if (!m_isCollisionable)
        return false;

    RECT_F transformRect = m_obj->GetCartesianRectF();
    RECT_F collisionRect;

    for (auto& collisionArea : m_collisionAreas)
    {
        collisionRect = {collisionArea.left + transformRect.left,
                         collisionArea.top + transformRect.top,
                         collisionArea.right + transformRect.right,
                         collisionArea.bottom + transformRect.bottom};

        if (IsAABBCollision(collisionRect, target))
            return true;
    }

    return false;
}

void CollisionComponent::IsCollisionWithEvent(CollisionComponent& targetCollision)
{
    // �浹 ������Ʈ�� �ƴ϶��

    if (!m_isCollisionable || !targetCollision.m_isCollisionable)
        return;

    vec2   myLocation = m_obj->GetLocation();
    RECT_F myCollisionRect;

    vec2   targetLocation = targetCollision.m_obj->GetLocation();
    RECT_F targetCollisionRect;

    for (auto& selfRange : m_collisionAreas)
    {
        for (auto& targetRange : targetCollision.m_collisionAreas)
        {
            myCollisionRect = {selfRange.left + myLocation.x,
                               selfRange.top + myLocation.y,
                               selfRange.right + myLocation.x,
                               selfRange.bottom + myLocation.y};

            targetCollisionRect = {targetRange.left + targetLocation.x,
                                   targetRange.top + targetLocation.y,
                                   targetRange.right + targetLocation.x,
                                   targetRange.bottom + targetLocation.y};

            if (IsAABBCollision(myCollisionRect, targetCollisionRect))
            {
                if (m_collisionFunc != nullptr)
                    m_collisionFunc(myCollisionRect, targetCollisionRect, targetCollision.m_obj);
                if (targetCollision.m_collisionFunc != nullptr)
                    targetCollision.m_collisionFunc(targetCollisionRect, myCollisionRect, m_obj);
            }
        }
    }
}

bool CollisionComponent::IsCollisionable() const
{
    return m_isCollisionable;
}

void CollisionComponent::RegisterCollisionEvent(COLLISION_FUNC _func)
{
    m_collisionFunc = _func;
}

void CollisionComponent::ResizeCollisionArea()
{
    ClearCollisionAreas();
    m_collisionAreas.push_back(m_obj->GetCartesianScaleRectF());
}

RECT_F CollisionComponent::GetIntersectionRect(const RECT_F& rt1, const RECT_F& rt2)
{
    float left, top;
    float right, bottom;

    left   = max(rt1.left, rt2.left);
    top    = min(rt1.top, rt2.top);
    right  = min(rt1.right, rt2.right);
    bottom = max(rt1.bottom, rt2.bottom);

    return {left, top, right, bottom};
}

vec2 CollisionComponent::GetCorrectionForCollision(const vec2 offsetDir, const vec2 targetLocation,
                                                   const RECT_F& rt1, const RECT_F& rt2)
{
    vec2 correctionVec   = {0.f, 0.f};
    vec2 myLocation      = m_obj->GetLocation();
    vec2 FromObjToTarget = targetLocation - myLocation;

    RECT_F beforeRt1X = {
        rt1.left - offsetDir.x,
        rt1.top,
        rt1.right - offsetDir.x,
        rt1.bottom,
    };

    RECT_F beforeRt1Y = {rt1.left, rt1.top - offsetDir.y, rt1.right, rt1.bottom - offsetDir.y};

    RECT_F intersectionRt = GetIntersectionRect(rt1, rt2);

    float intersectWidth  = abs(intersectionRt.right - intersectionRt.left);
    float intersectHeight = abs(intersectionRt.top - intersectionRt.bottom);

    bool IsXAxisCollided = IsAABBCollision(beforeRt1Y, rt2);  // ���� �浹�̸� x�� �浹�����̶�� ��
    bool IsYAxisCollided = IsAABBCollision(beforeRt1X, rt2);  // ���� �浹�̸� y�� �浹�����̶�� ��

    // �� �浹�� ���� Ư��ó��
    // if (IsXAxisCollided && IsYAxisCollided)
    // {
    //     return correctionVec;
    // }
    if (IsXAxisCollided)
    {
        if (_offsetDir.x >= TOLERANCE)
        {
            correctionVec.x = -intersectWidth - TOLERANCE;
        }
        else if (_offsetDir.x <= -TOLERANCE)
        {
            correctionVec.x = intersectWidth + TOLERANCE;
        }
        else  // x�� 0�� ���
        {
            if (FromObjToTarget.x > 0)  // target�� obj �տ� ���� ��
                correctionVec.x = -intersectWidth - TOLERANCE;
            else
                correctionVec.x = intersectWidth + TOLERANCE;
        }
    }
    else if (IsYAxisCollided)
    {
        if (_offsetDir.y >= TOLERANCE)
        {
            correctionVec.y = -intersectHeight - TOLERANCE;
        }
        else if (_offsetDir.y <= -TOLERANCE)
        {
            correctionVec.y = intersectHeight + TOLERANCE;
        }
        else  // y�� 0�� ���
        {
            if (FromObjToTarget.y > 0)  // target�� obj �տ� ���� ��
                correctionVec.y = -intersectWidth - TOLERANCE;
            else
                correctionVec.y = intersectWidth + TOLERANCE;
        }
    }

    return correctionVec;
}

bool CollisionComponent::IsPointInRect(const RECT_F rt1, const vec2 pt)
{
    if (rt1.left <= pt.x && rt1.right >= pt.x)
    {
        if (rt1.top >= pt.y && rt1.bottom <= pt.y)
        {
            return true;
        }
    }
    return false;
}

bool CollisionComponent::IsAABBCollision(const RECT_F& rt1, const RECT_F& rt2)
{
    float left, top;
    float right, bottom;
    float sizeX, sizeY;
    float rt1Width, rt1Height;
    float rt2Width, rt2Height;

    left   = min(rt1.left, rt2.left);
    top    = max(rt1.top, rt2.top);
    right  = max(rt1.right, rt2.right);
    bottom = min(rt1.bottom, rt2.bottom);

    sizeX = abs(right - left);
    sizeY = abs(top - bottom);

    rt1Width  = abs(rt1.right - rt1.left);  // rt1.w + rt2.w;
    rt1Height = abs(rt1.top - rt1.bottom);
    rt2Width  = abs(rt2.right - rt2.left);  // rt1.w + rt2.w;
    rt2Height = abs(rt2.top - rt2.bottom);

    if ((rt1Width + rt2Width) - sizeX > TOLERANCE && (rt1Height + rt2Height) - sizeY > TOLERANCE)
        return true;

    return false;
}

bool CollisionComponent::IsAABBCollision(const Transform2D& _objM, const Transform2D& _targetM)
{
    vec2 objScale       = _objM.GetScale();
    vec2 objLocation    = _objM.GetLocation();
    vec2 targetScale    = _targetM.GetScale();
    vec2 targetLocation = _targetM.GetLocation();

    vec2 objToTarget     = glm::abs(targetLocation - objLocation);
    vec2 minimumDistance = {objScale.x / 2 + targetScale.x / 2, objScale.y / 2 + targetScale.y / 2};
    minimumDistance      = glm::abs(minimumDistance);

    if (objToTarget.x <= minimumDistance.x && objToTarget.y <= minimumDistance.y)
        return true;
    else
        return false;
}

bool CollisionComponent::IsOBBCollision(const Transform2D& _objM, const Transform2D& _targetM)
{
    vec2  objScale       = _objM.GetScale();
    vec2  objLocation    = _objM.GetLocation();
    float objAngle       = _objM.GetAngle();
    vec2  targetScale    = _targetM.GetScale();
    vec2  targetLocation = _targetM.GetLocation();
    float targetAngle    = _targetM.GetAngle();

    vec2 objXVec    = Transform2D::RotateAsAngle({objScale.x / 2, 0.f}, objAngle);
    vec2 objYVec    = Transform2D::RotateAsAngle({0.f, objScale.y / 2}, objAngle);
    vec2 targetXVec = Transform2D::RotateAsAngle({targetScale.x / 2, 0.f}, targetAngle);
    vec2 targetYVec = Transform2D::RotateAsAngle({0.f, targetScale.y / 2}, targetAngle);

    vec2 distance = targetLocation - objLocation;

    float distance1 = glm::abs(glm::dot(objXVec, distance)) / glm::length(objXVec);
    float distance2 = glm::abs(glm::dot(objYVec, distance)) / glm::length(objYVec);
    float distance3 = glm::abs(glm::dot(targetXVec, distance)) / glm::length(targetXVec);
    float distance4 = glm::abs(glm::dot(targetYVec, distance)) / glm::length(targetYVec);

    float targetProj1X = glm::abs(glm::dot(objXVec, targetXVec)) / glm::length(objXVec);
    float targetProj1Y = glm::abs(glm::dot(objXVec, targetYVec)) / glm::length(objXVec);
    float objProj1     = glm::length(objXVec);

    float targetProj2X = glm::abs(glm::dot(objYVec, targetXVec)) / glm::length(objYVec);
    float targetProj2Y = glm::abs(glm::dot(objYVec, targetYVec)) / glm::length(objYVec);
    float objProj2     = glm::length(objYVec);

    float objProj1X   = glm::abs(glm::dot(targetXVec, objXVec)) / glm::length(targetXVec);
    float objProj1Y   = glm::abs(glm::dot(targetXVec, objYVec)) / glm::length(targetXVec);
    float targetProj3 = glm::length(targetXVec);

    float objProj2X   = glm::abs(glm::dot(targetYVec, objXVec)) / glm::length(targetYVec);
    float objProj2Y   = glm::abs(glm::dot(targetYVec, objYVec)) / glm::length(targetYVec);
    float targetProj4 = glm::length(targetYVec);

    if (targetProj1X + targetProj1Y + objProj1 < distance1)
        return false;

    if (targetProj2X + targetProj2Y + objProj2 < distance2)
        return false;

    if (objProj1X + objProj1Y + targetProj3 < distance3)
        return false;

    if (objProj2X + objProj2Y + targetProj4 < distance4)
        return false;

    return true;
}
