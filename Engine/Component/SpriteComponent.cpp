#include "pch.h"
#include "SpriteComponent.h"
using namespace MyProject;

SpriteComponent::SpriteComponent(MyObject& _obj) :
	mObj(_obj)
{
	mTimer = 0.f;
	mChangeTime = 1.f;
	mAnimationIdx = 0;
	mAnimationCount = 0;
	mIsLoop = true;
}

void SpriteComponent::ResetAnimation()
{
	mAnimationIdx = 0;
	mTimer = 0.f;
}

void SpriteComponent::SetLoop(const bool _loop)
{
	mIsLoop = _loop;
}

void SpriteComponent::SetAnimationIdx(const size_t _idx)
{
	mAnimationIdx = _idx % mAnimationCount;
}

void SpriteComponent::SetSpriteKey(const SPRITE_KEY _spriteKey)
{
	mSpriteKey = _spriteKey;
	mAnimationCount = mManager.mSprite[_spriteKey]->GetSize();
	ResetAnimation();
}

void SpriteComponent::SetChangeTime(const float _time)
{
	mChangeTime = _time;
}

void SpriteComponent::Update(const float _deltaTime)
{
	mTimer += _deltaTime;

	if (mTimer >= mChangeTime)
	{
		mTimer -= mChangeTime;
		mAnimationIdx++;

		if (mIsLoop)
			mAnimationIdx %= mAnimationCount;
		else
			mAnimationIdx = min(mAnimationIdx, mAnimationCount - 1);
	}
}

void SpriteComponent::Render()
{
	mManager.mSprite[mSpriteKey]->Render(mObj, mAnimationIdx);
}
