#pragma once
#include "MyCoreAPI.h"
#include "MyObject.h"

namespace MyProject
{
	class SpriteComponent
	{
	private:
		SPRITE_KEY	mSpriteKey;

		float	mTimer			= 0.f;
		float	mChangeTime		= 1.f;

		size_t  mAnimationCount	= 0;
		size_t	mAnimationIdx	= 0;
		
		bool	mIsLoop			= true;

		MyResourceManager& mManager = MyResourceManager::GetInstance();

	public:
		void ResetAnimation();

		void SetLoop(const bool _loop);
		void SetAnimationIdx(const size_t _idx);
		void SetChangeTime(const float _time);
		void SetSpriteKey(const SPRITE_KEY _spriteKey);
		
		void Update(const float _deltaTime);
		void Render(MyObject& _obj);
	};
}

