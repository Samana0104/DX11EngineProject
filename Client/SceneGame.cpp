/*
author : ���Ѻ�, ������, ������
description : ���� ���� ���� �����ϴ� �ҽ� ����
              v1.1.2 : �ϵ��ڵ��� ������Ʈ �ʱ�ȭ, ������Ʈ, ���� �κ� �ڵ�ȭ

version: 1.1.2
date: 2024-12-24
*/

#include "pch.h"
#include "SceneGame.h"
using namespace HBSoft;

SceneGame::SceneGame()
    : m_tree(5)
{
    cameraTest = std::make_shared<Camera>(glm::radians(90.f), 0.1f, 10000.f);
    lightTest  = std::make_shared<DirectionalLight>(vec3(-1.f, -1.f, 0.f), 1.f);
    mapTest    = std::make_shared<HeightMapObj>();

    cameraTest->LookAt({0.f, 3.f, -1.5f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f});
    m_line.SetCamera(cameraTest);
    cube.SetCamera(cameraTest);
    m_test.SetCamera(cameraTest);

    m_goose.SetCamera(cameraTest);
    m_goose.SetHeightMap(mapTest);
    m_goose.SetLight(lightTest);

    mapTest->SetCamera(cameraTest);
    mapTest->SetLight(lightTest);

    m_tree.SetHeightMapObj(mapTest);
    m_test.SetLight(lightTest);

    m_staticObjs.LoadFromFolder("../res/Mesh/StaticObj", cameraTest, lightTest);
}

void SceneGame::Update(float deltaTime)
{
    ImGui::Checkbox("wireframe : ", &isWire);
    ImGui::SliderFloat("light Power", &lightTest->m_lightPower, 0.f, 2.f);

    /*ImGui::DragFloat("X: ", &m_x, 0.1f);
    ImGui::DragFloat("Y: ", &m_y, 0.1f);
    ImGui::DragFloat("Z: ", &m_z, 0.1f);*/

    cameraTest->Update(deltaTime);
    m_line.Update(deltaTime);
    cube.Update(deltaTime);
    m_escButton.Update(deltaTime);
    m_test.Update(deltaTime);
    m_goose.Update(deltaTime);
    m_tree.Update(deltaTime);

    //m_test2.GetTransform().SetLocation(glm::vec3(m_x, m_y, m_z));

    for (auto& hbsc : m_staticObjs.HBSContainer)
    {
        //if (hbsc.GetName() != m_test2.GetName())
            hbsc.Update(deltaTime);
    }
}

void SceneGame::Render()
{
    EasyRender::Begin(MultiRT::MAIN);
    EasyRender::SetWireFrame(isWire);
    m_line.Draw({0.f, 0.f, 0.f}, {1000.f, 0.f, 0.f}, {1.f, 0.f, 0.f, 1.f});
    m_line.Draw({0.f, 0.f, 0.f}, {0.f, 1000.f, 0.f}, {0.f, 1.f, 0.f, 1.f});
    m_line.Draw({0.f, 0.f, 0.f}, {0.f, 0.f, 1000.f}, {0.f, 0.f, 1.f, 1.f});

    m_goose.Render();
    cube.Render();
    m_tree.Render();
    m_test.Render();
    //m_test2.Render();

    for (auto& hbsc : m_staticObjs.HBSContainer)
    {
        //if (hbsc.GetName() != m_test2.GetName())
            hbsc.Render();
    }
    EasyRender::End(MultiRT::MAIN);

    // ���� �ȳ����� ���� ��� ����
    // ������ �������� ���� ��Ʈ��
    EasyRender::Begin(MultiRT::GUI);
    m_escButton.Render();
    EasyRender::End(MultiRT::GUI);

    if (HINPUT->IsKeyDown(VK_HOME))
    {
        EasyRender::SaveScreenShot(MultiRT::GUI, L"Gui");
        EasyRender::SaveScreenShot(MultiRT::MAIN, L"Test");
    }

    EasyRender::MergeRenderTarget(MultiRT::MAIN, MultiRT::GUI);
}

void SceneGame::Release() {}

void SceneGame::Start() {}

void SceneGame::End() {}