#include "pch.h"
#include "CollisionComponent.h"
using namespace MyProject;

CollisionComponent::CollisionComponent(MyTransformer2D& _objMat) :
    mObjMat(_objMat)
{
}

bool CollisionComponent::IsAABBCollision(MyTransformer2D& _targetM)
{
    vec2 objScale = mObjMat.GetScale();
    vec2 objLocation = mObjMat.GetLocation();
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

bool CollisionComponent::IsOBBCollision(MyTransformer2D& _targetM)
{ 
    vec2 objScale     = mObjMat.GetScale();
    vec2 objLocation  = mObjMat.GetLocation();
    float objAngle    = mObjMat.GetAngle();
    vec2 targetScale  = _targetM.GetScale();
    vec2 targetLocation = _targetM.GetLocation();
    float targetAngle = _targetM.GetAngle();

    vec2 objXVec = MyTransformer2D::RotateAsAngle({ objScale.x / 2, 0.f }, objAngle);
    vec2 objYVec = MyTransformer2D::RotateAsAngle({ 0.f, objScale.y / 2 }, objAngle);
    vec2 targetXVec = MyTransformer2D::RotateAsAngle({ targetScale.x / 2, 0.f }, targetAngle);
    vec2 targetYVec = MyTransformer2D::RotateAsAngle({ 0.f, targetScale.y / 2 }, targetAngle);
    
    vec2 distance = targetLocation - objLocation;

    float distance1 = glm::dot(objXVec, distance) / glm::length(objXVec);
    float distance2 = glm::dot(objYVec, distance) / glm::length(objYVec);
    float distance3 = glm::dot(targetXVec, distance) / glm::length(targetXVec);
    float distance4 = glm::dot(targetYVec, distance) / glm::length(targetYVec);

    float targetProj1 = glm::dot(objXVec, targetXVec + targetYVec) / glm::length(objXVec);
    float objProj1 = glm::length(objXVec);

    float targetProj2 = glm::dot(objYVec, targetXVec + targetYVec) / glm::length(objYVec);
    float objProj2 = glm::length(objYVec);

    float objProj3 = glm::dot(targetXVec, objXVec + objYVec) / glm::length(targetXVec);
    float targetProj3 = glm::length(targetXVec);

    float objProj4 = glm::dot(targetYVec, objXVec + objYVec) / glm::length(targetYVec);
    float targetProj4 = glm::length(targetYVec);

    if (!(targetProj1 + objProj1 < distance1))
        return false;
            
    if (!(targetProj2 + objProj2 < distance2))
        return false;

    if (!(targetProj3 + objProj3 < distance3))
        return false;

    if (!(targetProj4 + objProj4 < distance4))
        return false;

    return true;
}
