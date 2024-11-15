/*
author : 정찬빈
description : 3D공간에서의 회전 스케일 이동을 표현하기 위한 클래스 헤더 파일

version: 1.0.5
date: 2024-11-14
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

Transform3D& Transform3D::SetLocation(const vec3 pos)
{
    m_pos = pos;
    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::AddLocation(const vec3 pos)
{
    SetLocation(m_pos + pos);
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
    quat rotator2;

    rotator2.x = sin(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) * cos(eulerAngle.z * 0.5f) -
                 cos(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f) * sin(eulerAngle.z * 0.5f);
    rotator2.y = cos(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f) * cos(eulerAngle.z * 0.5f) +
                 sin(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) * sin(eulerAngle.z * 0.5f);
    rotator2.z = cos(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) * sin(eulerAngle.z * 0.5f) -
                 sin(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f) * cos(eulerAngle.z * 0.5f);
    rotator2.w = cos(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) * cos(eulerAngle.z * 0.5f) +
                 sin(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f) * sin(eulerAngle.z * 0.5f);

    m_rotator *= rotator2;

    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3& axis, const float radian)
{
    m_rotator = glm::angleAxis(radian, axis);

    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3& eulerAngle)
{
    quat axisX = quat(cos(0.5f * eulerAngle.x), sin(0.5f * eulerAngle.x) * vec3(1.f, 0.f, 0.f));
    quat axisY = quat(cos(0.5f * eulerAngle.y), sin(0.5f * eulerAngle.y) * vec3(0.f, 1.f, 0.f));
    quat axisZ = quat(cos(0.5f * eulerAngle.z), sin(0.5f * eulerAngle.z) * vec3(0.f, 0.f, 1.f));

    // m_rotator.x = sin(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) * cos(eulerAngle.z * 0.5f) -
    //               cos(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f) * sin(eulerAngle.z * 0.5f);
    // m_rotator.y = cos(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f) * cos(eulerAngle.z * 0.5f) +
    //               sin(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) * sin(eulerAngle.z * 0.5f);
    // m_rotator.z = cos(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) * sin(eulerAngle.z * 0.5f) -
    //               sin(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f) * cos(eulerAngle.z * 0.5f);
    // m_rotator.w = cos(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) * cos(eulerAngle.z * 0.5f) +
    //               sin(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f) * sin(eulerAngle.z * 0.5f);

    m_rotator = axisX * axisZ * axisY;

    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::SetScale(const vec3 scale)
{
    m_scale = scale;
    CalculateWorldMat();

    return *this;
}

void Transform3D::CalculateWorldMat()
{
    m_worldMat = glm::transpose(glm::toMat3(m_rotator));

    m_worldMat[0][0] *= m_scale.x;
    m_worldMat[0][1] *= m_scale.x;
    m_worldMat[0][2] *= m_scale.x;

    m_worldMat[1][0] *= m_scale.y;
    m_worldMat[1][1] *= m_scale.y;
    m_worldMat[1][2] *= m_scale.y;

    m_worldMat[2][0] *= m_scale.z;
    m_worldMat[2][1] *= m_scale.z;
    m_worldMat[2][2] *= m_scale.z;

    m_worldMat[3][0] = m_pos.x;
    m_worldMat[3][1] = m_pos.y;
    m_worldMat[3][2] = m_pos.z;
}
