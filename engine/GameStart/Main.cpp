/*
author : ���Ѻ�
description : �ڵ� ���� ��Ʈ�� ����Ʈ

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Core.h"
#include "SceneLobby.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
#ifdef DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // �޸� ���� Ȯ��
#endif

    HBSoft::Core engine(hInstance, 1280, 960);

    auto lobbyScene = std::make_unique<HBSoft::SceneLobby>();
    engine.m_sceneManager.Add(L"Lobby", std::move(lobbyScene));
    engine.m_sceneManager.SetCurrentScene(L"Lobby");
    engine.Run();

#ifdef DEBUG
    _CrtCheckMemory();  // �޸� ���� Ȯ�ο�
#endif                  // DEBUG
    return 0;
}