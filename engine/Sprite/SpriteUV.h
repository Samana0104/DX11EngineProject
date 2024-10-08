#pragma once
#include "Sprite.h"

namespace HBSoft
{
	class SpriteUV : public Sprite
	{
		std::vector<RECT_F>		 mUVRects;
		TEXTURE_KEY				 mSpriteTexKey;
	};
}

