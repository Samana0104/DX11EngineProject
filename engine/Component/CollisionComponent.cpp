#include "pch.h"
#include "CollisionComponent.h"
#include "MyActor.h"
using namespace MyProject;

CollisionComponent::CollisionComponent(MyActor& _obj):
    mObj(_obj)
{
    mCollisionAreas.reserve(5);
}

void CollisionComponent::AddCollisionArea(const RECT_F _collisionArea)
{
    mCollisionAreas.push_back(_collisionArea);
}

void CollisionComponent::AddCollisionArea(const vec2 _scaleVec)
{
    RECT_F rt =
    {
        -_scaleVec.x * 0.5f,
        _scaleVec.y * 0.5f,
        _scaleVec.x * 0.5f,
        -_scaleVec.y * 0.5f
    };

    mCollisionAreas.push_back(rt);
}
void CollisionComponent::SetCollisionable(bool _isCollisionable)
{
    mIsCollisionable = _isCollisionable;
}

void CollisionComponent::ClearCollisionAreas()
{
    mCollisionAreas.clear();
}

bool CollisionComponent::IsCollision(const RECT_F& _target)
{
    if (!mIsCollisionable)
        return false;

    RECT_F transformRect = mObj->GetCartesianRectF();
    RECT_F collisionRect;
    
    for (auto& collisionArea : mCollisionAreas)
    {
        collisionRect =
        {
            collisionArea.left + transformRect.left,
            collisionArea.top + transformRect.top,
            collisionArea.right + transformRect.right,
            collisionArea.bottom + transformRect.bottom
        };

        if (IsAABBCollision(collisionRect, _target))
            return true;
    }
    
    return false;
}

void CollisionComponent::IsCollisionWithEvent(CollisionComponent& _targetCollision)
{
    // 충돌 오브젝트가 아니라면

    if (!mIsCollisionable || !_targetCollision.mIsCollisionable)
        return;

    vec2 myLocation = mObj->GetLocation();
    RECT_F myCollisionRect;

    vec2 targetLocation = _targetCollision.mObj->GetLocation();
    RECT_F targetCollisionRect;

    for (auto& selfRange : mCollisionAreas)
    {
        for(auto& targetRange : _targetCollision.mCollisionAreas)
        {
			myCollisionRect =
			{
				selfRange.left + myLocation.x,
				selfRange.top + myLocation.y,
				selfRange.right + myLocation.x,
				selfRange.bottom + myLocation.y
			};
			targetCollisionRect =
			{
				targetRange.left + targetLocation.x,
				targetRange.top + targetLocation.y,
				targetRange.right + targetLocation.x,
				targetRange.bottom + targetLocation.y
			};

            if (IsAABBCollision(myCollisionRect, targetCollisionRect))
            {
                if (mCollisionFunc != nullptr)
                    mCollisionFunc(myCollisionRect, targetCollisionRect, _targetCollision.mObj);
                if(_targetCollision.mCollisionFunc != nullptr)
                    _targetCollision.mCollisionFunc(targetCollisionRect, myCollisionRect, mObj);
            }
		}
    }
}

bool CollisionComponent::IsCollisionable() const
{
    return mIsCollisionable;
}

void CollisionComponent::RegisterCollisionEvent(COLLISION_FUNC _func)
{
    mCollisionFunc = _func;
}

void CollisionComponent::ResizeCollisionArea()
{
    ClearCollisionAreas();
    mCollisionAreas.push_back(mObj->GetCartesianScaleRectF());
}

RECT_F CollisionComponent::GetIntersectionRect(const RECT_F& _rt1, const RECT_F& _rt2)
{
    float left, top;
    float right, bottom;

    left   = max(_rt1.left, _rt2.left);
    top    = min(_rt1.top, _rt2.top);
    right  = min(_rt1.right, _rt2.right);
    bottom = max(_rt1.bottom, _rt2.bottom);

    return {left, top, right, bottom};
}

vec2 CollisionComponent::GetCorrectionForCollision(const vec2 _offsetDir, const vec2 _targetLocation, 
			const RECT_F& _rt1, const RECT_F& _rt2)
{
    vec2 correctionVec = { 0.f, 0.f };
    vec2 myLocation    =  mObj->GetLocation();
    vec2 FromObjToTarget = _targetLocation - myLocation;
    
    RECT_F beforeRt1X =
    {
        _rt1.left   - _offsetDir.x,
        _rt1.top,
        _rt1.right  - _offsetDir.x,
        _rt1.bottom,
    };

    RECT_F beforeRt1Y =
    {
        _rt1.left,
        _rt1.top    - _offsetDir.y,
        _rt1.right,
        _rt1.bottom - _offsetDir.y
    };
    
    RECT_F intersectionRt = GetIntersectionRect(_rt1, _rt2);

	float  intersectWidth  = abs(intersectionRt.right - intersectionRt.left);
	float  intersectHeight = abs(intersectionRt.top - intersectionRt.bottom);

    bool   IsXAxisCollided  = IsAABBCollision(beforeRt1Y, _rt2); // 만약 충돌이면 x와 충돌지점이라는 뜻
    bool   IsYAxisCollided  = IsAABBCollision(beforeRt1X, _rt2); // 만약 충돌이면 y와 충돌지점이라는 뜻

    // 두 충돌은 따로 특수처리
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
        else // x가 0인 경우
        {
            if (FromObjToTarget.x > 0) // target이 obj 앞에 있을 때
				correctionVec.x = -intersectWidth - TOLERANCE;
            else
				correctionVec.x = intersectWidth + TOLERANCE;
        }
    }
    else if(IsYAxisCollided)
    {
        if (_offsetDir.y >= TOLERANCE)
        {
            correctionVec.y = -intersectHeight - TOLERANCE;
        }
        else if (_offsetDir.y <= -TOLERANCE)
        {
            correctionVec.y = intersectHeight + TOLERANCE;
        }
        else // y가 0인 경우
        {
            if (FromObjToTarget.y > 0) // target이 obj 앞에 있을 때
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

	rt1Width = abs(rt1.right - rt1.left);// rt1.w + rt2.w;
	rt1Height = abs(rt1.top - rt1.bottom);
	rt2Width = abs(rt2.right - rt2.left);// rt1.w + rt2.w;
	rt2Height = abs(rt2.top - rt2.bottom);

	if ((rt1Width + rt2Width) - sizeX > TOLERANCE && 
        (rt1Height + rt2Height) - sizeY > TOLERANCE)
		return true;

	return false;
}

bool CollisionComponent::IsAABBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM)
{
    vec2 objScale = _objM.GetScale();
    vec2 objLocation = _objM.GetLocation();
    vec2 targetScale = _targetM.GetScale();
    vec2 targetLocation = _targetM.GetLocation();

    vec2 objToTarget = glm::abs(targetLocation - objLocation);
    vec2 minimumDistance = { objScale.x / 2 + targetScale.x / 2, objScale.y / 2 + targetScale.y / 2 };
    minimumDistance = glm::abs(minimumDistance);

    if (objToTarget.x <= minimumDistance.x && objToTarget.y <= minimumDistance.y)
        return true;
    else
        return false;
}

bool CollisionComponent::IsOBBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM)
{ 
    vec2 objScale     = _objM.GetScale();
    vec2 objLocation  = _objM.GetLocation();
    float objAngle    = _objM.GetAngle();
    vec2 targetScale  = _targetM.GetScale();
    vec2 targetLocation = _targetM.GetLocation();
    float targetAngle = _targetM.GetAngle();

    vec2 objXVec = MyTransformer2D::RotateAsAngle({ objScale.x / 2, 0.f }, objAngle);
    vec2 objYVec = MyTransformer2D::RotateAsAngle({ 0.f, objScale.y / 2 }, objAngle);
    vec2 targetXVec = MyTransformer2D::RotateAsAngle({ targetScale.x / 2, 0.f }, targetAngle);
    vec2 targetYVec = MyTransformer2D::RotateAsAngle({ 0.f, targetScale.y / 2 }, targetAngle);
    
    vec2 distance = targetLocation - objLocation;

    float distance1 = glm::abs(glm::dot(objXVec, distance)) / glm::length(objXVec);
    float distance2 = glm::abs(glm::dot(objYVec, distance)) / glm::length(objYVec);
    float distance3 = glm::abs(glm::dot(targetXVec, distance)) / glm::length(targetXVec);
    float distance4 = glm::abs(glm::dot(targetYVec, distance)) / glm::length(targetYVec);

    float targetProj1X = glm::abs(glm::dot(objXVec, targetXVec)) / glm::length(objXVec);
    float targetProj1Y = glm::abs(glm::dot(objXVec, targetYVec)) / glm::length(objXVec);
    float objProj1 = glm::length(objXVec);

    float targetProj2X = glm::abs(glm::dot(objYVec, targetXVec)) / glm::length(objYVec);
    float targetProj2Y = glm::abs(glm::dot(objYVec, targetYVec)) / glm::length(objYVec);
    float objProj2 = glm::length(objYVec);

    float objProj1X = glm::abs(glm::dot(targetXVec, objXVec)) / glm::length(targetXVec);
    float objProj1Y = glm::abs(glm::dot(targetXVec, objYVec)) / glm::length(targetXVec);
    float targetProj3 = glm::length(targetXVec);

    float objProj2X = glm::abs(glm::dot(targetYVec, objXVec)) / glm::length(targetYVec);
    float objProj2Y = glm::abs(glm::dot(targetYVec, objYVec)) / glm::length(targetYVec);
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
