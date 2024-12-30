/*
author : ������
description : ������ ������Ʈ�� �����ϴ� �ҽ� ����

version: 1.1.0
date: 2024-12-23
*/
#include "pch.h"
#include "Static3DObj.h"
#include "Camera.h"

using namespace HBSoft;

Static3DObj::Static3DObj()
{
    m_easyRender.SetVSShader(L"BasicVS.hlsl");
    m_easyRender.SetPSShader(L"ColorPS.hlsl");
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

Transform3D HBSoft::Static3DObj::GetTransform()
{
    return m_transform;
}

void Static3DObj::Update(const float deltaTime)
{
    if (m_transType == TransformType::GooseGameTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0, 0));
        m_transform.SetLocation(glm::vec3(-7, 0, -12));
    }
    else if (m_transType == TransformType::CMTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0, 0));
        m_transform.SetLocation(glm::vec3(-7.0f, 0.0f, -12.0f));
        m_transform.SetScale({1 / 100.0f, 1 / 100.0f, 1 / 100.0f});
    }
    else if (m_transType == TransformType::UnityTrans)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0, 0));
        m_transform.SetLocation(glm::vec3(12.28f, 0.48f, 11.71f));
        m_transform.SetScale(0.0015);
    }
    else if (m_transType == TransformType::ConcretePath)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0, 0));
        m_transform.SetLocation(glm::vec3(-4.85, 0.26, -8.41));
        m_transform.SetScale(0.86);
    }
    else if (m_transType == TransformType::FrontHouse)
    {
        m_transform.SetRotation(glm::vec3(1.57, -0.25, 0));
        m_transform.SetLocation(glm::vec3(4.9, 0, 13.5));
        m_transform.SetScale(1);
    }
    else if (m_transType == TransformType::Store)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0.35, 0));
        m_transform.SetLocation(glm::vec3(-14.2, -1.8, -12.65));
        m_transform.SetScale(1);
    }
    else if (m_transType == TransformType::Bollard || m_transType == TransformType::Parkcube)
    {
        m_transform.SetRotation(glm::vec3(1.57, -0.1, 0));
        m_transform.SetLocation(glm::vec3(-5.3, 0.1, -6.5));
        m_transform.SetScale(0.85);
    }
    else if (m_transType == TransformType::Bench)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0.05, 0));
        m_transform.SetLocation(glm::vec3(-3.55, 0.4, -8.6));
        m_transform.SetScale(0.85);
    }
    else if (m_transType == TransformType::PondRetainers)
    {
        m_transform.SetRotation(glm::vec3(1.57, -0.03, 0));
        m_transform.SetLocation(glm::vec3(-4.2, 0, -7.39));
        m_transform.SetScale(0.83);
    }
    else if (m_transType == TransformType::Concrete22)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0.26, 0));
        m_transform.SetLocation(glm::vec3(0.37, 0.32, -10.11));
        m_transform.SetScale(0.845);
    }
    else if (m_transType == TransformType::Bridge)
    {
        m_transform.SetRotation(glm::vec3(1.57, 0, 0));
        m_transform.SetLocation(glm::vec3(-4.86, 0.26, -8.42));
        m_transform.SetScale(0.86);
    }
    else if (m_transType == TransformType::Picnicrug)
    {
       /* m_transform.SetRotation(glm::vec3(1.57, 0.21, 0));
        m_transform.SetLocation(glm::vec3(0.37, 0.2, -11.59));
        m_transform.SetScale(0.85);*/
    }

    else if (m_transType == TransformType::Test)
    {
        ImGui::DragFloat("x ", &x, 0.01f);
        ImGui::DragFloat("y ", &y, 0.01f);
        ImGui::DragFloat("z ", &z, 0.01f);
        ImGui::DragFloat("rotX ", &rotX, 0.01f);
        ImGui::DragFloat("rotY ", &rotY, 0.01f);
        ImGui::DragFloat("rotZ ", &rotZ, 0.01f);
        ImGui::DragFloat("scale ", &scale, 0.01f);
        m_transform.SetRotation(glm::vec3(rotX, rotY, rotZ));
        m_transform.SetLocation(glm::vec3(x, y, z));
        m_transform.SetScale(scale);
       // m_transform.SetLocation(glm::vec3(-7, 0.5, -12));
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
    m_easyRender.Draw();
}

void Static3DObj::Init() {}

void Static3DObj::Init(const std::wstring& key)
{
    m_mesh = HASSET->m_meshes[key];

    m_easyRender.SetVSShader(L"BasicVS.hlsl");
    m_easyRender.SetPSShader(L"ColorPS.hlsl");
    m_easyRender.SetTexture(nullptr);
    if (key == L"_picnicruggg.hbs")
    {
        m_easyRender.SetPSShader(L"BasicPS.hlsl");
        m_picnicRugTexture = HASSET->m_textures[L"PicnicRugPattern.png"];
        m_easyRender.SetTexture(m_picnicRugTexture);
    }
    m_easyRender.SetMesh(m_mesh);
}

void Static3DObj::Release() {}
