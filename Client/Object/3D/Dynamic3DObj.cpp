/*
author : 이지혁
description : 동적인 오브젝트를 관리하는 소스 파일

version: 1.1.0
date: 2025-01-06
*/
#include "pch.h"
#include "Dynamic3DObj.h"
#include "Camera/Camera.h"

using namespace HBSoft;

Dynamic3DObj::Dynamic3DObj() {}

std::string HBSoft::Dynamic3DObj::GetName()
{
    return m_name;
}

std::string HBSoft::Dynamic3DObj::GetKey()
{
    return m_key;
}

void HBSoft::Dynamic3DObj::SetTransType(DynamicTransformType transType)
{
    m_transType = transType;
}

Transform3D HBSoft::Dynamic3DObj::GetTransform()
{
    return m_transform;
}

void Dynamic3DObj::Init() {}

void Dynamic3DObj::Init(const std::string& key)
{
    m_key = key;
    m_easyRender.SetVSShader(L"CartoonEnvVS.hlsl");
    m_easyRender.SetPSShader(L"CartoonEnvPS.hlsl");
    m_easyRender.SetTexture(nullptr);

    if (key.find('~') == 0)
        SetTransType(DynamicTransformType::DefaultTrans);
    else if (key.find('#') == 0)
        SetTransType(DynamicTransformType::CMTrans);
    else if (key.find('_') == 0)
        SetTransType(DynamicTransformType::UnityTrans);
    else
        SetTransType(DynamicTransformType::GooseGameTrans);

    static int flagCarrotL = 0;
    static int flagCarrotR = 0;

    if (m_transType == DynamicTransformType::GooseGameTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
    }
    else if (m_transType == DynamicTransformType::CMTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
        m_transform.SetScale({1 / 100.0f, 1 / 100.0f, 1 / 100.0f});
    }
    else if (m_transType == DynamicTransformType::UnityTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(12.28f, 0.48f, 11.71f));
        m_transform.SetScale(0.0015f);
    }
    else if (m_key.find("carrotL") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(3.91f - 0.3f * flagCarrotL, 0.78f, 3.81f));
        m_transform.SetScale(0.3f);
        flagCarrotL++;
    }
    else if (m_key.find("carrotR") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(3.91f - 0.3f * flagCarrotR, 0.78f, 4.31f));
        m_transform.SetScale(0.3);
        flagCarrotR++;
    }
    else if (m_key.find("pumpkin0") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(2.08, 0.78, -1.8));
        m_transform.SetScale(0.25f);
    }
    else if (m_key.find("pumpkin1") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(1.55f, 0.78f, -0.63f));
        m_transform.SetScale(0.18f);
    }
    else if (m_key.find("pumpkin2") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-0.120f, 0.78f, -1.800f));
        m_transform.SetScale(0.310f);
    }
    else if (m_key.find("pumpkin3") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-0.550f, 0.78f, -0.950f));
        m_transform.SetScale(0.240f);
    }
    else if (m_key.find("tulipBig") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 1.57f, 0.0f));
        m_transform.SetLocation(glm::vec3(0.75f, 0.87f, 1.83f));
        m_transform.SetScale(0.14f);
    }

    m_mesh     = HASSET->m_meshes[std::wstring().assign(key.begin(), key.end())];
    m_texCube1 = HASSET->m_textures[L"cubeTest.dds"];
    m_easyRender.SetMesh(m_mesh);
}

void Dynamic3DObj::Update(const float deltaTime)
{
    if (m_transType == DynamicTransformType::GooseGameTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
    }
    else if (m_transType == DynamicTransformType::CMTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
        m_transform.SetScale({1 / 100.0f, 1 / 100.0f, 1 / 100.0f});
    }
    else if (m_transType == DynamicTransformType::UnityTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(12.28f, 0.48f, 11.71f));
        m_transform.SetScale(0.0015f);
    }

    UpdateDefaultCB();
}

void Dynamic3DObj::Render()
{
    HDEVICE->m_context->PSSetShaderResources(1, 1, m_texCube1->GetSRV().GetAddressOf());
    m_easyRender.Draw();
}

void Dynamic3DObj::Release() {}
