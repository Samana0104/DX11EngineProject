/*
author : 변한빛, 정찬빈, 이지혁
description : 게임 내부 씬을 정의하는 소스 파일
              v1.1.2 : 하드코딩된 오브젝트 초기화, 업데이트, 렌더 부분 자동화
              v1.1.3 : BGM 추가 (이지혁)

version: 1.1.3
date: 2024-12-24
*/

#include "pch.h"
#include "SceneGame.h"
using namespace HBSoft;

SceneGame::SceneGame()
    : m_tree(2)
{
    m_ingameBGM = HASSET->m_sounds[L"ingameBGM.mp3"];
    m_ingameBGM->VolumeSet(0.15f);
    
#ifdef _DEBUG
    cameraTest = std::make_shared<DebugCamera>();
#else
    cameraTest = std::make_shared<GooseCamera>();
#endif
    lightTest = std::make_shared<DirectionalLight>(vec3(-1.f, -1.f, 0.f), 1.6f);
    mapTest   = std::make_shared<HeightMapObj>();
    m_line    = std::make_shared<LineObj>();
    m_colObjs = std::make_shared<CollisionObj>();
    m_goose   = std::make_shared<Goose>();


    m_line->SetCamera(cameraTest);
    cube.SetCamera(cameraTest);

    m_gardener.SetCamera(cameraTest);
    m_gardener.SetHeightMap(mapTest);
    m_gardener.SetLight(lightTest);
    m_gardener.SetGooseObj(m_goose);

    m_gardener1.SetCamera(cameraTest);
    m_gardener1.SetHeightMap(mapTest);
    m_gardener1.SetLight(lightTest);
    m_gardener1.SetGooseObj(m_goose);

    m_gardener2.SetCamera(cameraTest);
    m_gardener2.SetHeightMap(mapTest);
    m_gardener2.SetLight(lightTest);
    m_gardener2.SetGooseObj(m_goose);

    m_goose->SetCamera(cameraTest);
    m_goose->SetHeightMap(mapTest);
    m_goose->SetLight(lightTest);

    m_picnicRug.SetCamera(cameraTest);
    m_picnicRug.SetLight(lightTest);

    mapTest->SetCamera(cameraTest);
    mapTest->SetLight(lightTest);

    m_tree.SetMapObj(mapTest);

    m_staticObjs.LoadFromFolder("../res/Mesh/StaticObj", cameraTest, lightTest);
    m_colObjs->LoadRange("../res/collision.txt");

    EventHandler::GetInstance().AddEvent(EventList::QUEST_CLEAR, this);
}

void SceneGame::Update(float deltaTime)
{
#ifdef _DEBUG
    ImGui::Checkbox("wireframe : ", &isWire);
    ImGui::SliderFloat("light Power", &lightTest->m_lightPower, 0.f, 5.f);
#endif

    cameraTest->Update(deltaTime);

    if (!m_isGameClear)
    {
        m_escButton.Update(deltaTime);
        m_questGUI.Update(deltaTime);
    }
    else
    {
        m_isTimer += deltaTime;
        if (m_isTimer <= 5.f)
        {
            vec3 cameraEye  = cameraTest->GetEyePos();
            cameraEye.y    += 0.25f * m_isTimer;

            cameraTest->Move(cameraEye);
        }
        else
        {
            HASSET->m_fonts[L"DEBUG_FONT"]->DrawMsg(
            L"제작 : 변한빛, 이지혁, 정찬빈 \n\n\n 엔진 : 변한빛 \n 맵 : 이지혁 \n 캐릭터, AI : 정찬빈 "
            L"\n\n\n 플레이해주셔서 감사합니다.");
        }

        if (m_isTimer > 10.f)
        {
            HSCENE.SetCurrentScene(L"Lobby");
        }
    }

    cube.Update(deltaTime);
    m_gardener.Update(deltaTime);
    m_gardener1.Update(deltaTime);
    m_gardener2.Update(deltaTime);
    m_goose->Update(deltaTime);

    m_picnicRug.Update(deltaTime);
    m_tree.Update(deltaTime);

#ifdef _DEBUG
    m_line->Update(deltaTime);
#endif

    m_colObjs->Update(deltaTime);

    for (auto& hbsc : m_staticObjs.HBSContainer)
    {
        hbsc->Update(deltaTime);
    }

    m_goose->ProcessCollision(m_colObjs);
    for (auto& hbdc : m_dynamicObjs.HBSContainer)
    {
        m_goose->ProcessCollision(hbdc);
        hbdc->Update(deltaTime);
    }

    for (auto& hbdc : m_dynamicObjs.HBSContainer)
    {
        m_picnicRug.ProcessCollision(hbdc);
    }

    if (HINPUT->IsKeyDown(VK_F2))
    {
        EventHandler::GetInstance().Notify(EventList::QUEST_CLEAR);
    }
}

void SceneGame::Render()
{
    EasyRender::Begin(MultiRT::SUB1);
    EasyRender::SetWireFrame(isWire);


    for (auto& hbsc : m_staticObjs.HBSContainer)
        hbsc->Render();

    for (auto& hbdc : m_dynamicObjs.HBSContainer)
    {
        hbdc->Render();
        // hbdc->m_component.DrawBoundary(m_line);
    }

#ifdef _DEBUG
    m_line->Draw({0.f, 0.f, 0.f}, {1000.f, 0.f, 0.f}, {1.f, 0.f, 0.f, 1.f});
    m_line->Draw({0.f, 0.f, 0.f}, {0.f, 1000.f, 0.f}, {0.f, 1.f, 0.f, 1.f});
    m_line->Draw({0.f, 0.f, 0.f}, {0.f, 0.f, 1000.f}, {0.f, 0.f, 1.f, 1.f});
#endif

    m_gardener.Render();
    m_gardener1.Render();
    m_gardener2.Render();
    m_goose->Render();
    m_picnicRug.Render();

    m_tree.Render();
    cube.Render();
    EasyRender::End(MultiRT::SUB1);

    // 글자 안나오는 이유 상수 버퍼
    // 프레임 떨어지는 이유 폰트로
    EasyRender::Begin(MultiRT::GUI);
    if (!m_isGameClear)
    {
        m_questGUI.Render();
        m_escButton.Render();
    }
    EasyRender::End(MultiRT::GUI);

    if (HINPUT->IsKeyDown(VK_HOME))
    {
        EasyRender::SaveScreenShot(MultiRT::GUI, L"Gui");
        EasyRender::SaveScreenShot(MultiRT::MAIN, L"Test");
    }

    EasyRender::MergeRenderTarget(MultiRT::MAIN, MultiRT::SUB1);
    EasyRender::MergeRenderTarget(MultiRT::MAIN, MultiRT::GUI);
}

void SceneGame::Release()
{
    EventHandler::GetInstance().DeleteEvent(EventList::QUEST_CLEAR, this);
}

void SceneGame::Start()
{
    Dynamic3DObj::flagCarrotL = 0;
    Dynamic3DObj::flagCarrotR = 0;

    m_dynamicObjs.LoadFromFolder("../res/Mesh/DynamicObj", cameraTest, lightTest);
#ifdef _DEBUG
    m_goose->m_transform.SetLocation({8.0f, 0.4f, 4.0f});
#else
    m_goose->m_transform.SetLocation({23.5f, 0.625f, -4.5f});
#endif
    m_gardener.m_transform.SetLocation({-0.6f, 0.3f, 0.7f});
    m_gardener1.m_transform.SetLocation({3.f, 0.3f, 5.f});
    m_gardener2.m_transform.SetLocation({0.37f, 0.3f, 3.f});
    cameraTest->SetPerspective(glm::radians(90.f), 0.5f, 10000.f);
    cameraTest->LookAt({m_goose->m_transform.m_pos[0] + 1.f,
                        m_goose->m_transform.m_pos[1] + 2.5f,
                        m_goose->m_transform.m_pos[2]},
                       m_goose->m_transform.m_pos,
                       {0.f, 1.f, 0.f});

    m_goose->Init();
    m_questGUI.Init();
    m_isTimer     = 0.f;
    m_isGameClear = false;
}

void SceneGame::End()
{
    m_ingameBGM->Stop();
    m_dynamicObjs.HBSContainer.clear();
}

void SceneGame::OnNotice(EventList event, void* entity)
{
    if (event == EventList::QUEST_CLEAR)
    {
        m_isGameClear          = true;
        m_goose->m_isGameClear = true;

        cameraTest->LookAt({m_goose->m_transform.m_pos[0] + 0.5f,
                            m_goose->m_transform.m_pos[1] + 2.5f,
                            m_goose->m_transform.m_pos[2]},
                           m_goose->m_transform.m_pos,
                           {0.f, 1.f, 0.f});
        // HSCENE.SetCurrentScene(L"Lobby");
    }
}
