/*
author : 변한빛
description : 씬 전체를 관리하기 위해 만든 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "SceneMgr.h"
using namespace HBSoft;

void SceneMgr::SetCurrentScene(SCENE_KEY key)
{
    auto scene = this->Get(key);
    if (!m_currentScene)  // nullptr 처리
        m_currentScene = scene;

    m_queueForWaiting.push(scene);
}

void SceneMgr::Update(const float deltaTime)
{
    // 이거 없으면 Render에서 누가 신을 삭제하거나 바꿔버리면 다 끝나기도 전에 바뀜
    if (!m_queueForWaiting.empty())
    {
        m_currentScene->End();  // 신 끝나면 호출되는 함수
        m_currentScene = m_queueForWaiting.front();
        m_currentScene->Start();  // 신 시작하면 호출되는 함수
        m_queueForWaiting.pop();
    }
    m_currentScene->Update(deltaTime);
}

void SceneMgr::Render()
{
    m_currentScene->Render();
}

void SceneMgr::Release()
{
    auto& scenes = GetAll();

    for (auto& scene : scenes)
        scene.second->Release();
    // 전체 신 Release 호출 후 제거

    Clear();
}
