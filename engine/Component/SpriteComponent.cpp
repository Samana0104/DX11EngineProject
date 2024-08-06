#include "pch.h"
#include "SpriteComponent.h"
using namespace MyProject;

void SpriteComponent::ResetAnimation()
{
	SetAnimationIdx(0);
}

void SpriteComponent::SetLoop(const bool _loop)
{
	mIsLoop = _loop;
}

void SpriteComponent::SetAnimationIdx(const size_t _idx)
{
	mAnimationIdx = _idx;
}

void SpriteComponent::SetSpriteKey(const SPRITE_KEY _spriteKey)
{
	mSpriteKey = _spriteKey;
	mAnimationCount = mManager.mSprite[_spriteKey]->GetSize();
}

void SpriteComponent::SetChangeTime(const float _time)
{
	mChangeTime = _time;
}

void SpriteComponent::Update(const float _deltaTime)
{
	if (mAnimationCount == 0)
		return;

	mTimer += _deltaTime;

	if (mTimer >= mChangeTime)
	{
		mTimer -= mChangeTime;
		mAnimationIdx++;

		if (mIsLoop)
		{
			mAnimationIdx %= mAnimationCount;
		}
		else
		{
			mAnimationIdx = min(mAnimationIdx, mAnimationCount - 1);
		}
	}
}

void SpriteComponent::Render(MyObject& mObj)
{
	mManager.mSprite[mSpriteKey]->Render(mObj, mAnimationIdx);
}
