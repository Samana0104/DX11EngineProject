/*
author : 변한빛
description : 게임 타이틀 씬 소스 파일

version: 1.0.0
date: 2024-11-30
*/
#include "pch.h"
#include "SceneLobby.h"

using namespace HBSoft;

SceneLobby::SceneLobby() {}

void SceneLobby::Update(float deltaTime)
{
#ifdef _DEBUG
    ImGui::Checkbox("wireframe : ", &isWire);
#endif

    m_title.Update(deltaTime);

    if (HINPUT->IsKeyDown(VK_MBUTTON))
    {
        Core::engine->m_sceneMgr.SetCurrentScene(L"Game");
    }

    m_lobbyBtn.Update(deltaTime);
}

void SceneLobby::Render()
{
    EasyRender::Begin(MultiRT::MAIN);
    m_title.Render();
    EasyRender::SetWireFrame(isWire);
    EasyRender::End(MultiRT::MAIN);

    EasyRender::Begin(MultiRT::GUI);
    m_lobbyBtn.Render();
    EasyRender::End(MultiRT::GUI);

    if (HINPUT->IsKeyDown(VK_HOME))
    {
        EasyRender::SaveScreenShot(MultiRT::GUI, L"Gui");
        EasyRender::SaveScreenShot(MultiRT::MAIN, L"Test");
    }

    EasyRender::MergeRenderTarget(MultiRT::MAIN, MultiRT::GUI);
}

void SceneLobby::Release() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
