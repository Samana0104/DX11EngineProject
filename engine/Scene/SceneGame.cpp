#include "pch.h"
#include "SceneGame.h"

using namespace HBSoft;

SceneGame::SceneGame()
    : camera(glm::radians(90.0f), 0.1f, 10000.0f)
{
    camera.LookAt(vec3(0.0f, 10.f, -20.f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    /* goose.SetCamera(&camera);*/
    /* cube.SetCamera(&camera);
     line.SetCamera(&camera);*/
}

void SceneGame::Update(float deltaTime)
{
    ImGui::Checkbox("wireframe : ", &isWire);

    camera.Update(deltaTime);

    /*goose.Update(deltaTime);*/

    /*cube.Update(deltaTime);*/
    /*  line.Update(deltaTime);*/

    if (HINPUT->IsKeyDown(VK_LBUTTON))
    {
        Core::engine->m_sceneMgr.SetCurrentScene(L"Lobby");
    }
}

void SceneGame::Render()
{
    if (isWire)
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsWireState.Get());
    else
        HDEVICE->m_context->RSSetState(HDEVICE->m_rsState.Get());

    /*goose.Render();*/
    /*circle.Render();*/
    /* cube.Render();*/
}

void SceneGame::Release() {}

void SceneGame::Start() {}

void SceneGame::End() {}
