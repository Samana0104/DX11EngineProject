#include "pch.h"
#include "SpriteComponent.h"
using namespace HBSoft;

void SpriteComponent::ResetAnimation()
{
    SetAnimationIdx(0);
}

void SpriteComponent::SetLoop(const bool loop)
{
    m_isLoop = loop;
}

void SpriteComponent::SetAnimationIdx(const size_t idx)
{
    m_animationIdx = idx;
}

void SpriteComponent::SetSpriteKey(const SPRITE_KEY spriteKey)
{
    m_spriteKey      = spriteKey;
    m_animationCount = m_manager.m_sprite[spriteKey]->GetSize();
}

void SpriteComponent::SetChangeTime(const float time)
{
    m_changeTime = time;
}

void SpriteComponent::Update(const float deltaTime)
{
    if (m_animationCount == 0)
        return;

    m_timer += deltaTime;

    if (m_timer >= m_changeTime)
    {
        m_timer -= m_changeTime;
        m_animationIdx++;

        if (m_isLoop)
        {
            m_animationIdx %= m_animationCount;
        }
        else
        {
            m_animationIdx = min(m_animationIdx, m_animationCount - 1);
        }
    }
}

void SpriteComponent::Render(Object2D& mObj)
{
    m_manager.m_sprite[m_spriteKey]->Render(mObj, m_animationIdx);
}
