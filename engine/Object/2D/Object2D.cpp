/*
author : ���Ѻ�
description : 2D������ �׷��� ������Ʈ�� �����ϱ� ���� �ҽ� ����

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
        m_cb0.view = view;
    }
    else
    {
        m_cb0.view = mat4(1.0f);
    }

    m_cb0.world = m_transform.m_worldMat;
    m_easyRender.UpdateVSCB((void*)&m_cb0, sizeof(m_cb0), 0);
}
