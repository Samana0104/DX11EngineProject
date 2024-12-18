/*
author : 변한빛
description : 코드 메인 엔트리 포인트

version: 1.0.5
date: 2024-12-11
*/

#include "pch.h"

#include "SceneGame.h"
#include "SceneLobby.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // #ifdef DEBUG
    //     _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // 메모리 누수 확인
    // #endif

    HBSoft::Core::Create(hInstance, {1280, 720});

    /*
        Scene begin
        씬 등록은 이 이후로 작성할 것
    */

    auto gameScene  = std::make_shared<HBSoft::SceneGame>();
    auto lobbyScene = std::make_shared<HBSoft::SceneLobby>();

    HSCENE.Add(L"Game", gameScene);
    HSCENE.Add(L"Lobby", lobbyScene);
    HSCENE.SetCurrentScene(L"Lobby");
    HENGINE->Run();


    /*
        Scene end
        여기 안에 작성할 것
    */


    // #ifdef DEBUG
    //     _CrtCheckMemory();  // 메모리 누수 확인용
    // #endif                  // DEBUG
    HBSoft::Core::Delete();
    return 0;
}