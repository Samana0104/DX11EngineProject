/*
author : 변한빛
description : 애니메이션 관련 정보를 관리하는 클래스의 헤더 파일

version: 1.0.0
date: 2024-11-29
*/

#pragma once

#include "pch.h"

namespace HBSoft
{
    struct KeyFrame
    {
        vec3 pos;
        quat rot;
        vec3 scale;
    };

    class AnimationClip
    {
    public:
        std::string m_aniName;
        int         m_startFrame;
        int         m_lastFrame;

        std::vector<std::vector<KeyFrame>> m_keyFrame;

    public:
        AnimationClip();
        ~AnimationClip() = default;

        std::vector<mat4> GetAnimationMatrix(float frame);

        void SetStartFrame(int start);
        void SetLastFrame(int last);
        void SetAnimationName(const stringV aniName);

        const int GetStartFrame() const;
        const int GetLastFrame() const;
    };

}  // namespace HBSoft
