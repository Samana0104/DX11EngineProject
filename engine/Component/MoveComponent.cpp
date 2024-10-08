#include "pch.h"
#include "MoveComponent.h"
using namespace HBSoft;

MoveComponent::MoveComponent(Transform2D& transform)
    : m_transform(transform)
{}

void MoveComponent::SetSpeedX(const float speedX)
{
    m_velocity.x = speedX;
}

void MoveComponent::SetSpeedY(const float speedY)
{
    m_velocity.y = speedY;
}

void MoveComponent::SetAccelX(const float acclerationX)
{
    m_acceleration.x = acclerationX;
}

void MoveComponent::SetAccelY(const float acclerationY)
{
    m_acceleration.y = acclerationY;
}

const vec2& MoveComponent::GetOffset() const
{
    return m_offset;
}

void MoveComponent::AddSpeedX(const float speed)
{
    m_velocity.x += speed;
}

void MoveComponent::AddSpeedY(const float speed)
{
    m_velocity.y += speed;
}

void MoveComponent::AddAccelX(const float acceleration)
{
    m_acceleration.x += acceleration;
}

void MoveComponent::AddAccelY(const float acceleration)
{
    m_acceleration.y += acceleration;
}

void MoveComponent::Break(const vec2 accleration)
{
    if (m_velocity.x <= TOLERANCE && m_velocity.y <= TOLERANCE)
        return;

    if (m_velocity.x > 0.f)
    {
        m_isXposBreaking = true;
    }
    else if (m_velocity.x < 0.f)
    {
        m_isXposBreaking = false;
    }
}

void MoveComponent::Stop()
{
    m_velocity     = {0.f, 0.f};
    m_acceleration = {0.f, 0.f};
}

vec2 MoveComponent::GetVelocity() const
{
    return m_velocity;
}

vec2 MoveComponent::GetAccel() const
{
    return m_acceleration;
}

void MoveComponent::Update(float _deltaTime)
{
    m_velocity += m_acceleration * _deltaTime;
    m_offset = m_velocity * _deltaTime;
    m_transform->AddLocation(m_offset);
}
