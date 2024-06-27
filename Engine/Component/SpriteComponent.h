#pragma once
#include "MyCoreAPI.h"
#include "MyObject.h"

namespace MyProject
{
	class SpriteComponent
	{
	private:
		MyObject& mObj;

		int		mAnimIndex = 0;
		float	mPlayTimer = 0.0f;
		float	mAnimationTimer = 0.0f;
		float	mChangeTime = 0.0f;
		float   mTexCounter = 1.0f;

	public:
		SpriteComponent(MyObject& _obj);

		void Render(const mat3& _viewMat);
	};
}

