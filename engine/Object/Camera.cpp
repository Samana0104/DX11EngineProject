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
