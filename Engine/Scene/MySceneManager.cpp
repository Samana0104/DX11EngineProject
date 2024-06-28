#include "pch.h"
#include "MySceneManager.h"
#include "MySceneLobby.h"
#include "MySceneSetting.h"
using namespace MyProject;

void MySceneManager::AddScene(std::shared_ptr<MyScene> _scene, SCENE_KEY _key)
{
	_scene->Init();
	AddResource(_key, _scene);
}
void MySceneManager::SetCurrentScene(SCENE_KEY _key)
{
	mCurrentScene = GetResource(_key);
}

void MySceneManager::Init()
{
	AddScene(std::make_shared<MySceneLobby>(*this), L"LOBBY");
	AddScene(std::make_shared<MySceneSetting>(*this), L"SETTING");

	SetCurrentScene(L"LOBBY");
}

void MySceneManager::Update(const float _deltaTime)
{
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

	Clear();
}
