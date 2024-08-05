#include "pch.h"
#include "MyDoor.h"
using namespace MyProject;

MyDoor::MyDoor()
{
	mTransform.SetScale({ 8.5f, 20.f });
	mLock.SetSpriteKey(L"lock.sprite");
	mLock.SetLoop(true);
	mLock.SetChangeTime(5.f);
	mUnLock.SetSpriteKey(L"unlock.sprite");
	mUnLock.SetLoop(false);
	mUnLock.SetChangeTime(0.05f);
	mCollision.ResizeCollisionArea();
	SetObjectCode(ObjectCode::DOOR);
}

void MyDoor::OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj)
{
	ObjectCode targetObjCode = _targetObj.GetObjectCode();

	switch (targetObjCode)
	{
	case ObjectCode::KEY:
		mIsLock = false;
		mCollision.SetCollisionable(false);
		mManager.mSound[L"unlock.wav"]->Play();
	}

}

void MyDoor::Update(const float _deltaTime)
{
	if (mIsLock)
		mLock.Update(_deltaTime);
	else
		mUnLock.Update(_deltaTime);
}

void MyDoor::Render()
{	
	if (mIsLock)
		mLock.Render(*this);
	else
		mUnLock.Render(*this);
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
