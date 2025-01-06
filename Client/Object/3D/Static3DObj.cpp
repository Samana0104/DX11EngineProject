/*
author : ������
description : ������ ������Ʈ�� �����ϴ� �ҽ� ����

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

void HBSoft::Static3DObj::SetTransType(TransformType transType)
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
        SetTransType(TransformType::DefaultTrans);
    else if (key.find('#') == 0)
        SetTransType(TransformType::CMTrans);
    else if (key.find('@') == 0)
        SetTransType(TransformType::Test);
    else if (key.find('_') == 0)
        SetTransType(TransformType::UnityTrans);
    else if (key.find('!') == 0)
        SetTransType(TransformType::ConcretePath);
    else if (key.find("StoneHouses") == 0)
        SetTransType(TransformType::FrontHouse);
    else if (key.find("store") == 0)
        SetTransType(TransformType::Store);
    else if (key.find("bollard") == 0)
        SetTransType(TransformType::Bollard);
    else if (key.find("parkcube") == 0)
        SetTransType(TransformType::Parkcube);
    else if (key.find("bench") == 0)
        SetTransType(TransformType::Bench);
    else if (key.find("retainer") == 0)
        SetTransType(TransformType::PondRetainers);
    else if (key.find("singleconcreteblock22") == 0)
        SetTransType(TransformType::Concrete22);
    else if (key.find("bridge") == 0)
        SetTransType(TransformType::Bridge);
    else if (key == "PanterDirltRightLow1.hbs")
        SetTransType(TransformType::DirtRightLow1);
    else if (key == "cabbage0.hbs")
        SetTransType(TransformType::Cabbage0);
    else if (key == "cabbage1.hbs")
        SetTransType(TransformType::Cabbage1);
    else if (key == "cabbage2.hbs")
        SetTransType(TransformType::Cabbage2);
    else if (key == "cabbage3.hbs")
        SetTransType(TransformType::Cabbage3);
    else
        SetTransType(TransformType::GooseGameTrans);

    static int flagSeed    = 0;
    static int flagCarrotL = 0;
    static int flagCarrotR = 0;

    if (key == "_picnicrug.hbs")
    {
        m_easyRender.SetPSShader(L"BasicPS.hlsl");
        m_picnicRugTexture = HASSET->m_textures[L"PicnicRugPattern.png"];
        m_easyRender.SetTexture(m_picnicRugTexture);
    }
    else if (m_key.find("seedling") != std::string::npos)
    {
        m_transform.SetRotation(glm::vec3(0.0f, generateRandomValue(0.0f, 6.28f), 0.0f));
        m_transform.SetLocation(
        glm::vec3(5.01f - 0.55f * flagSeed, generateRandomValue(0.92f, 0.98f), 9.82f));
        m_transform.SetScale(0.09f);
        flagSeed++;
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

void Static3DObj::Update(const float deltaTime)
{
    if (m_transType == TransformType::GooseGameTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
    }
    else if (m_transType == TransformType::CMTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
        m_transform.SetScale({1 / 100.0f, 1 / 100.0f, 1 / 100.0f});
    }
    else if (m_transType == TransformType::UnityTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(12.28f, 0.48f, 11.71f));
        m_transform.SetScale(0.0015f);
    }
    else if (m_transType == TransformType::ConcretePath)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-4.85f, 0.26f, -8.41f));
        m_transform.SetScale(0.86f);
    }
    else if (m_transType == TransformType::FrontHouse)
    {
        m_transform.SetRotation(glm::vec3(1.57f, -0.25f, 0.0f));
        m_transform.SetLocation(glm::vec3(4.9f, 0.0f, 13.5f));
        m_transform.SetScale(1.0f);
    }
    else if (m_transType == TransformType::Store)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.35f, 0.0f));
        m_transform.SetLocation(glm::vec3(-14.2f, -1.8f, -12.65f));
        m_transform.SetScale(1);
    }
    else if (m_transType == TransformType::Bollard || m_transType == TransformType::Parkcube)
    {
        m_transform.SetRotation(glm::vec3(1.57f, -0.1f, 0.0f));
        m_transform.SetLocation(glm::vec3(-5.3f, 0.1f, -6.5f));
        m_transform.SetScale(0.85f);
    }
    else if (m_transType == TransformType::Bench)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.05f, 0.0f));
        m_transform.SetLocation(glm::vec3(-3.55f, 0.4f, -8.6f));
        m_transform.SetScale(0.85f);
    }
    else if (m_transType == TransformType::PondRetainers)
    {
        m_transform.SetRotation(glm::vec3(1.57f, -0.03f, 0.0f));
        m_transform.SetLocation(glm::vec3(-4.2f, 0.0f, -7.39f));
        m_transform.SetScale(0.83f);
    }
    else if (m_transType == TransformType::Concrete22)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.26f, 0.0f));
        m_transform.SetLocation(glm::vec3(0.37f, 0.32f, -10.11f));
        m_transform.SetScale(0.845f);
    }
    else if (m_transType == TransformType::Bridge)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-4.86f, 0.26f, -8.42f));
        m_transform.SetScale(0.86f);
    }
    else if (m_transType == TransformType::DirtRightLow1)
    {
        m_transform.SetRotation(glm::vec3(1.57f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(-6.7f, 0.0f, -12.0f));
        m_transform.SetScale(glm::vec3(1.8f, 1.0f, 1.0f));
    }
    else if (m_transType == TransformType::Cabbage0)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(5.09f, 1.03f, -1.3f));
        m_transform.SetScale(0.22f);
    }
    else if (m_transType == TransformType::Cabbage1)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(4.570f, 1.03f, -0.600f));
        m_transform.SetScale(0.22f);
    }
    else if (m_transType == TransformType::Cabbage2)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(3.010f, 1.03f, -0.630f));
        m_transform.SetScale(0.22f);
    }
    else if (m_transType == TransformType::Cabbage3)
    {
        m_transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
        m_transform.SetLocation(glm::vec3(3.270f, 1.03f, -1.630f));
        m_transform.SetScale(0.22f);
    }
    else if (m_transType == TransformType::Test)
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

void HBSoft::Static3DObj::UpdateLocation(const float deltaTime, float x, float y, float z)
{
    m_transform.SetLocation(glm::vec3(x, y, z));

    UpdateDefaultCB();
}

void Static3DObj::Render()
{
    HDEVICE->m_context->PSSetShaderResources(1, 1, m_texCube1->GetSRV().GetAddressOf());
    m_easyRender.Draw();
}

void Static3DObj::Release() {}
