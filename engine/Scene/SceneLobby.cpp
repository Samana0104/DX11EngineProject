/*
author : 변한빛
description : 씬의 전환을 테스트 하기 위해 만든 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "SceneLobby.h"
using namespace HBSoft;

SceneLobby::SceneLobby()
    : cameraTest(glm::radians(90.f), 1.f, 10000.f)
{}

void SceneLobby::Update(float deltaTime)
{
    static float test2  = 0;
    test2              += deltaTime;

    test.m_transform.SetLocation({0.f, 0.f, 5.f});
    test.m_transform.SetRotation({-1.f, 3.f, 5.f}, glm::radians(100 * test2));
    test.m_transform.SetScale({1.f, 1.f, 1.f});
    test.Update(deltaTime);
}

void SceneLobby::Render()
{
    test.Render();
}

void SceneLobby::Release() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
