/*
author : 변한빛, 정찬빈, 이지혁
description : 게임 내부 씬을 정의하는 소스 파일

version: 1.1.0
date: 2024-11-30
*/

#include "pch.h"
#include "SceneGame.h"
using namespace HBSoft;

SceneGame::SceneGame()
    : m_tree(5)
{
    cameraTest = std::make_shared<Camera>(glm::radians(90.f), 0.1f, 10000.f);

    cameraTest->LookAt({0.f, 3.f, -1.5f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f});
    m_line.SetCamera(cameraTest);
    cube.SetCamera(cameraTest);
    m_tree.SetCamera(cameraTest);
    m_goose.SetCamera(cameraTest);
    m_goose.SetHeightMap(m_tree.GetMapObj());
}

void SceneGame::Update(float deltaTime)
{

    ImGui::Checkbox("wireframe : ", &isWire);

    cameraTest->Update(deltaTime);


    m_line.Update(deltaTime);
    cube.Update(deltaTime);
    m_escButton.Update(deltaTime);
    m_goose.Update(deltaTime);
    m_tree.Update(deltaTime);
}

void SceneGame::Render()
{
    if (isWire)
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsWireState.Get());
    else
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsState.Get());

    m_line.Draw({0.f, 0.f, 0.f}, {1000.f, 0.f, 0.f}, {1.f, 0.f, 0.f, 1.f});
    m_line.Draw({0.f, 0.f, 0.f}, {0.f, 1000.f, 0.f}, {0.f, 1.f, 0.f, 1.f});
    m_line.Draw({0.f, 0.f, 0.f}, {0.f, 0.f, 1000.f}, {0.f, 0.f, 1.f, 1.f});

    m_goose.Render();
    cube.Render();
    m_escButton.Render();
    m_tree.Render();
}

void SceneGame::Release() {}

void SceneGame::Start() {}

void SceneGame::End() {}