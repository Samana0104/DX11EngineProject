/*
author : 변한빛
description : 게임 내부의 버튼을 정의하기 위한 헤더 파일

version: 1.0.0
date: 2024-12-03
*/

#pragma once

#include "Button.h"

namespace HBSoft
{
    class GameButton
    {
    private:
        Button m_resumeBtn;
        Button m_resetBtn;
        Button m_optionBtn;
        Button m_quitBtn;

        bool m_isRender;

    private:
        void SetResumeBtn();
        void SetResetBtn();
        void SetOptionBtn();
        void SetQuitBtn();

    public:
        GameButton();

        virtual void Init();
        virtual void Release();
        virtual void Update(const float deltaTime);
        virtual void Render();
    };
}  // namespace HBSoft
