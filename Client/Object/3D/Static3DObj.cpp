/*
author : 이지혁
description : 정적인 오브젝트를 관리하는 소스 파일

version: 1.1.0
date: 2024-12-23
*/
#include "pch.h"
#include "Static3DObj.h"
#include "Camera/Camera.h"

using namespace HBSoft;

Static3DObj::Static3DObj()
    : m_component(m_transform)
{
    m_cubeTex = HASSET->m_textures[L"cubeTest.dds"];
    m_easyRender.SetVSShader(L"BasicVS.hlsl");
    m_easyRender.SetPSShader(L"ColorEnvPS.hlsl");
    m_easyRender.SetTexture(m_cubeTex);
    m_easyRender.SetSS(ERSamplerState::LINEAR);
    m_easyRender.SetMesh(m_mesh);
}

std::string HBSoft::Static3DObj::GetName()
{
    return m_name;
}

void HBSoft::Static3DObj::SetTransType(TransformType transType)
{
    m_transType = transType;
}

void Static3DObj::Update(const float deltaTime)
{
    if (m_transType == TransformType::GooseGameTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0, 0));
        m_transform.SetLocation(glm::vec3(-7, 0, -12));
    }
    else if (m_transType == TransformType::UnityTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0, 0));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
        m_transform.SetScale({1 / 100.0f, 1 / 100.0f, 1 / 100.0f});
    }

    UpdateDefaultCB();
}

void Static3DObj::Render()
{
    HDEVICE->m_context->PSSetShaderResources(1, 1, m_cubeTex->GetSRV().GetAddressOf());
    m_easyRender.Draw();
}

void Static3DObj::Init() {}

void Static3DObj::Init(const std::wstring& key)
{
    m_mesh = HASSET->m_meshes[key];

    m_cubeTex = HASSET->m_textures[L"cubeTest.dds"];
    m_easyRender.SetVSShader(L"BasicVS.hlsl");
    m_easyRender.SetPSShader(L"ColorEnvPS.hlsl");
    m_easyRender.SetTexture(m_cubeTex);
    m_easyRender.SetMesh(m_mesh);
    m_component.AddAABBRange(m_mesh->m_autoCollision.aabb);
}

void Static3DObj::Release() {}
