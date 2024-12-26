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
    HBSoft::Core::Create(hInstance, {1280, 720});
    HBSoft::Core::AddScene<HBSoft::SceneGame>(L"Game");
    HBSoft::Core::AddScene<HBSoft::SceneLobby>(L"Lobby");
    HBSoft::Core::Start(L"Lobby");
    HBSoft::Core::Delete();
    return 0;
}