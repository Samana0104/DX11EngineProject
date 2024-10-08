#pragma once
#include "Sprite.h"

namespace HBSoft
{
    class SpriteUV : public Sprite
    {
        std::vector<RECT_F> m_uvRects;
        TEXTURE_KEY         m_spriteTexKey;
    };
}  // namespace HBSoft
