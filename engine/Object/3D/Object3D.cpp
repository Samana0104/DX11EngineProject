/*
author : 변한빛
description : 3D상으로 그려질 오브젝트를 정의하기 위한 소스 파일

version: 1.0.8
date: 2024-11-29
*/

#include "pch.h"
#include "Object3D.h"
#include "Camera.h"
using namespace HBSoft;

void Object3D::SetLight(std::shared_ptr<DirectionalLight> light)
{
    m_light = light;
}

void Object3D::UpdateDefaultCB()
{
    if (m_camera != nullptr)
    {
        m_vsCB0.view   = m_camera->GetViewMat();
        m_vsCB0.proj   = m_camera->GetProjMat();
        m_psCB0.eyePos = m_camera->GetEyePos();
    }
    else
    {
        m_vsCB0.view = mat4(1.0f);
        m_vsCB0.proj = mat4(1.0f);
    }

    if (m_light != nullptr)
    {
        m_psCB0.lightDir   = m_light->m_dir;
        m_psCB0.lightPower = m_light->m_lightPower;
    }
    else
    {
        m_psCB0.lightDir   = vec3(0.f);
        m_psCB0.lightPower = 1.f;
    }

    m_vsCB0.world       = m_transform.m_worldMat;
    m_vsCB0.normalWorld = glm::transpose(glm::inverse(m_transform.m_worldMat));
    m_easyRender.UpdateVSCB((void*)&m_vsCB0, sizeof(m_vsCB0), 0);
    m_easyRender.UpdatePSCB((void*)&m_psCB0, sizeof(m_psCB0), 0);
}
