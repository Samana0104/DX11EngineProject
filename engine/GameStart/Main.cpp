/*
author : 변한빛
description : 코드 메인 엔트리 포인트

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Core.h"
#include "SceneLobby.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
#ifdef DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // 메모리 누수 확인
#endif

    HBSoft::Core::Create(hInstance, {1280, 720});
    auto lobbyScene = std::make_unique<HBSoft::SceneLobby>();
    HENGINE->m_sceneMgr.Add(L"Lobby", std::move(lobbyScene));
    HENGINE->m_sceneMgr.SetCurrentScene(L"Lobby");
    HENGINE->Run();

#ifdef DEBUG
    _CrtCheckMemory();  // 메모리 누수 확인용
#endif                  // DEBUG
    HBSoft::Core::Delete();
    return 0;
}