/*
author : 변한빛, 정찬빈, 이지혁
description : 게임 내부 씬을 정의하는 소스 파일

version: 1.1.1
date: 2024-12-23
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
    m_terrain.SetCamera(cameraTest);
    m_planterLeftLowDirt.Init(L"PlanterLeftLowDirt.hbs");
    m_planterLeftLowDirt.SetCamera(cameraTest);
    m_planterLeftLowEdges.Init(L"PlanterLeftLowEdges.hbs");
    m_planterLeftLowEdges.SetCamera(cameraTest);
    m_hedges[0].Init(L"HedgeLeft0.hbs");
    m_hedges[1].Init(L"HedgeLeft1.hbs");
    m_hedges[2].Init(L"HedgeLeft2.hbs");
    m_hedges[3].Init(L"HedgeRight0.hbs");
    m_hedges[4].Init(L"HedgeRight1.hbs");
    for (int i = 0; i < std::size(m_hedges); i++)
        m_hedges[i].SetCamera(cameraTest);
    m_brickwalls[0].Init(L"brickwall0.hbs");
    m_brickwalls[1].Init(L"brickwall1.hbs");
    m_brickwalls[2].Init(L"brickwall2.hbs");
    m_brickwalls[3].Init(L"brickwall3.hbs");
    m_brickwalls[4].Init(L"brickwall4.hbs");
    m_brickwalls[5].Init(L"brickgate.hbs");
    for (int i = 0; i < std::size(m_brickwalls); i++)
        m_brickwalls[i].SetCamera(cameraTest);
    m_waterTank.Init(L"watertank.hbs");
    m_waterTank.SetCamera(cameraTest);
    m_shed.Init(L"shed.hbs");
    m_shed.SetCamera(cameraTest);
    m_shedporch.Init(L"shedporch.hbs");
    m_shedporch.SetCamera(cameraTest);
    m_trestletable.Init(L"trestletable.hbs");
    m_trestletable.SetCamera(cameraTest);
    m_plasticchair.Init(L"plasticchair1.hbs");
    m_plasticchair.SetCamera(cameraTest);
    m_oilbarrels.Init(L"oilbarrels.hbs");
    m_oilbarrels.SetCamera(cameraTest);
    m_foregroundgarden.Init(L"foregroundgarden.hbs");
    m_foregroundgarden.SetCamera(cameraTest);
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
    m_terrain.Update(deltaTime);
    m_planterLeftLowDirt.Update(deltaTime, TransformType::OriginalTrans);
    m_planterLeftLowEdges.Update(deltaTime, TransformType::UnityTrans);
    for (int i = 0; i < std::size(m_hedges); i++)
        m_hedges[i].Update(deltaTime, TransformType::OriginalTrans);
    for (int i = 0; i < std::size(m_brickwalls); i++)
        m_brickwalls[i].Update(deltaTime, TransformType::OriginalTrans);
    m_waterTank.Update(deltaTime, TransformType::OriginalTrans);
    m_shed.Update(deltaTime);
    m_shedporch.Update(deltaTime);
    m_trestletable.Update(deltaTime);
    m_plasticchair.Update(deltaTime);
    m_oilbarrels.Update(deltaTime);
    m_foregroundgarden.Update(deltaTime);
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
    m_terrain.Render();
    m_planterLeftLowDirt.Render();
    m_planterLeftLowEdges.Render();
    for (int i = 0; i < std::size(m_hedges); i++)
        m_hedges[i].Render();
    for (int i = 0; i < std::size(m_brickwalls); i++)
        m_brickwalls[i].Render();
    m_waterTank.Render();
    m_shed.Render();
    m_shedporch.Render();
    m_trestletable.Render();
    m_plasticchair.Render();
    m_oilbarrels.Render();
    m_foregroundgarden.Render();
    EasyRender::End();

    EasyRender::Begin(MultiRT::GUI);
    m_escButton.Render();
    HASSET->m_fonts[L"DEBUG_FONT"]->DrawMsg(HDEVICE, HTIMER.m_csBuffer, {10.f, 10.f, 1000.f, 1000.f});
    EasyRender::End();

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