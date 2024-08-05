#include "pch.h"
#include "MyPlayer.h"
using namespace MyProject;

MyPlayer::MyPlayer()
{
	vec2 scale = { 7.2f, 8.9f };

	InitSprite();
	mTransform.SetScale({ 7.5f, 8.9f });
	mMove.SetAccelY(-160.f);
	mCollision.AddCollisionArea(scale);
	SetObjectCode(ObjectCode::PLAYER);
}

void MyPlayer::OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj)
{
	vec2 targetLocation = _targetObj->GetLocation();
	vec2 correction	= mCollision.GetCorrectionForCollision(
		mMove.GetOffset(), targetLocation, _self, _target);
	vec2 mVelocity = mMove.GetVelocity();

	ObjectCode targetObjCode = _targetObj.GetObjectCode();

	switch (targetObjCode)
	{
	case ObjectCode::TILE:
	case ObjectCode::DOOR:
		if (mObjectOnHand != nullptr)
			(*mObjectOnHand)->AddLocation(correction);

		mTransform.AddLocation(correction);
		if (correction.y > 0.f)
		{
			if (mIsJumping)
				mManager.mSound[L"land.wav"]->Play();

			mIsJumping = false;
			mMove.SetSpeedY(0.f);
		}
		else if (correction.y < 0.f) // ÃµÀå¿¡ ºÎµúÈú ¶§
		{
			mMove.SetSpeedY(0.f);
		}
		
		return;

	case ObjectCode::WOOD_BOX:
		if (correction.y > TOLERANCE)
		{
			if (mIsJumping)
				mManager.mSound[L"land.wav"]->Play();

			mTransform.AddLocation(correction);
			mMove.SetSpeedY(0.f);
			mIsJumping = false;
		}
	}

	// GRAP
	if (mInput.GetCurrentKeyState(0x58) == KeyState::KEY_DOWN && mCanGrap)
	{
		RECT_F intersectRect = mCollision.GetIntersectionRect(_self, _target);
		vec2 targetSpeed = _targetObj.GetMoveComponent().GetVelocity();
		vec2 targetScale = _targetObj->GetScale();
		float width = intersectRect.right - intersectRect.left;
		float height = intersectRect.top - intersectRect.bottom;

		if (width < targetScale.x * 0.5f || height < targetScale.y * 0.5f)
			return;

		if (mObjectOnHand == nullptr && 
			abs(targetSpeed.x) < TOLERANCE && 
			!mIsJumping)
		{
			mManager.mSound[L"grab.wav"]->Play();
			mObjectOnHand = &_targetObj;
			mCanGrap = false;
			_targetObj.GetMoveComponent().Stop();
			_targetObj.GetCollisionComponent().SetCollisionable(false);
		}
	}
}

void MyPlayer::InitSprite()
{

	mSprite[PlayerAction::STAND].SetLoop(false);
	mSprite[PlayerAction::STAND].SetChangeTime(1.f);

	mSprite[PlayerAction::STAND_HEAVY].SetLoop(false);
	mSprite[PlayerAction::STAND_HEAVY].SetChangeTime(1.f);

	mSprite[PlayerAction::WALK].SetLoop(true);
	mSprite[PlayerAction::WALK].SetChangeTime(0.08f);

	mSprite[PlayerAction::WALK_HEAVY].SetLoop(true);
	mSprite[PlayerAction::WALK_HEAVY].SetChangeTime(0.08f);

	mSprite[PlayerAction::JUMP].SetLoop(false);
	mSprite[PlayerAction::JUMP].SetChangeTime(1.f);

	mSprite[PlayerAction::JUMP_HEAVY].SetLoop(false);
	mSprite[PlayerAction::JUMP_HEAVY].SetChangeTime(1.f);

	mSprite[PlayerAction::FALL].SetLoop(false);
	mSprite[PlayerAction::FALL].SetChangeTime(1.f);

	mSprite[PlayerAction::FALL_HEAVY].SetLoop(false);
	mSprite[PlayerAction::FALL_HEAVY].SetChangeTime(1.f);

	SetSpriteForRight();
}

void MyPlayer::SetSpriteForRight()
{
	mSprite[PlayerAction::STAND].SetSpriteKey(L"player-stand-right.sprite");
	mSprite[PlayerAction::STAND_HEAVY].SetSpriteKey(L"player-stand-heavy-right.sprite");
	mSprite[PlayerAction::WALK].SetSpriteKey(L"player-walk-right.sprite");
	mSprite[PlayerAction::WALK_HEAVY].SetSpriteKey(L"player-walk-heavy-right.sprite");
	mSprite[PlayerAction::JUMP].SetSpriteKey(L"player-jump-right.sprite");
	mSprite[PlayerAction::JUMP_HEAVY].SetSpriteKey(L"player-jump-heavy-right.sprite");
	mSprite[PlayerAction::FALL].SetSpriteKey(L"player-fall-right.sprite");
	mSprite[PlayerAction::FALL_HEAVY].SetSpriteKey(L"player-fall-heavy-right.sprite");
}

void MyPlayer::SetSpriteForLeft()
{
	mSprite[PlayerAction::STAND].SetSpriteKey(L"player-stand-left.sprite");
	mSprite[PlayerAction::STAND_HEAVY].SetSpriteKey(L"player-stand-heavy-left.sprite");
	mSprite[PlayerAction::WALK].SetSpriteKey(L"player-walk-left.sprite");
	mSprite[PlayerAction::WALK_HEAVY].SetSpriteKey(L"player-walk-heavy-left.sprite");
	mSprite[PlayerAction::JUMP].SetSpriteKey(L"player-jump-left.sprite");
	mSprite[PlayerAction::JUMP_HEAVY].SetSpriteKey(L"player-jump-heavy-left.sprite");
	mSprite[PlayerAction::FALL].SetSpriteKey(L"player-fall-left.sprite");
	mSprite[PlayerAction::FALL_HEAVY].SetSpriteKey(L"player-fall-heavy-left.sprite");
}

void MyPlayer::Right()
{
	mMove.SetSpeedX(46.f);

	if (!mManager.mSound[L"walk.wav"]->IsPlaying() && !mIsJumping)
		mManager.mSound[L"walk.wav"]->Play();
	SetSpriteForRight();
	mIsLeft = false;
}

void MyPlayer::Left()
{
	mMove.SetSpeedX(-46.f);
	if (!mManager.mSound[L"walk.wav"]->IsPlaying() && !mIsJumping)
		mManager.mSound[L"walk.wav"]->Play();
	SetSpriteForLeft();
	mIsLeft = true;
}

void MyPlayer::Stand()
{
	mMove.SetSpeedX(0.f);
	mCurrentAction = PlayerAction::STAND;
	mSprite[PlayerAction::STAND].ResetAnimation();
}

void MyPlayer::Jump()
{
	if (mIsJumping)
		return;

	mIsJumping = true;
	if (mObjectOnHand == nullptr)
	{
		mManager.mSound[L"jump.wav"]->Play();
		mMove.SetSpeedY(80.f);
	}
	else
	{
		mManager.mSound[L"jump-heavy.wav"]->Play();
		mMove.SetSpeedY(70.f);
	}
}

void MyPlayer::Drop()
{
	if (mObjectOnHand != nullptr && mCanGrap)
	{
		mObjectOnHand->GetCollisionComponent().SetCollisionable(true);
		mCanGrap = false;


		if (mInput.IsKeyPressed(VK_LEFT))
		{
			(*mObjectOnHand)->SetLocation(mTransform.GetLocation());
			mManager.mSound[L"throw.wav"]->Play();

			if(mIsLeft)
				(*mObjectOnHand)->AddLocation({ 1.f, 0.f });
			else
				(*mObjectOnHand)->AddLocation({ -1.f, 0.f });

			mObjectOnHand->GetMoveComponent().SetSpeedX(-130.f);
		}
		else if (mInput.IsKeyPressed(VK_RIGHT))
		{
			mManager.mSound[L"throw.wav"]->Play();
			mObjectOnHand->GetMoveComponent().SetSpeedX(130.f);
		}
		else if (mInput.IsKeyPressed(VK_UP))
		{
			(*mObjectOnHand)->SetLocation(mTransform.GetLocation());

			mManager.mSound[L"throw.wav"]->Play();
			mObjectOnHand->GetMoveComponent().SetAccelY(-160.f);
			mObjectOnHand->GetMoveComponent().SetSpeedY(67.f);
		}
		else if (mInput.IsKeyPressed(VK_DOWN))
		{
			mManager.mSound[L"throw.wav"]->Play();
			mObjectOnHand->GetMoveComponent().SetAccelY(-160.f);
			mObjectOnHand->GetMoveComponent().SetSpeedY(-90.f);
		}
		else
		{
			mManager.mSound[L"drop.wav"]->Play();
			mObjectOnHand->GetMoveComponent().SetAccelY(-160.f);
			mObjectOnHand->GetMoveComponent().SetSpeedY(30.f);
		}
		mObjectOnHand = nullptr;
	}
}

void MyPlayer::UpdatePlayerState()
{
	vec2 mCurrentSpeed = mMove.GetVelocity();

	if (mInput.IsKeyPressed(VK_RIGHT))
		Right();

	if (mInput.IsKeyPressed(VK_LEFT))
		Left();
	
	if (mInput.GetCurrentKeyState(VK_RIGHT) == KeyState::KEY_UP ||
		mInput.GetCurrentKeyState(VK_LEFT) == KeyState::KEY_UP)
		Stand();

	if (mInput.GetCurrentKeyState(0x5A) == KeyState::KEY_DOWN)
		Jump();

	if (mInput.GetCurrentKeyState(0x58) == KeyState::KEY_DOWN)
		Drop();

	if (abs(mCurrentSpeed.x) <= TOLERANCE && abs(mCurrentSpeed.y) <= TOLERANCE)
	{
		if (mObjectOnHand == nullptr)
			mCurrentAction = PlayerAction::STAND;
		else
			mCurrentAction = PlayerAction::STAND_HEAVY;
	}
	else if (mCurrentSpeed.y >= TOLERANCE)
	{
		if (mObjectOnHand == nullptr)
			mCurrentAction = PlayerAction::JUMP;
		else
			mCurrentAction = PlayerAction::JUMP_HEAVY;
	}
	else if (mCurrentSpeed.y <= -TOLERANCE)
	{
		mIsJumping = true;

		if (mObjectOnHand == nullptr)
			mCurrentAction = PlayerAction::FALL;
		else
			mCurrentAction = PlayerAction::FALL_HEAVY;
	}
	else if (abs(mCurrentSpeed.x) >= TOLERANCE)
	{
		if (mObjectOnHand == nullptr)
			mCurrentAction = PlayerAction::WALK;
		else
			mCurrentAction = PlayerAction::WALK_HEAVY;
	}
}

void MyPlayer::Update(const float _deltaTime)
{
	UpdatePlayerState();
	mMove.Update(_deltaTime);
	mSprite[mCurrentAction].Update(_deltaTime);

	if (mObjectOnHand != nullptr)
	{
		vec2 location = mTransform.GetLocation();
		if(mIsLeft)
			(*mObjectOnHand)->SetLocation({ location.x-2.f, location.y+1 });
		else
			(*mObjectOnHand)->SetLocation({ location.x+2.f, location.y+1 });
	}

	if (!mCanGrap)
	{
		mGrapCooltime += _deltaTime;

		if (mGrapCooltime >= 0.1f)
		{
			mGrapCooltime = 0.f;
			mCanGrap = true;
		}
	}
}

void MyPlayer::Render()
{
	mSprite[mCurrentAction].Render(*this);
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
