#pragma once

#include "pch.h"

namespace HBSoft
{
    class AnimationClip
    {
    private:
        std::string m_aniName;
        int         m_startFrame;
        int         m_lastFrame;

    public:
        std::vector<std::vector<mat4>> m_aniMat;

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
