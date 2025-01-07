/*
author : ���Ѻ�, ������
description : ���� ������ ��ư�� �����ϱ� ���� �ҽ�����
              v1.0.1: ���� �߰� (������)

version: 1.0.1
date: 2024-12-03
*/

#include "pch.h"
#include "GameButton.h"
using namespace HBSoft;

GameButton::GameButton()
{
    m_popupSound = HASSET->m_sounds[L"uiPopup.mp3"];

    m_isRender = false;
    SetResumeBtn();
    SetResetBtn();
    SetOptionBtn();
    SetQuitBtn();
}

void GameButton::SetResumeBtn()
{
    HPoint windowSize = HWINDOW->GetWindowSize();

    m_resumeBtn.SetArea({windowSize.x * 0.5f - 130.f,
                         windowSize.y * 0.5f - 200.f,
                         windowSize.x * 0.5f + 150.f,
                         windowSize.y * 0.5f - 100.f});
    m_resumeBtn.SetText(L"�簳", {1.f, 1.f, 1.f, 1.f});
    m_resumeBtn.SetImage(L"�簳.png");
    m_resumeBtn.SetOnClickCallback([this](void) { m_isRender = false; });
}

void GameButton::SetResetBtn()
{
    HPoint windowSize = HWINDOW->GetWindowSize();

    m_resetBtn.SetArea({windowSize.x * 0.5f - 150.f,
                        windowSize.y * 0.5f - 80.f,
                        windowSize.x * 0.5f + 130.f,
                        windowSize.y * 0.5f + 20.f});
    m_resetBtn.SetText(L"����", {1.f, 1.f, 1.f, 1.f});
    m_resetBtn.SetImage(L"����.png");
    m_resetBtn.SetOnClickCallback([this](void) {});
}

void GameButton::SetOptionBtn()
{
    HPoint windowSize = HWINDOW->GetWindowSize();

    m_optionBtn.SetArea({windowSize.x * 0.5f - 130.f,
                         windowSize.y * 0.5f + 40.f,
                         windowSize.x * 0.5f + 150.f,
                         windowSize.y * 0.5f + 140.f});
    m_optionBtn.SetText(L"�ɼ�", {0.f, 0.f, 0.f, 1.f});
    m_optionBtn.SetImage(L"�ɼ�.png");
    m_optionBtn.SetOnClickCallback([this](void) {});
}

void GameButton::SetQuitBtn()
{
    HPoint windowSize = HWINDOW->GetWindowSize();

    m_quitBtn.SetArea({windowSize.x * 0.5f - 150.f,
                       windowSize.y * 0.5f + 160.f,
                       windowSize.x * 0.5f + 130.f,
                       windowSize.y * 0.5f + 260.f});
    m_quitBtn.SetText(L"����", {1.f, 1.f, 1.f, 1.f});
    m_quitBtn.SetImage(L"����.png");
    m_quitBtn.SetOnClickCallback(
    [this](void)
    {
        HSCENE.SetCurrentScene(L"Lobby");
        m_isRender = false;
    });
}

void GameButton::Init() {}

void GameButton::Release() {}

void GameButton::Update(const float deltaTime)
{
    if (HINPUT->IsKeyDown(VK_ESCAPE))
    {
        if (!m_popupSound->IsPlaying())
            m_popupSound->Play();

        if (m_isRender)
            m_isRender = false;
        else
            m_isRender = true;
    }

    if (m_isRender)
    {
        m_resumeBtn.Update(deltaTime);
        m_resetBtn.Update(deltaTime);
        m_optionBtn.Update(deltaTime);
        m_quitBtn.Update(deltaTime);
    }
}

void GameButton::Render()
{
    if (m_isRender)
    {
        m_resumeBtn.Render();
        m_resetBtn.Render();
        m_optionBtn.Render();
        m_quitBtn.Render();
    }
}
