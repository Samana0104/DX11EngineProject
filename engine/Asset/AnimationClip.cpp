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

    vec3 translation1, translation2, interpolatedT;
    vec3 scale1, scale2, interpolatedS;
    vec3 dummy1;
    vec4 dummy2;

    quat rotation1, rotation2, interpolatedR;

    std::vector<mat4> interpolatedMat;

    int infimumFrame  = static_cast<int>(glm::floor(frame));
    int supremumFrame = static_cast<int>(glm::ceil(frame));

    if (supremumFrame == m_lastFrame)
        supremumFrame = m_startFrame;

    interpolatedMat.resize(m_aniMat.size());

    for (int i = 0; i < m_aniMat.size(); i++)
    {
        glm::decompose(m_aniMat[i][infimumFrame], scale1, rotation1, translation1, dummy1, dummy2);
        glm::decompose(m_aniMat[i][supremumFrame], scale2, rotation2, translation2, dummy1, dummy2);

        interpolatedT = glm::lerp(translation1, translation2, frame - infimumFrame);
        interpolatedR = glm::slerp(rotation1, rotation2, frame - infimumFrame);
        interpolatedS = glm::lerp(scale1, scale2, frame - infimumFrame);

        interpolatedMat[i]     = glm::toMat4(interpolatedR);
        interpolatedMat[i][0] *= interpolatedS.x;
        interpolatedMat[i][1] *= interpolatedS.y;
        interpolatedMat[i][2] *= interpolatedS.z;
        interpolatedMat[i][3]  = vec4(interpolatedT, 1.f);
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
