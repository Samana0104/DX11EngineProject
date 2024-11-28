#pragma once

#include "pch.h"

namespace HBSoft
{
    class AnimationClip
    {
    private:
        std::string m_aniName;
        UINT        m_startFrame;
        UINT        m_lastFrame;

        std::vector<std::vector<mat4>> m_aniMat;

    public:
        AnimationClip();
        ~AnimationClip() = default;

        std::vector<mat4>& GetAnimationMatrix(float frame);

        void SetStartFrame(UINT start);
        void SetLastFrame(UINT last);

        const UINT GetStartFrame() const;
        const UINT GetLastFrame() const;
    };

}  // namespace HBSoft
