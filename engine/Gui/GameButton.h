/*
author : ���Ѻ�, ������
description : ���� ������ ��ư�� �����ϱ� ���� ��� ����
              v1.0.1: ���� �߰� (������)

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
