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
    m_pos      = vec3(0.0f, 0.0f, 0.0f);
    m_scale    = vec3(1.0f, 1.0f, 1.0f);
    m_worldMat = mat4(1.0f);
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
    m_worldMat = glm::rotate(m_worldMat, radian, axis);
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3& axis, const float radian)
{
    m_worldMat = glm::rotate(glm::mat4(1.f), radian, axis);
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3& eulerAngle)
{
    glm::quat rotator;
    glm::mat4 rotateMat;

    rotator.x = sin(eulerAngle.z * 0.5f) * cos(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) -
                cos(eulerAngle.z * 0.5f) * sin(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f);
    rotator.y = cos(eulerAngle.z * 0.5f) * sin(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) +
                sin(eulerAngle.z * 0.5f) * cos(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f);
    rotator.z = cos(eulerAngle.z * 0.5f) * cos(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f) -
                sin(eulerAngle.z * 0.5f) * sin(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f);
    rotator.w = cos(eulerAngle.z * 0.5f) * cos(eulerAngle.x * 0.5f) * cos(eulerAngle.y * 0.5f) +
                sin(eulerAngle.z * 0.5f) * sin(eulerAngle.x * 0.5f) * sin(eulerAngle.y * 0.5f);

    return SetRotation(glm::axis(rotator), 0.f);
}

Transform3D& Transform3D::SetScale(const vec3 scale)
{
    m_scale = scale;
    CalculateWorldMat();

    return *this;
}

void Transform3D::CalculateWorldMat()
{
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

const mat4& Transform3D::GetWorldMat() const
{
    return m_worldMat;
}

const vec3& Transform3D::GetPos() const
{
    return m_pos;
}
