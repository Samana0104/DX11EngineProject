#include "pch.h"
#include "MySceneManager.h"
#include "MySceneLobby.h"
#include "MySceneSetting.h"
#include "MySceneStage.h"
#include "MySceneStage1.h"
#include "MySceneStage2.h"
#include "MySceneStage3.h"
using namespace MyProject;

void MySceneManager::AddScene(std::shared_ptr<MyScene> _scene, SCENE_KEY _key)
{
	_scene->Init();
	AddResource(_key, _scene);
}
void MySceneManager::SetCurrentScene(SCENE_KEY _key)
{
	mQueueForWaiting.push(GetResource(_key));
}

void MySceneManager::SetCurrentScene(std::shared_ptr<MyScene> _scene)
{
	mQueueForWaiting.push(_scene);
}

void MySceneManager::Init()
{
	AddScene(std::make_shared<MySceneLobby>(*this), L"LOBBY");
	AddScene(std::make_shared<MySceneSetting>(*this), L"SETTING");
	AddScene(std::make_shared<MySceneStage>(*this), L"STAGE");
	AddScene(std::make_shared<MySceneStage1>(*this), L"STAGE1");
	AddScene(std::make_shared<MySceneStage2>(*this), L"STAGE2");
	AddScene(std::make_shared<MySceneStage3>(*this), L"STAGE3");

	mCurrentScene = GetResource(L"LOBBY");
	mCurrentScene->Start();
}

void MySceneManager::Update(const float _deltaTime)
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

void MySceneManager::Render()
{
	mCurrentScene->Render();
}

void MySceneManager::Release()
{
	auto& scenes = GetAllResources();

	for (auto& scene : scenes)
		scene.second->Release();

	ClearResources();
}
