#include "pch.h"
#include "MoveComponent.h"
using namespace MyProject;

MoveComponent::MoveComponent(float _speed, float _acceleration, vec2 _dir) :
    mSpeed(_speed),
    mAcceleration(_acceleration),
    mDirection(_dir)
{
}

void MoveComponent::SetSpeed(const float _speed)
{
    mSpeed = _speed;
}

void MoveComponent::SetAcceleration(const float _acceleration)
{
    mAcceleration = _acceleration;
}

void MoveComponent::SetDirection(const vec2 _direction)
{
    mDirection = _direction;
}

float MoveComponent::GetSpeed() const
{
    return mSpeed;
}

float MoveComponent::GetAcceleration() const
{
    return mAcceleration;
}

vec2 MoveComponent::GetDirection() const
{
    return mDirection;
}

void MoveComponent::Update(float _deltaTime)
{
    mSpeed += mAcceleration * _deltaTime;
    mOffset = mSpeed * _deltaTime * mDirection;
}
