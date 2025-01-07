/*
author : 변한빛, 이지혁
description : 게임 내부의 버튼을 정의하기 위한 헤더 파일
              v1.0.1: 사운드 추가 (이지혁)

version: 1.0.1
date: 2024-12-03
*/

#pragma once

#include "Button.h"
#include "Sound/HSound.h"

namespace HBSoft
{
    class GameButton
    {
    private:
        Button m_resumeBtn;
        Button m_resetBtn;
        Button m_optionBtn;
        Button m_quitBtn;
        std::shared_ptr<HSound> m_popupSound;

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
