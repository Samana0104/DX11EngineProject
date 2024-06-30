#include "pch.h"
#include "MySceneSetting.h"
using namespace MyProject;

void MySceneSetting::Init()
{
	obj->SetScale({ 50.f, 50.f });
}

void MySceneSetting::Update(float _deltaTime)
{
	obj->AddRotation(0.5f);

	if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_DOWN)
		mSceneManager.SetCurrentScene(L"LOBBY");
}

void MySceneSetting::Render()
{
	obj.Render();
	mManager.mFont.DrawTextForDebugging(L"¾Æ Èûµé´Ù¾Æ");
}

void MySceneSetting::Release()
{
}

void MySceneSetting::Reset()
{
}

void MySceneSetting::Execute()
{
}
