/*
author : 이지혁
description : 정적인 오브젝트를 관리하는 소스 파일

version: 1.1.0
date: 2024-12-23
*/
#include "pch.h"
#include "Static3DObj.h"
#include "Camera.h"

using namespace HBSoft;

Static3DObj::Static3DObj()
{
    m_easyRender.SetVSShader(L"VertexShader.hlsl");
    m_easyRender.SetPSShader(L"ColorPixelShader.hlsl");
    m_easyRender.SetTexture(nullptr);
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
    m_easyRender.Draw();
}

void Static3DObj::Init() {}

void Static3DObj::Init(const std::wstring& key)
{
    m_mesh = HASSET->m_meshes[key];

    m_easyRender.SetVSShader(L"VertexShader.hlsl");
    m_easyRender.SetPSShader(L"ColorPixelShader.hlsl");
    m_easyRender.SetTexture(nullptr);
    m_easyRender.SetMesh(m_mesh);
}

void Static3DObj::Release() {}
