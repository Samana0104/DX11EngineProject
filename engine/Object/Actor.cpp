#include "pch.h"
#include "Actor.h"
using namespace HBSoft;

Actor::Actor()
    : mCollision(*this), mMove(m_transform)
{
    mCollision.RegisterCollisionEvent(std::bind(&Actor::OnCollision,
                                                this,
                                                std::placeholders::_1,
                                                std::placeholders::_2,
                                                std::placeholders::_3));
}

void Actor::SetViewedCamera(Camera* _camera)
{
    mCamera = _camera;
}

CollisionComponent& Actor::GetCollisionComponent()
{
    return mCollision;
}

MoveComponent& Actor::GetMoveComponent()
{
    return mMove;
}

void Actor::Update(const float _deltaTime)
{
    mMove.Update(_deltaTime);
}

void Actor::Render()
{
    if (mCamera == nullptr)
    {
        Object2D::Render();
    }
    else
    {
        m_manager.m_shader[m_shaderKey]->SetUpConfiguration();
        m_manager.m_texture[m_textureKey]->Render();
        m_manager.m_mesh[m_meshKey]->Draw(mCamera->GetViewMat() * m_transform.GetModelMat(), m_color);
    }
}

// void Actor::OnCollision(RECT_F& _self, RECT_F& _target, Actor& _targetObj)
//{
//	// 플레이어, 타겟 둘중 하나라도 콜리젼 불가능하면 패스
//	if (!mCollision.IsCollisionable() || !_targetObj.mCollision.IsCollisionable())
//		return;
//
//	vec2 currentSpeed = mMove.GetSpeed();
//
//	if (currentSpeed.x > 0.f)
//	{
//
//	}
// }
