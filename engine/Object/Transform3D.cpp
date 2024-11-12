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
    m_pos      = vec3(0.0f, 0.0f, 0.0f);
    m_scale    = vec3(1.0f, 1.0f, 1.0f);
    m_rtQuat   = quat(0.0f, 0.0f, 1.0f, 0.f);  // y축 고정
    m_worldMat = mat4(1.0f);
}

Transform3D& Transform3D::SetLocation(const vec3 pos)
{
    m_pos = pos;
    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::AddRotation(const vec3 axis, const float radian)
{
    vec3 normalizedAxis = glm::normalize(axis);

    m_rtQuat = glm::rotate(m_rtQuat, radian, normalizedAxis);

    CalculateWorldMat();
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3 axis, const float radian)
{
    vec3 normalizedAxis = glm::normalize(axis);

    m_rtQuat = quat(glm::cos(radian * 0.5f), glm::sin(radian * 0.5f) * normalizedAxis);

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
    mat3 rotateMat(0.f);

    /*
        https://blog.naver.com/sipack7297/220421092039?viewType=pc
        참조
    */

    rotateMat[0][0] = 1 - 2 * m_rtQuat.y * m_rtQuat.y - 2 * m_rtQuat.z * m_rtQuat.z;
    rotateMat[0][1] = 2 * m_rtQuat.x * m_rtQuat.y - 2 * m_rtQuat.w * m_rtQuat.z;
    rotateMat[0][2] = 2 * m_rtQuat.x * m_rtQuat.z + 2 * m_rtQuat.w * m_rtQuat.y;

    rotateMat[1][0] = 2 * m_rtQuat.x * m_rtQuat.y + 2 * m_rtQuat.w * m_rtQuat.z;
    rotateMat[1][1] = 1 - 2 * m_rtQuat.x * m_rtQuat.x - 2 * m_rtQuat.z * m_rtQuat.z;
    rotateMat[1][2] = 2 * m_rtQuat.y * m_rtQuat.z - 2 * m_rtQuat.w * m_rtQuat.x;

    rotateMat[2][0] = 2 * m_rtQuat.x * m_rtQuat.z - 2 * m_rtQuat.w * m_rtQuat.y;
    rotateMat[2][1] = 2 * m_rtQuat.y * m_rtQuat.z + 2 * m_rtQuat.w * m_rtQuat.x;
    rotateMat[2][2] = 1 - 2 * m_rtQuat.x * m_rtQuat.x - 2 * m_rtQuat.y * m_rtQuat.y;

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
