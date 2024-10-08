#pragma once
#include "CoreAPI.h"
#include "Object2D.h"

namespace HBSoft
{
    class SpriteComponent
    {
    private:
        SPRITE_KEY m_spriteKey;

        float m_timer      = 0.f;
        float m_changeTime = 1.f;

        size_t m_animationCount = 0;
        size_t m_animationIdx   = 0;

        bool m_isLoop = true;

        ResourceManager& m_manager = ResourceManager::GetInstance();

    public:
        void ResetAnimation();

        void SetLoop(const bool loop);
        void SetAnimationIdx(const size_t idx);
        void SetChangeTime(const float time);
        void SetSpriteKey(const SPRITE_KEY spriteKey);

        void Update(const float deltaTime);
        void Render(Object2D& obj);
    };
}  // namespace HBSoft
