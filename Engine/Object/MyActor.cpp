#include "pch.h"
#include "MyActor.h"
using namespace MyProject;

MyActor::MyActor() :
	mCollision(*this),
	mMove(mTransform)
{
	mCollision.RegisterCollisionEvent(
		std::bind(
			&MyActor::OnCollision,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3
		));
}

void MyActor::SetViewedCamera(MyCamera* _camera)
{
	mCamera = _camera;
}

CollisionComponent& MyActor::GetCollisionComponent()
{
	return mCollision;
}

MoveComponent& MyActor::GetMoveComponent()
{
	return mMove;
}

void MyActor::Update(const float _deltaTime)
{
	mMove.Update(_deltaTime);
}

void MyActor::Render()
{
	if (mCamera == nullptr)
	{
		MyObject::Render();
	}
	else
	{
		mManager.mShader[mShaderKey]->SetUpConfiguration();
		mManager.mTexture[mTextureKey]->Render();
		mManager.mMesh[mMeshKey]->Draw(mCamera->GetViewMat()*mTransform.GetModelMat(), mColor);
	}
}

//void MyActor::OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj)
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
//}
