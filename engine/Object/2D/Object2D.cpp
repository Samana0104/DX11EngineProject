/*
author : 변한빛
description : 2D상으로 그려질 오브젝트를 정의하기 위한 소스 파일

version: 1.0.4
date: 2024-11-30
*/

#include "pch.h"
#include "Object2D.h"
using namespace HBSoft;

Object2D::Object2D() {}

void Object2D::UpdateDefaultCB()
{
    if (m_camera != nullptr)
    {
        mat3 view(1.f);
        view[2]    = m_camera->GetViewMat()[3];
        view[2][2] = 1.f;
        m_vsCB0.view = view;
    }
    else
    {
        m_vsCB0.view = mat4(1.0f);
    }

    m_vsCB0.world       = m_transform.m_worldMat;
    m_vsCB0.normalWorld = 1.f;
    m_easyRender.UpdateVSCB((void*)&m_vsCB0, sizeof(m_vsCB0), 0);
}
