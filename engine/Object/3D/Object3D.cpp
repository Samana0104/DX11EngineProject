/*
author : ���Ѻ�
description : 3D������ �׷��� ������Ʈ�� �����ϱ� ���� �ҽ� ����

version: 1.0.8
date: 2024-11-29
*/

#include "pch.h"
#include "Object3D.h"
#include "Camera.h"
using namespace HBSoft;

void Object3D::UpdateDefaultCB()
{
    if (m_camera != nullptr)
    {
        m_cb0.view = m_camera->GetViewMat();
        m_cb0.proj = m_camera->GetProjMat();
    }
    else
    {
        m_cb0.view = mat4(1.0f);
        m_cb0.proj = mat4(1.0f);
    }
    m_cb0.world       = m_transform.m_worldMat;
    m_cb0.normalWorld = glm::transpose(glm::inverse(m_transform.m_worldMat));
    m_easyRender.UpdateVSCB((void*)&m_cb0, sizeof(m_cb0), 0);
}
