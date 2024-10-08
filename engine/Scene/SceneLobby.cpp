#include "pch.h"
#include "SceneLobby.h"
using namespace HBSoft;

void SceneLobby::Init()
{
    mCurrentButton = 0;
    mTitle.SetTextureKey(L"title1.png");
    mTitle->SetScale({135.f, 25.f});
    mTitle->SetLocation({0.f, 17.f});
    mBackground.SetImageScale();
    mBackground.SetColor({0.f, 0.f, 0.f, 1.f});
}

void SceneLobby::Update(float _deltaTime) {}

void SceneLobby::Render() {}

void SceneLobby::Release() {}

void SceneLobby::Reset() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
