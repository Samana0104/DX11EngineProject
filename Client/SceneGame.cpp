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
{
    cameraTest = std::make_shared<Camera>(glm::radians(90.f), 0.1f, 10000.f);
    m_map      = std::make_shared<HeightMapObj>();

    cameraTest->LookAt({0.f, 3.f, -1.5f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f});
    m_line.SetCamera(cameraTest);
    cube.SetCamera(cameraTest);
    m_goose.SetCamera(cameraTest);
    m_map->SetCamera(cameraTest);

    m_goose.SetHeightMap(m_map);
}

void SceneGame::Update(float deltaTime)
{

    ImGui::Checkbox("wireframe : ", &isWire);

    cameraTest->Update(deltaTime);


    m_line.Update(deltaTime);
    cube.Update(deltaTime);
    m_map->Update(deltaTime);
    m_escButton.Update(deltaTime);
    m_goose.Update(deltaTime);
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
    m_map->Render();
    m_escButton.Render();
}

void SceneGame::Release() {}

void SceneGame::Start() {}

void SceneGame::End() {}