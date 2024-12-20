#include "pch.h"
#include "PlanterFenceGrass.h"
#include "Camera.h"

using namespace HBSoft;

PlanterFenceGrass::PlanterFenceGrass()
{
    m_mesh = HASSET->m_meshes[L"PlanterFenceGrass.hbs"];

    m_easyRender.SetVSShader(L"VertexShader.hlsl");
    m_easyRender.SetPSShader(L"ColorPixelShader.hlsl");
    m_easyRender.SetTexture(nullptr);
    m_easyRender.SetMesh(m_mesh);
}

void PlanterFenceGrass::Update(const float deltaTime)
{
    ImGui::DragFloat("Scale", &m_scale, 0.01f, 0.0f, 900.f);
    ImGui::DragFloat("trnasX", &m_transX, 0.01f, -100.0f, 100.0f);
    ImGui::DragFloat("trnasY", &m_transY, 0.01f, -100.0f, 100.0f);
    ImGui::DragFloat("trnasZ", &m_transZ, 0.01f, -100.0f, 100.0f);
    m_transform.SetRotation(glm::vec3(1.57, 0, 0));
    m_transform.SetLocation(glm::vec3(m_transX, m_transY, m_transZ));
    m_transform.SetScale({1 / m_scale, 1 / m_scale, 1 / m_scale});
    UpdateDefaultCB();
}

void PlanterFenceGrass::Render()
{
    m_easyRender.Draw();
}

void PlanterFenceGrass::Init() {}

void PlanterFenceGrass::Release() {}
