/*
author : 변한빛
description : 애니메이션 관련 정보를 관리하는 클래스의 소스 파일

version: 1.0.0
date: 2024-11-29
*/

#include "pch.h"
#include "AnimationClip.h"
using namespace HBSoft;

AnimationClip::AnimationClip()
    : m_startFrame(0), m_lastFrame(0)
{}

std::vector<mat4> AnimationClip::GetAnimationMatrix(float frame)
{
    if (frame < 0 || frame >= m_lastFrame)
        assert(false);

    std::vector<mat4> interpolatedMat;
    KeyFrame          key1, key2, interpolatedKey;

    int infimumFrame  = static_cast<int>(glm::floor(frame));
    int supremumFrame = static_cast<int>(glm::ceil(frame));

    if (supremumFrame == m_lastFrame)
        supremumFrame = m_startFrame;

    interpolatedMat.resize(m_keyFrame.size());

    for (int i = 0; i < m_keyFrame.size(); i++)
    {
        key1 = m_keyFrame[i][infimumFrame];
        key2 = m_keyFrame[i][supremumFrame];

        interpolatedKey.pos   = glm::lerp(key1.pos, key2.pos, frame - infimumFrame);
        interpolatedKey.rot   = glm::slerp(key1.rot, key2.rot, frame - infimumFrame);
        interpolatedKey.scale = glm::lerp(key1.scale, key2.scale, frame - infimumFrame);

        interpolatedMat[i]     = glm::toMat4(interpolatedKey.rot);
        interpolatedMat[i][0] *= interpolatedKey.scale.x;
        interpolatedMat[i][1] *= interpolatedKey.scale.y;
        interpolatedMat[i][2] *= interpolatedKey.scale.z;
        interpolatedMat[i][3]  = vec4(interpolatedKey.pos, 1.f);
    }

    return std::move(interpolatedMat);
}

void AnimationClip::SetStartFrame(int start)
{
    m_startFrame = start;
}

void AnimationClip::SetLastFrame(int last)
{
    m_lastFrame = last;
}

void AnimationClip::SetAnimationName(const stringV aniName)
{
    m_aniName = aniName;
}

const int AnimationClip::GetStartFrame() const
{
    return m_startFrame;
}

const int AnimationClip::GetLastFrame() const
{
    return m_lastFrame;
}
