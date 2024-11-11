/*
author : 정찬빈
description : 3D공간에서의 회전 스케일 이동을 표현하기 위한 클래스 헤더 파일

version: 1.0.2
date: 2024-11-08
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
    m_pos         = vec3(0.0f, 0.0f, 0.0f);
    m_scale       = vec3(1.0f, 1.0f, 1.0f);
    m_rotateAxis  = vec3(0.0f, 0.0f, 0.0f);
    m_worldMat    = glm::mat4(1.0f);
    m_rotateAngle = 0.f;
}

Transform3D& Transform3D::SetLocation(const vec3 pos)
{
    m_pos = pos;
    CalculateWorldMat();
    // m_worldMat[3][0] = pos.x;
    // m_worldMat[3][1] = pos.y;
    // m_worldMat[3][2] = pos.z;
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3 axis, const float radian)
{
    vec3 normalizedAxis = glm::normalize(axis);

    m_rotateAxis  = normalizedAxis;
    m_rotateAngle = radian;

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
    quat qt(glm::cos(m_rotateAngle * 0.5f), glm::sin(m_rotateAngle * 0.5f) * m_rotateAxis);
    mat3 rotateMat(0.f);

    /*
        https://blog.naver.com/sipack7297/220421092039?viewType=pc
        참조
    */
    rotateMat[0][0] = 1 - 2 * qt.y * qt.y - 2 * qt.z * qt.z;
    rotateMat[1][0] = 2 * qt.x * qt.y - 2 * qt.w * qt.z;
    rotateMat[2][0] = 2 * qt.x * qt.z + 2 * qt.w * qt.y;
    rotateMat[0][1] = 2 * qt.x * qt.y + 2 * qt.w * qt.z;
    rotateMat[1][1] = 1 - 2 * qt.x * qt.x - 2 * qt.z * qt.z;
    rotateMat[2][1] = 2 * qt.y * qt.z - 2 * qt.w * qt.x;
    rotateMat[0][2] = 2 * qt.x * qt.z - 2 * qt.w * qt.y;
    rotateMat[1][2] = 2 * qt.y * qt.z + 2 * qt.w * qt.x;
    rotateMat[2][2] = 1 - 2 * qt.x * qt.x - 2 * qt.y * qt.y;

    m_worldMat[0][0] = m_scale.x * rotateMat[0][0];
    m_worldMat[0][1] = m_scale.x * rotateMat[0][1];
    m_worldMat[0][2] = m_scale.x * rotateMat[0][2];

    m_worldMat[1][0] = m_scale.y * rotateMat[1][0];
    m_worldMat[1][1] = m_scale.y * rotateMat[1][1];
    m_worldMat[1][2] = m_scale.y * rotateMat[1][2];

    m_worldMat[2][0] = m_scale.z * rotateMat[2][0];
    m_worldMat[2][1] = m_scale.z * rotateMat[2][1];
    m_worldMat[2][2] = m_scale.z * rotateMat[2][2];

    m_worldMat[3][0] = m_pos.x;
    m_worldMat[3][1] = m_pos.y;
    m_worldMat[3][2] = m_pos.z;
}

const mat4& Transform3D::GetWorldMat() const
{
    return m_worldMat;
}
