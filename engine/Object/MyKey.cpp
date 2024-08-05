#include "pch.h"
#include "MyKey.h"
using namespace MyProject;

MyKey::MyKey(MyObjectManager&  _objManager) :
	mObjManager(_objManager)
{
	RECT_F collisionArea = { -5.5f, 2.7f, 6.f, -2.5f };
	mTransform.SetScale({ 14.f, 10.f });
	mSprite.SetSpriteKey(L"key.sprite");
	mSprite.SetLoop(true);
	mSprite.SetChangeTime(0.15f);
	mMove.SetAccelY(-160.f);
	mCollision.AddCollisionArea(collisionArea);
	SetObjectCode(ObjectCode::KEY);
}

void MyKey::OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj)
{
	vec2 targetLocation = _targetObj->GetLocation();
	vec2 correction = mCollision.GetCorrectionForCollision(
		mMove.GetOffset(), targetLocation, _self, _target);
	vec2 speed = mMove.GetVelocity();

	ObjectCode targetObjCode = _targetObj.GetObjectCode();

	switch (targetObjCode)
	{
	case ObjectCode::DOOR:
		mObjManager.DeleteObject(GetObjectID());
		break;

	case ObjectCode::TILE:
		mTransform.AddLocation(correction);

		if (abs(correction.x) > TOLERANCE)
		{
			mManager.mSound[L"key-hit.wav"]->Play();
			mMove.SetSpeedX(0.f);
			mMove.SetAccelY(-160.f);
		}

		if (correction.y >= TOLERANCE)
		{
			mMove.SetSpeedX(0.f);
			mMove.SetSpeedY(0.f);
		}
		else if (correction.y <= -TOLERANCE)
		{
			mManager.mSound[L"key-hit.wav"]->Play();
			mMove.SetSpeedY(0.f);
			mMove.SetSpeedX(0.f);
		}
		break;

	case ObjectCode::WOOD_BOX:
		if (correction.y >= TOLERANCE)
		{
			mTransform.AddLocation(correction);
			mMove.SetSpeedY(0.f);
			mMove.SetSpeedX(0.f);
		}
		break;
	}
}

void MyKey::Update(const float _deltaTime)
{
	mMove.Update(_deltaTime);
	mSprite.Update(_deltaTime);

}

void MyKey::Render()
{
	mSprite.Render(*this);
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}

