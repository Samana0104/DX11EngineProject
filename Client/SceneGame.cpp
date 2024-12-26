/*
author : 변한빛, 정찬빈, 이지혁
description : 게임 내부 씬을 정의하는 소스 파일
              v1.1.2 : 하드코딩된 오브젝트 초기화, 업데이트, 렌더 부분 자동화

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

    cameraTest->Update(deltaTime);
    m_line.Update(deltaTime);
    cube.Update(deltaTime);
    m_escButton.Update(deltaTime);
    m_test.Update(deltaTime);
    m_goose.Update(deltaTime);
    m_tree.Update(deltaTime);

    for (auto& hbsc : m_staticObjs.HBSContainer)
    {
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

    for (auto& hbsc : m_staticObjs.HBSContainer)
    {
        hbsc.Render();
    }
    EasyRender::End(MultiRT::MAIN);

    // 글자 안나오는 이유 상수 버퍼
    // 프레임 떨어지는 이유 폰트로
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