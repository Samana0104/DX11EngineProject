/*
author : 변한빛
description : 3D공간에서의 회전 스케일 이동을 표현하기 위한 클래스 헤더 파일

version: 1.1
date: 2024-11-15
*/

#include "pch.h"
#include "Transform3D.h"
using namespace HBSoft;

Transform3D::Transform3D()
{
    InitTransform();
}

void Transform3D::InitTransform()
{
    m_pos      = vec3(0.f, 0.f, 0.f);
    m_scale    = vec3(1.f, 1.f, 1.f);
    m_rotator  = quat(1.f, 0.f, 0.f, 0.f);
    m_worldMat = mat4(1.f);
}

Transform3D& Transform3D::AddLocation(const vec3 pos)
{
    return SetLocation(m_pos + pos);
}

Transform3D& Transform3D::SetLocation(const vec3 pos)
{
    m_pos = pos;
    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::AddRotation(const vec3& axis, const float radian)
{
    m_rotator = glm::rotate(m_rotator, radian, axis);
    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::AddRotation(const vec3& eulerAngle)
{
    quat axisX = quat(cos(0.5f * eulerAngle.x), sin(0.5f * eulerAngle.x) * vec3(1.f, 0.f, 0.f));
    quat axisY = quat(cos(0.5f * eulerAngle.y), sin(0.5f * eulerAngle.y) * vec3(0.f, 1.f, 0.f));
    quat axisZ = quat(cos(0.5f * eulerAngle.z), sin(0.5f * eulerAngle.z) * vec3(0.f, 0.f, 1.f));

    m_rotator *= axisX * axisZ * axisY;

    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3& axis, const float radian)
{
    m_rotator = glm::angleAxis(radian, glm::normalize(axis));

    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3& eulerAngle)
{
    quat axisX = quat(cos(0.5f * eulerAngle.x), sin(0.5f * eulerAngle.x) * vec3(1.f, 0.f, 0.f));
    quat axisY = quat(cos(0.5f * eulerAngle.y), sin(0.5f * eulerAngle.y) * vec3(0.f, 1.f, 0.f));
    quat axisZ = quat(cos(0.5f * eulerAngle.z), sin(0.5f * eulerAngle.z) * vec3(0.f, 0.f, 1.f));

    m_rotator = axisX * axisZ * axisY;

    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::AddScale(const vec3 scale)
{
    return SetScale(m_scale + scale);
}

Transform3D& Transform3D::AddScale(const float scale)
{
    return SetScale(m_scale + vec3(scale, scale, scale));
}

Transform3D& Transform3D::SetScale(const vec3 scale)
{
    m_scale = scale;
    CalculateWorldMat();

    return *this;
}

Transform3D& Transform3D::SetScale(const float scale)
{
    m_scale = vec3(scale, scale, scale);
    return *this;
}

void Transform3D::CalculateWorldMat()
{
    m_worldMat = glm::transpose(glm::toMat3(m_rotator));

    m_worldMat[0] *= m_scale.x;
    m_worldMat[1] *= m_scale.y;
    m_worldMat[2] *= m_scale.z;

    m_worldMat[3][0] = m_pos.x;
    m_worldMat[3][1] = m_pos.y;
    m_worldMat[3][2] = m_pos.z;
}
