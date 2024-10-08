#include "pch.h"
#include "SceneManager.h"
#include "SceneLobby.h"
using namespace HBSoft;

void SceneManager::AddScene(std::shared_ptr<Scene> _scene, SCENE_KEY _key)
{
    _scene->Init();
    AddResource(_key, _scene);
}

void SceneManager::SetCurrentScene(SCENE_KEY _key)
{
    mQueueForWaiting.push(GetResource(_key));
}

void SceneManager::SetCurrentScene(std::shared_ptr<Scene> _scene)
{
    mQueueForWaiting.push(_scene);
}

void SceneManager::Init()
{
    AddScene(std::make_shared<SceneLobby>(*this), L"LOBBY");

    mCurrentScene = GetResource(L"LOBBY");
    mCurrentScene->Start();
}

void SceneManager::Update(const float _deltaTime)
{
    // 이거 없으면 현재 실행되고 있는 다 끝나기도 전에 바뀜
    if (!mQueueForWaiting.empty())
    {
        mCurrentScene->End();
        mCurrentScene = mQueueForWaiting.front();
        mCurrentScene->Start();
        mQueueForWaiting.pop();
    }

    mCurrentScene->Update(_deltaTime);
}

void SceneManager::Render()
{
    mCurrentScene->Render();
}

void SceneManager::Release()
{
    auto& scenes = GetAllResources();

    for (auto& scene : scenes)
        scene.second->Release();

    ClearResources();
}
