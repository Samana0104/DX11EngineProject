#include "pch.h"
#include "SceneLobby.h"
using namespace HBSoft;

void SceneLobby::Init()
{
    test.m_transform.SetScale({100.f, 100.f});
    test.m_transform.SetLocation({0.f, 0.f});
    test.SetColor({1.f, 0.f, 1.f, 1.f});
}

void SceneLobby::Update(float deltaTime) {}

void SceneLobby::Render()
{
    test.Render();
}

void SceneLobby::Release() {}

void SceneLobby::Reset() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
