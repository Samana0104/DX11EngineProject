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

    AABB carpetRange;
    carpetRange.min = vec3(-560.f, -150.f, -560.f);
    carpetRange.max = vec3(560.f, 400.f, 560.f);
    m_component.AddAABBRange(carpetRange, "picnic");

    Init();
}

void PicnicRug::Update(const float deltaTime)
{
    if (m_previousCarrot != m_numCarrot)
    {
        m_previousCarrot = m_numCarrot;
        EventHandler::GetInstance().Notify(EventList::CARROT_DOWN, this);
    }

    if (m_previousPumpkin != m_numPumpkin)
    {
        m_previousPumpkin = m_numPumpkin;
        EventHandler::GetInstance().Notify(EventList::PUMPKIN_DOWN, this);
    }

    m_numPumpkin = 0;
    m_numCarrot  = 0;
    UpdateDefaultCB();
}

void PicnicRug::Render()
{
    HDEVICE->m_context->PSSetShaderResources(1, 1, m_texCube->GetSRV().GetAddressOf());
    m_easyRender.Draw();
}

void PicnicRug::Init()
{
    m_previousCarrot  = 0;
    m_previousPumpkin = 0;
    m_numCarrot       = 0;
    m_numPumpkin      = 0;
}

void PicnicRug::Release() {}

void PicnicRug::ProcessCollision(std::shared_ptr<Object3D> obj)
{
    if (m_component.IsCollision(obj->m_component))
    {
        for (auto str : m_component.m_collidedAreaNames)
        {
            if (str.find("carrot") != std::string::npos)
            {
                m_numCarrot += 1;
            }
            else if (str.find("pumpkin") != std::string::npos)
            {
                m_numPumpkin += 1;
            }
        }
    }
}
