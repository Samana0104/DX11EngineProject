/*
author : º¯ÇÑºû, ÀÌÁöÇõ
description : °ÔÀÓ Å¸ÀÌÆ² ¾À ¼Ò½º ÆÄÀÏ
              v1.0.1 : BGM Ãß°¡ (ÀÌÁöÇõ)

version: 1.0.1
date: 2024-11-30
*/
#include "pch.h"
#include "SceneLobby.h"

using namespace HBSoft;

SceneLobby::SceneLobby()
{
    m_lobbyBGM = HASSET->m_sounds[L"lobbyBGM.mp3"];
}

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

void SceneLobby::Start()
{
    m_lobbyBGM->Play();
}

void SceneLobby::End()
{
    m_lobbyBGM->Stop();
}
