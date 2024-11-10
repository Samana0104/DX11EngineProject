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
    // #ifdef DEBUG
    //     _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // �޸� ���� Ȯ��
    // #endif

    HBSoft::Core::Create(hInstance, {1280, 720});

    /*
		Scene begin
		�� ����� �� ���ķ� �ۼ��� ��
    */
    auto lobbyScene = std::make_shared<HBSoft::SceneLobby>();
    HENGINE->m_sceneMgr.Add(L"Lobby", lobbyScene);
    HENGINE->m_sceneMgr.SetCurrentScene(L"Lobby");
    HENGINE->Run();
	/*
		Scene end
		���� �ȿ� �ۼ��� ��
    */


    // #ifdef DEBUG
    //     _CrtCheckMemory();  // �޸� ���� Ȯ�ο�
    // #endif                  // DEBUG
    HBSoft::Core::Delete();
    return 0;
}