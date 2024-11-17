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
    : cameraTest(glm::radians(90.f), 0.1f, 10000.f)
{
    cameraTest.LookAt({0.f, 5.f, -10.f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f});
    test.SetCamera(&cameraTest);
    m_line.SetCamera(&cameraTest);
    cube.SetCamera(&cameraTest);
}

void SceneLobby::Update(float deltaTime)
{
    ImGui::Checkbox("wireframe : ", &isWire);

    cameraTest.Update(deltaTime);

    test.Update(deltaTime);
    m_line.Update(deltaTime);
    cube.Update(deltaTime);
}

void SceneLobby::Render()
{
    if (isWire)
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsWireState.Get());
    else
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsState.Get());

    m_line.Draw({0.f, 0.f, 0.f}, {1000.f, 0.f, 0.f}, {1.f, 0.f, 0.f, 1.f});
    m_line.Draw({0.f, 0.f, 0.f}, {0.f, 1000.f, 0.f}, {0.f, 1.f, 0.f, 1.f});
    m_line.Draw({0.f, 0.f, 0.f}, {0.f, 0.f, 1000.f}, {0.f, 0.f, 1.f, 1.f});
    test.Render();
    cube.Render();
}

void SceneLobby::Release() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
