/*
author : 변한빛
description : 카메라를 정의하기 위한 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Camera.h"
using namespace HBSoft;

const mat3 Camera::GetViewMat() const
{
    return m_transform.GetViewMat();
}

void Camera::ZoomIn(const float scale)
{
    m_transform.AddScale({-scale, -scale});
}

void Camera::ZoomOut(const float scale)
{
    m_transform.AddScale({scale, scale});
}

void Camera::LookAtObject(Object2D& obj)
{
    m_transform.SetLocation(obj.m_transform.GetLocation());
}
