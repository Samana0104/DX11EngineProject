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
    : m_tree(2)
{
#ifdef _DEBUG
    cameraTest = std::make_shared<DebugCamera>();
#else
    cameraTest = std::make_shared<GooseCamera>();
#endif
    lightTest = std::make_shared<DirectionalLight>(vec3(-1.f, -1.f, 0.f), 1.6f);
    mapTest   = std::make_shared<HeightMapObj>();
    m_line    = std::make_shared<LineObj>();
    m_colObjs = std::make_shared<CollisionObj>();

    cameraTest->SetPerspective(glm::radians(90.f), 1.f, 10000.f);
    cameraTest->LookAt({m_goose.m_transform.m_pos[0] + 0.9f,
                        m_goose.m_transform.m_pos[1] + 3.0f,
                        m_goose.m_transform.m_pos[2]},
                       m_goose.m_transform.m_pos,
                       {0.f, 1.f, 0.f});

    m_line->SetCamera(cameraTest);
    cube.SetCamera(cameraTest);

    // m_gardener.SetCamera(cameraTest);
    // m_gardener.SetLight(lightTest);

    m_goose.SetCamera(cameraTest);
    m_goose.SetHeightMap(mapTest);
    m_goose.SetLight(lightTest);

    mapTest->SetCamera(cameraTest);
    mapTest->SetLight(lightTest);

    m_tree.SetMapObj(mapTest);

    m_grid.SetCamera(cameraTest);
    m_staticObjs.LoadFromFolder("../res/Mesh/StaticObj", cameraTest, lightTest);
    m_colObjs->LoadRange("../res/collision.txt");
    // m_colObjs.SaveRange("../res/collision.txt");
}

void SceneGame::Update(float deltaTime)
{
#ifdef _DEBUG
    ImGui::Checkbox("wireframe : ", &isWire);
    ImGui::SliderFloat("light Power", &lightTest->m_lightPower, 0.f, 5.f);
#endif

    cameraTest->Update(deltaTime);

    m_escButton.Update(deltaTime);
    m_questGUI.Update(deltaTime);

    cube.Update(deltaTime);
    m_grid.Update(deltaTime);
    // m_gardener.Update(deltaTime);
    m_goose.Update(deltaTime);
    m_tree.Update(deltaTime);

    m_line->Update(deltaTime);

    m_colObjs->Update(deltaTime);
    // m_test2.GetTransform().SetLocation(glm::vec3(m_x, m_y, m_z));

    for (auto& hbsc : m_staticObjs.HBSContainer)
    {
        hbsc->Update(deltaTime);
    }

    m_goose.ProcessCollision(m_colObjs);
}

void SceneGame::Render()
{
    EasyRender::Begin(MultiRT::MAIN);
    EasyRender::SetWireFrame(isWire);


    for (auto& hbsc : m_staticObjs.HBSContainer)
        hbsc->Render();

#ifdef _DEBUG
    m_line->Draw({0.f, 0.f, 0.f}, {1000.f, 0.f, 0.f}, {1.f, 0.f, 0.f, 1.f});
    m_line->Draw({0.f, 0.f, 0.f}, {0.f, 1000.f, 0.f}, {0.f, 1.f, 0.f, 1.f});
    m_line->Draw({0.f, 0.f, 0.f}, {0.f, 0.f, 1000.f}, {0.f, 0.f, 1.f, 1.f});
#endif

    // m_gardener.Render();
    m_goose.Render();
    //m_grid.Render();

    m_tree.Render();
    cube.Render();
    // m_goose.m_component.DrawBoundary(m_line);
    m_goose.m_component.DrawBoundary(m_line);
    m_colObjs->m_component.DrawBoundary(m_line);
    EasyRender::End(MultiRT::MAIN);

    // 글자 안나오는 이유 상수 버퍼
    // 프레임 떨어지는 이유 폰트로
    EasyRender::Begin(MultiRT::GUI);
    m_questGUI.Render();
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