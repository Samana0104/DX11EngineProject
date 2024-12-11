/*
author : Á¤Âùºó, º¯ÇÑºû
description : °ÔÀÓ Å¸ÀÌÆ² ¾À ¼Ò½º ÆÄÀÏ

version: 1.0.0
date: 2024-11-30
*/

#include "SceneLobby.h"

using namespace HBSoft;

SceneLobby::SceneLobby() {}

void SceneLobby::Update(float deltaTime)
{
    ImGui::Checkbox("wireframe : ", &isWire);

    m_title.Update(deltaTime);

    if (HINPUT->IsKeyDown(VK_MBUTTON))
    {
        Core::engine->m_sceneMgr.SetCurrentScene(L"Game");
    }

    m_lobbyBtn.Update(deltaTime);
}

void SceneLobby::Render()
{
    if (isWire)
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsWireState.Get());
    else
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsState.Get());

    m_title.Render();
    m_lobbyBtn.Render();
}

void SceneLobby::Release() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
