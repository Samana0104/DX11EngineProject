#include "pch.h"
#include "Test3DObj.h"
#include "Camera.h"

using namespace HBSoft;

Test3DObj::Test3DObj()
{
    m_mesh = HASSET->m_meshes[L"202412031822testFBXBlender.hbs"];

    m_easyRender.SetVSShader(L"VertexShader.hlsl");
    m_easyRender.SetPSShader(L"ColorPixelShader.hlsl");
    m_easyRender.SetTexture(nullptr);
    m_easyRender.SetMesh(m_mesh);
}

void Test3DObj::Update(const float deltaTime)
{
    m_transform.SetRotation(glm::vec3(1.57, 0, 0));
    m_transform.SetLocation(glm::vec3(-7, 0, -12));
    UpdateDefaultCB();
}

void Test3DObj::Render()
{
    m_easyRender.Draw();
}

void Test3DObj::Init() {}

void Test3DObj::Release() {}
