/*
author : ���Ѻ�
description : �ִϸ��̼� ���� ������ �����ϴ� Ŭ������ ��� ����

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
