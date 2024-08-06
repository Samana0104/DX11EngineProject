#include "pch.h"
#include "MoveComponent.h"
using namespace MyProject;

MoveComponent::MoveComponent(MyTransformer2D & _transform) :
    mTransform(_transform)
{
}

void MoveComponent::SetSpeedX(const float _speedX)
{
    mVelocity.x = _speedX;
}

void MoveComponent::SetSpeedY(const float _speedY)
{
    mVelocity.y = _speedY;
}

void MoveComponent::SetAccelX(const float _acclerationX)
{
    mAcceleration.x = _acclerationX;
}

void MoveComponent::SetAccelY(const float _acclerationY)
{
    mAcceleration.y = _acclerationY;
}

const vec2& MoveComponent::GetOffset() const
{
    return mOffset;
}

void MoveComponent::AddSpeedX(const float _speed)
{
    mVelocity.x += _speed;
}

void MoveComponent::AddSpeedY(const float _speed)
{
    mVelocity.y += _speed;
}

void MoveComponent::AddAccelX(const float _acceleration)
{
    mAcceleration.x += _acceleration;
}

void MoveComponent::AddAccelY(const float _acceleration)
{
    mAcceleration.y += _acceleration;
}

void MoveComponent::Break(const vec2 _accleration)
{
    if (mVelocity.x <= TOLERANCE && mVelocity.y <= TOLERANCE)
        return;

    if (mVelocity.x > 0.f)
    {
		mIsXposBreaking = true;
    }
    else if(mVelocity.x < 0.f)
    {
		mIsXposBreaking = false;
    }

}

void MoveComponent::Stop()
{
    mVelocity = { 0.f, 0.f };
    mAcceleration = { 0.f, 0.f };
}

vec2 MoveComponent::GetVelocity() const
{
    return mVelocity;
}

vec2 MoveComponent::GetAccel() const
{
    return mAcceleration;
}

void MoveComponent::Update(float _deltaTime)
{
    mVelocity += mAcceleration * _deltaTime;
    mOffset = mVelocity * _deltaTime;
    mTransform->AddLocation(mOffset);
}
