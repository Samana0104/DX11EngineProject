/*
author : 변한빛
description : 게임 내부 씬을 정의하는 소스 파일

version: 1.1.0
date: 2024-11-30
*/

#include "SceneGame.h"
using namespace HBSoft;

SceneGame::SceneGame()
{
    cameraTest = std::make_shared<Camera>(glm::radians(90.f), 0.1f, 10000.f);


    cameraTest->LookAt({0.f, 3.f, -1.5f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f});
    m_line.SetCamera(cameraTest);
    m_line1.SetCamera(cameraTest);
    cube.SetCamera(cameraTest);
    m_map.SetCamera(cameraTest);
    m_goose.SetCamera(cameraTest);
    m_gardener.SetCamera(cameraTest);
    m_map1.SetCamera(cameraTest);
}

void SceneGame::Update(float deltaTime)
{

    ImGui::Checkbox("wireframe : ", &isWire);

    cameraTest->Update(deltaTime);


    m_line.Update(deltaTime);
    m_line1.Update(deltaTime);
    cube.Update(deltaTime);
    m_map.Update(deltaTime);
    m_escButton.Update(deltaTime);
    m_goose.Update(deltaTime);
    m_gardener.Update(deltaTime);
    m_map1.Update(deltaTime);


    if (m_aabbCollider.CheckAABBCollision(m_goose.GetaabbCollider(), m_gardener.GetaabbCollider()))
    {
        std::cout << "1";
    }
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


    m_line.Draw(m_gardener.GetaabbCollider().min,
                m_gardener.GetaabbCollider().min + vec3(1.5f, 0.f, 0.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_gardener.GetaabbCollider().min + vec3(1.5f, 0.f, 0.f),
                m_gardener.GetaabbCollider().min + vec3(1.5f, 0.f, 1.5f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_gardener.GetaabbCollider().min + vec3(1.5f, 0.f, 1.5f),
                m_gardener.GetaabbCollider().min + vec3(0.f, 0.f, 1.5f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_gardener.GetaabbCollider().min + vec3(0.f, 0.f, 1.5f),
                m_gardener.GetaabbCollider().min,
                {1.f, 1.f, 1.f, 1.f});


    m_line.Draw(m_gardener.GetaabbCollider().min,
                m_gardener.GetaabbCollider().min + vec3(0.f, 1.5f, 0.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_gardener.GetaabbCollider().min + vec3(1.5f, 0.f, 0.f),
                m_gardener.GetaabbCollider().min + vec3(1.5f, 1.5f, 0.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_gardener.GetaabbCollider().min + vec3(1.5f, 0.f, 1.5f),
                m_gardener.GetaabbCollider().min + vec3(1.5f, 1.5f, 1.5f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_gardener.GetaabbCollider().min + vec3(0.f, 0.f, 1.5f),
                m_gardener.GetaabbCollider().min + vec3(0.f, 1.5f, 1.5f),
                {1.f, 1.f, 1.f, 1.f});


    m_line.Draw(m_gardener.GetaabbCollider().max,
                m_gardener.GetaabbCollider().max - vec3(0.f, 0.f, 1.5f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_gardener.GetaabbCollider().max - vec3(0.f, 0.f, 1.5f),
                m_gardener.GetaabbCollider().max - vec3(1.5f, 0.f, 1.5f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_gardener.GetaabbCollider().max - vec3(1.5f, 0.f, 1.5f),
                m_gardener.GetaabbCollider().max - vec3(1.5f, 0.f, 0.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_gardener.GetaabbCollider().max - vec3(1.5f, 0.f, 0.f),
                m_gardener.GetaabbCollider().max,
                {1.f, 1.f, 1.f, 1.f});

    m_line.Draw(m_goose.GetaabbCollider().min,
                m_goose.GetaabbCollider().min + vec3(1.f, 0.f, 0.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_goose.GetaabbCollider().min + vec3(1.f, 0.f, 0.f),
                m_goose.GetaabbCollider().min + vec3(1.f, 0.f, 1.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_goose.GetaabbCollider().min + vec3(1.f, 0.f, 1.f),
                m_goose.GetaabbCollider().min + vec3(0.f, 0.f, 1.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_goose.GetaabbCollider().min + vec3(0.f, 0.f, 1.f),
                m_goose.GetaabbCollider().min,
                {1.f, 1.f, 1.f, 1.f});


    m_line.Draw(m_goose.GetaabbCollider().min,
                m_goose.GetaabbCollider().min + vec3(0.f, 1.f, 0.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_goose.GetaabbCollider().min + vec3(1.f, 0.f, 0.f),
                m_goose.GetaabbCollider().min + vec3(1.f, 1.f, 0.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_goose.GetaabbCollider().min + vec3(1.f, 0.f, 1.f),
                m_goose.GetaabbCollider().min + vec3(1.f, 1.f, 1.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_goose.GetaabbCollider().min + vec3(0.f, 0.f, 1.f),
                m_goose.GetaabbCollider().min + vec3(0.f, 1.f, 1.f),
                {1.f, 1.f, 1.f, 1.f});


    m_line.Draw(m_goose.GetaabbCollider().max,
                m_goose.GetaabbCollider().max - vec3(0.f, 0.f, 1.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_goose.GetaabbCollider().max - vec3(0.f, 0.f, 1.f),
                m_goose.GetaabbCollider().max - vec3(1.f, 0.f, 1.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_goose.GetaabbCollider().max - vec3(1.f, 0.f, 1.f),
                m_goose.GetaabbCollider().max - vec3(1.f, 0.f, 0.f),
                {1.f, 1.f, 1.f, 1.f});
    m_line.Draw(m_goose.GetaabbCollider().max - vec3(1.f, 0.f, 0.f),
                m_goose.GetaabbCollider().max,
                {1.f, 1.f, 1.f, 1.f});

    m_map.Render();
    m_goose.Render();
    m_gardener.Render();
    m_map1.Render();
    cube.Render();
    m_escButton.Render();

    /* std::cout << m_map.GetHeight(m_goose.GetLocationX(), m_goose.GetLocationZ());*/
}

void SceneGame::Release() {}

void SceneGame::Start() {}

void SceneGame::End() {}