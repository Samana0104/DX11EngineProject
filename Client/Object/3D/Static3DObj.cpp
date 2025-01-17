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
{
    m_easyRender.SetVSShader(L"CartoonEnvVS.hlsl");
    m_easyRender.SetPSShader(L"CartoonEnvPS.hlsl");
    m_easyRender.SetTexture(nullptr);
    m_easyRender.SetMesh(m_mesh);
}

std::string HBSoft::Static3DObj::GetName()
{
    return m_name;
}

std::string HBSoft::Static3DObj::GetKey()
{
    return m_key;
}

void HBSoft::Static3DObj::SetTransType(StaticTransformType transType)
{
    m_transType = transType;
}

Transform3D HBSoft::Static3DObj::GetTransform()
{
    return m_transform;
}

void Static3DObj::Init() {}

void Static3DObj::Init(const std::string& key)
{
    m_key = key;
    m_easyRender.SetVSShader(L"CartoonEnvVS.hlsl");
    m_easyRender.SetPSShader(L"CartoonEnvPS.hlsl");
    m_easyRender.SetTexture(nullptr);

    if (key.find('~') == 0)
        SetTransType(StaticTransformType::DefaultTrans);
    else if (key.find('#') == 0)
        SetTransType(StaticTransformType::CMTrans);
    else if (key.find('@') == 0)
        SetTransType(StaticTransformType::Test);
    else if (key.find('_') == 0)
        SetTransType(StaticTransformType::UnityTrans);
    else if (key.find('!') == 0)
        SetTransType(StaticTransformType::ConcretePath);
    else if (key.find("StoneHouses") == 0)
        SetTransType(StaticTransformType::FrontHouse);
    else if (key.find("store") == 0)
        SetTransType(StaticTransformType::Store);
    else if (key.find("bollard") == 0)
        SetTransType(StaticTransformType::Bollard);
    else if (key.find("parkcube") == 0)
        SetTransType(StaticTransformType::Parkcube);
    else if (key.find("bench") == 0)
        SetTransType(StaticTransformType::Bench);
    else if (key.find("retainer") == 0)
        SetTransType(StaticTransformType::PondRetainers);
    else if (key.find("singleconcreteblock22") == 0)
        SetTransType(StaticTransformType::Concrete22);
    else if (key.find("bridge") == 0)
        SetTransType(StaticTransformType::Bridge);
    else if (key == "PanterDirltRightLow1.hbs")
        SetTransType(StaticTransformType::DirtRightLow1);
    else if (key == "cabbage0.hbs")
        SetTransType(StaticTransformType::Cabbage0);
    else if (key == "cabbage1.hbs")
        SetTransType(StaticTransformType::Cabbage1);
    else if (key == "cabbage2.hbs")
        SetTransType(StaticTransformType::Cabbage2);
    else if (key == "cabbage3.hbs")
        SetTransType(StaticTransformType::Cabbage3);
    else
        SetTransType(StaticTransformType::GooseGameTrans);

    static int flagSeed    = 0;

    if (key == "_picnicrug.hbs")
    {
        /*m_easyRender.SetPSShader(L"BasicPS.hlsl");
        m_picnicRugTexture = HASSET->m_textures[L"PicnicRugPattern.png"];
        m_easyRender.SetTexture(m_picnicRugTexture);*/
    }
    else if (m_key.find("seedling") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, generateRandomValue(0.0f, 6.28f), 0.0f));
        m_transform.SetLocation(
        glm::vec3(5.01f - 0.55f * flagSeed, generateRandomValue(0.92f, 0.98f), 9.82f));
        m_transform.SetScale(0.09f);
        flagSeed++;
    }
    else if (m_key.find("pumpkinLeavesL_") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(-0.35f, 1.09f, -0.06f));
        m_transform.SetLocation(glm::vec3(1.68f, 0.98f, -1.05f));
        m_transform.SetScale(0.21f);
    }
    else if (m_key.find("pumpkinLeavesR_") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(-0.32f, -2.15f, 0.07f));
        m_transform.SetLocation(glm::vec3(-0.25f, 1.02f, -1.19f));
        m_transform.SetScale(0.19f);
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

void Static3DObj::Update(const float deltaTime)
{
    if (m_transType == StaticTransformType::GooseGameTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
    }
    else if (m_transType == StaticTransformType::CMTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
        m_transform.SetScale({1 / 100.0f, 1 / 100.0f, 1 / 100.0f});
    }
    else if (m_transType == StaticTransformType::UnityTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(12.28f, 0.48f, 11.71f));
        m_transform.SetScale(0.0015f);
    }
    else if (m_transType == StaticTransformType::ConcretePath)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-4.85f, 0.26f, -8.41f));
        m_transform.SetScale(0.86f);
    }
    else if (m_transType == StaticTransformType::FrontHouse)
    {
        m_transform.SetRotation(glm::vec3(1.57f, -0.25f, 0.0f));
        m_transform.SetLocation(glm::vec3(4.9f, 0.0f, 13.5f));
        m_transform.SetScale(1.0f);
    }
    else if (m_transType == StaticTransformType::Store)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.35f, 0.0f));
        m_transform.SetLocation(glm::vec3(-14.2f, -1.8f, -12.65f));
        m_transform.SetScale(1);
    }
    else if (m_transType == StaticTransformType::Bollard || m_transType == StaticTransformType::Parkcube)
    {
        m_transform.SetRotation(glm::vec3(1.57f, -0.1f, 0.0f));
        m_transform.SetLocation(glm::vec3(-5.3f, 0.1f, -6.5f));
        m_transform.SetScale(0.85f);
    }
    else if (m_transType == StaticTransformType::Bench)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.05f, 0.0f));
        m_transform.SetLocation(glm::vec3(-3.55f, 0.4f, -8.6f));
        m_transform.SetScale(0.85f);
    }
    else if (m_transType == StaticTransformType::PondRetainers)
    {
        m_transform.SetRotation(glm::vec3(1.57f, -0.03f, 0.0f));
        m_transform.SetLocation(glm::vec3(-4.2f, 0.0f, -7.39f));
        m_transform.SetScale(0.83f);
    }
    else if (m_transType == StaticTransformType::Concrete22)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.26f, 0.0f));
        m_transform.SetLocation(glm::vec3(0.37f, 0.32f, -10.11f));
        m_transform.SetScale(0.845f);
    }
    else if (m_transType == StaticTransformType::Bridge)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-4.86f, 0.26f, -8.42f));
        m_transform.SetScale(0.86f);
    }
    else if (m_transType == StaticTransformType::DirtRightLow1)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-6.7f, 0.0f, -12.0f));
        m_transform.SetScale(glm::vec3(1.8f, 1.0f, 1.0f));
    }
    else if (m_transType == StaticTransformType::Cabbage0)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(5.09f, 1.03f, -1.3f));
        m_transform.SetScale(0.22f);
    }
    else if (m_transType == StaticTransformType::Cabbage1)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(4.570f, 1.03f, -0.600f));
        m_transform.SetScale(0.22f);
    }
    else if (m_transType == StaticTransformType::Cabbage2)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(3.010f, 1.03f, -0.630f));
        m_transform.SetScale(0.22f);
    }
    else if (m_transType == StaticTransformType::Cabbage3)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(3.270f, 1.03f, -1.630f));
        m_transform.SetScale(0.22f);
    }
    else if (m_key.find("tulipBig") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 1.57f, 0.0f));
        m_transform.SetLocation(glm::vec3(0.75f, 0.87f, 1.83f));
        m_transform.SetScale(0.14f);
    }
    else if (m_transType == StaticTransformType::Test)
    {
#ifdef _DEBUG
        ImGui::DragFloat("rotX ", &rotX, 0.01f);
        ImGui::DragFloat("rotY ", &rotY, 0.01f);
        ImGui::DragFloat("rotZ ", &rotZ, 0.01f);
        ImGui::DragFloat("x ", &x, 0.01f);
        ImGui::DragFloat("y ", &y, 0.01f);
        ImGui::DragFloat("z ", &z, 0.01f);
        ImGui::DragFloat("scale ", &scale, 0.01f);
#endif
        m_transform.SetRotation(glm::vec3(rotX, rotY, rotZ));
        m_transform.SetLocation(glm::vec3(x, y, z));
        m_transform.SetScale(scale);
    }

    UpdateDefaultCB();
}

void Static3DObj::Render()
{
    HDEVICE->m_context->PSSetShaderResources(1, 1, m_texCube1->GetSRV().GetAddressOf());
    m_easyRender.Draw();
}

void Static3DObj::Release() {}
