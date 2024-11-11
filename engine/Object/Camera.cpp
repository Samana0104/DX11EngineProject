/*
author : ���Ѻ�
description : ī�޶� �����ϱ� ���� �ҽ� ����

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Camera.h"
using namespace HBSoft;

Camera::Camera(float fov, float projNear, float projFar) {}

const mat4 Camera::GetViewMat() const
{
    return glm::inverse(m_transform.GetWorldMat());
}

const mat4 Camera::GetProjMat() const
{
    HPoint windowSize = HWINDOW->GetSize();

    // directx�� ���� z 0 ~ 1 ����� ������ִ� �Լ�
    mat4 projMat = glm::perspectiveFovLH_ZO(m_fov, windowSize.x, windowSize.y, m_projNear, m_projFar);
    return projMat;
}

void Camera::ZoomIn(const float scale) {}

void Camera::ZoomOut(const float scale) {}

void Camera::LookAtObject(Object3D& obj) {}
