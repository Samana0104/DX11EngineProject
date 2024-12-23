#include "pch.h"
#include "Test3DObj.h"
#include "Camera.h"

using namespace HBSoft;

Test3DObj::Test3DObj()
{
    m_mesh = HASSET->m_meshes[L"Walking.hbs"];

    m_easyRender.SetVSShader(L"BasicVS.hlsl");
    m_easyRender.SetPSShader(L"ColorPS.hlsl");
    m_easyRender.SetTexture(nullptr);
    m_easyRender.SetMesh(m_mesh);
}

void Test3DObj::Update(const float deltaTime)
{
    UpdateDefaultCB();
}

void Test3DObj::Render()
{
    m_easyRender.Draw();
    m_easyRender.SetNormalState();
    m_easyRender.Draw(false);
}

void Test3DObj::Init() {}

void Test3DObj::Release() {}
