#include "pch.h"
#include "MySceneLobby.h"
using namespace MyProject;

void MySceneLobby::Init()
{
	mCurrentButton = 0;
	mTitle.SetTextureKey(L"title1.png");
	mTitle->SetScale({ 135.f, 25.f });
	mTitle->SetLocation({ 0.f, 17.f });
	mBackground.SetImageScale();
	mBackground.SetColor({ 0.f, 0.f, 0.f, 1.f });
}

void MySceneLobby::Update(float _deltaTime)
{
}

void MySceneLobby::Render()
{
}

void MySceneLobby::Release()
{
}

void MySceneLobby::Reset()
{
}

void MySceneLobby::Start()
{
	mManager.mSound[L"theme.ogg"]->InitSound();
	mManager.mSound[L"theme.ogg"]->Play(true);
}

void MySceneLobby::End()
{
}
