/*
author : ���Ѻ�
description : ���� ������ ��ư�� �����ϱ� ���� ��� ����

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
