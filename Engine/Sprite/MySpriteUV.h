#pragma once
#include "MySprite.h"

namespace MyProject
{
	class MySpriteUV : public MySprite
	{
		std::vector<RECT_F>		 mUVRects;
		TEXTURE_KEY				 mSpriteTexKey;
	};
}

