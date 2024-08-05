#include "pch.h"
#include "MyRuby.h"
using namespace MyProject;

MyRuby::MyRuby(MySceneManager& _sceneManager) :
	mSceneManager(_sceneManager)
{
	vec2 collisionArea = { 6.f, 7.f };
	mTransform.SetScale({ 11.f, 9.f });
	mSprite.SetSpriteKey(L"ruby.sprite");
	mSprite.SetLoop(true);
	mSprite.SetChangeTime(0.05f);
	mCollision.AddCollisionArea(collisionArea);
	SetObjectCode(ObjectCode::RUBY);
}

void MyRuby::OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj)
{
	ObjectCode targetObjCode = _targetObj.GetObjectCode();

	switch (targetObjCode)
	{
	case ObjectCode::PLAYER:
		mIsGameClear = true;
		SetColor({ 0.f, 0.f, 0.f, 0.f });
		GameClear();
	}
}

void MyRuby::GameClear()
{
	mSceneManager.SetCurrentScene(L"STAGE");
}

void MyRuby::Update(const float _deltaTime)
{
	mSprite.Update(_deltaTime);
	mTransform.AddLocation({ 0.f, 0.02f * glm::cos(mAngleForMove) });
	mAngleForMove += _deltaTime;
}

void MyRuby::Render()
{
	if(!mIsGameClear)
		mSprite.Render(*this);
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
