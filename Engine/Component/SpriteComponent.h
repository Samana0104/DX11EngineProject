#pragma once
#include "MyCoreAPI.h"
#include "MyObject.h"

namespace MyProject
{
	class SpriteComponent
	{
	private:
		MyObject&	mObj;
		SPRITE_KEY	mSpriteKey;

		float	mTimer;
		float	mChangeTime;

		size_t  mAnimationCount;
		size_t	mAnimationIdx;
		
		bool    mIsLoop;

		MyResourceManager& mManager = MyResourceManager::GetInstance();

	public:
		SpriteComponent(MyObject& _obj);
		
		void ResetAnimation();

		void SetLoop(const bool _loop);
		void SetAnimationIdx(const size_t _idx);
		void SetChangeTime(const float _time);
		void SetSpriteKey(const SPRITE_KEY _spriteKey);

		void Update(const float _deltaTime);
		void Render();
	};
}

