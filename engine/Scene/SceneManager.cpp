#include "pch.h"
#include "SceneManager.h"
#include "SceneLobby.h"
using namespace HBSoft;

void SceneManager::AddScene(std::shared_ptr<Scene> _scene, SCENE_KEY _key)
{
    _scene->Init();
    Add(_key, _scene);
}

void SceneManager::SetCurrentScene(SCENE_KEY _key)
{
    m_queueForWaiting.push(Get(_key));
}

void SceneManager::SetCurrentScene(std::shared_ptr<Scene> _scene)
{
    m_queueForWaiting.push(_scene);
}

void SceneManager::Init()
{
    AddScene(std::make_shared<SceneLobby>(*this), L"LOBBY");

    m_currentScene = Get(L"LOBBY");
    m_currentScene->Start();
}

void SceneManager::Update(const float _deltaTime)
{
    // 이거 없으면 현재 실행되고 있는 다 끝나기도 전에 바뀜
    if (!m_queueForWaiting.empty())
    {
        m_currentScene->End();
        m_currentScene = m_queueForWaiting.front();
        m_currentScene->Start();
        m_queueForWaiting.pop();
    }

    m_currentScene->Update(_deltaTime);
}

void SceneManager::Render()
{
    m_currentScene->Render();
}

void SceneManager::Release()
{
    auto& scenes = GetAllResources();

    for (auto& scene : scenes)
        scene.second->Release();

    Clear();
}
