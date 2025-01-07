/*
author : 이지혁
description : 돗자리 오브젝트를 관리하는 소스 파일

version: 1.1.0
date: 2025-01-07
*/

#include "pch.h"
#include "PicnicRug.h"
#include "Camera/Camera.h"

using namespace HBSoft;

PicnicRug::PicnicRug()
{
    m_mesh = HASSET->m_meshes[L"picnicrug.hbs"];

    // UnityTrans
    m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
    m_transform.SetLocation(glm::vec3(12.28f, 0.48f, 11.71f));
    m_transform.SetScale(0.0015f);

    m_easyRender.SetVSShader(L"CartoonEnvVS.hlsl");
    m_easyRender.SetPSShader(L"BasicPS.hlsl");
    m_texCube          = HASSET->m_textures[L"cubeTest.dds"];
    m_picnicRugTexture = HASSET->m_textures[L"PicnicRugPattern.png"];
    m_easyRender.SetTexture(m_picnicRugTexture);
    m_easyRender.SetMesh(m_mesh);
}

void PicnicRug::Update(const float deltaTime)
{
    UpdateDefaultCB();
}

void PicnicRug::Render()
{
    HDEVICE->m_context->PSSetShaderResources(1, 1, m_texCube->GetSRV().GetAddressOf());
    m_easyRender.Draw();
}

void PicnicRug::Init() {}

void PicnicRug::Release() {}
