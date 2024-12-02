/*
author : 정찬빈, 변한빛
description : 게임 타이틀 씬 소스 파일

version: 1.0.0
date: 2024-11-30
*/

#include "pch.h"
#include "SceneLobby.h"

using namespace HBSoft;

SceneLobby::SceneLobby()
{
    HPoint windowSize = HWINDOW->GetWindowSize();

    m_button.SetArea({windowSize.x * 0.5f - 50.f,
                      windowSize.y * 0.5f - 30.f,
                      windowSize.x * 0.5f + 50.f,
                      windowSize.y * 0.5f + 30.f});
    m_button.SetText(L"시작", {0.f, 0.f, 0.f, 1.f});
    m_button.SetImage(L"투명.png");
    m_button.SetOnClickCallback([](void) { HSCENE.SetCurrentScene(L"Game"); });
}

void SceneLobby::Update(float deltaTime)
{
    ImGui::Checkbox("wireframe : ", &isWire);

    m_title.Update(deltaTime);

    if (HINPUT->IsKeyDown(VK_MBUTTON))
    {
        Core::engine->m_sceneMgr.SetCurrentScene(L"Game");
    }

    m_button.Update(deltaTime);
}

void SceneLobby::Render()
{
    if (isWire)
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsWireState.Get());
    else
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsState.Get());

    m_title.Render();
    m_button.Render();
}

void SceneLobby::Release() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
