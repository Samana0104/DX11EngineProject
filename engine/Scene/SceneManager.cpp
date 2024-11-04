/*
author : ���Ѻ�
description : �� ��ü�� �����ϱ� ���� ���� �ҽ� ����

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "SceneManager.h"
using namespace HBSoft;

void SceneManager::SetCurrentScene(SCENE_KEY key)
{
    auto& scene = this->Get(key);
    if (!m_currentScene)  // nullptr ó��
        m_currentScene = &scene;

    m_queueForWaiting.push(&scene);
}

void SceneManager::Update(const float deltaTime)
{
    // �̰� ������ Render���� ���� ���� �����ϰų� �ٲ������ �� �����⵵ ���� �ٲ�
    if (!m_queueForWaiting.empty())
    {
        (*m_currentScene)->End();  // �� ������ ȣ��Ǵ� �Լ�
        m_currentScene = m_queueForWaiting.front();
        (*m_currentScene)->Start();  // �� �����ϸ� ȣ��Ǵ� �Լ�
        m_queueForWaiting.pop();
    }
    (*m_currentScene)->Update(deltaTime);
}

void SceneManager::Render()
{
    (*m_currentScene)->Render();
}

void SceneManager::Release()
{
    auto& scenes = GetAll();

    for (auto& scene : scenes)
        scene.second->Release();
    // ��ü �� Release ȣ�� �� ����

    Clear();
}
