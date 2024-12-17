/*
author : 변한빛
description : 큐브맵을 그리기 위한 클래스 소스 파일

version: 1.0.8
date: 2024-11-29
*/

#include "pch.h"
#include "CubeMapObj.h"
using namespace HBSoft;

CubeMapObj::CubeMapObj()
{
    m_texture  = HASSET->m_textures[L"cubeTest.dds"];
    m_cubeMesh = HASSET->m_meshes[L"CUBEMAP"];
    m_easyRender.SetVSShader(L"CubeVertex.hlsl");
    m_easyRender.SetPSShader(L"CubePixel.hlsl");
    m_easyRender.SetTexture(m_texture);
    m_easyRender.SetMesh(m_cubeMesh);
    m_easyRender.SetSS(ERSamplerState::LINEAR, 0);

    m_transform.SetScale({1000.f, 1000.f, 1000.f});
}

void CubeMapObj::Update(const float deltaTime)
{
    UpdateDefaultCB();
}

void CubeMapObj::Render()
{
    m_easyRender.SetEntireState();
    m_easyRender.Draw();
}

void CubeMapObj::Release() {}

void CubeMapObj::Init() {}
