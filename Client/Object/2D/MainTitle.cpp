#include "pch.h"
#include "MainTitle.h"
using namespace HBSoft;

MainTitle::MainTitle()
{
    m_titleTexture = HASSET->m_textures[L"title.png"];
    m_boxMesh      = HASSET->m_meshes[L"BOX2D"];
    m_easyRender.SetVSShader(L"2DBasicVS.hlsl");
    m_easyRender.SetPSShader(L"BasicPS.hlsl");
    m_easyRender.SetMesh(m_boxMesh);
    m_easyRender.SetTexture(m_titleTexture);
    m_easyRender.SetSS(ERSamplerState::LINEAR);
}

void MainTitle::Update(const float deltaTime)
{
    UpdateDefaultCB();
}

void MainTitle::Render()
{
    m_easyRender.Draw();
}

void MainTitle::Init() {}

void MainTitle::Release() {}
