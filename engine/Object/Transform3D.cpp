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
    m_pos        = vec3(0.0f, 0.0f, 0.0f);
    m_scale      = vec3(1.0f, 1.0f, 1.0f);
    m_eulerAngle = vec3(0.0f, 0.0f, 0.0f);
    m_worldMat   = mat4(1.0f);
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

Transform3D& Transform3D::AddRotation(const vec3 eulerAngle)
{
    SetRotation(eulerAngle + m_eulerAngle);
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3 eulerAngle)
{
    m_eulerAngle = eulerAngle;
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
        https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
        참조
    */
    quat axisX(cos(m_eulerAngle.x * 0.5f), sin(m_eulerAngle.x * 0.5f) * vec3(1.f, 0.f, 0.f));
    quat axisY(cos(m_eulerAngle.y * 0.5f), sin(m_eulerAngle.y * 0.5f) * vec3(0.f, 1.f, 0.f));
    quat axisZ(cos(m_eulerAngle.z * 0.5f), sin(m_eulerAngle.z * 0.5f) * vec3(0.f, 0.f, 1.f));

    quat eulerToQuat = axisX * axisY * axisZ;

    rotateMat[0][0] = 1 - 2 * eulerToQuat.y * eulerToQuat.y - 2 * eulerToQuat.z * eulerToQuat.z;
    rotateMat[0][1] = 2 * eulerToQuat.x * eulerToQuat.y - 2 * eulerToQuat.w * eulerToQuat.z;
    rotateMat[0][2] = 2 * eulerToQuat.x * eulerToQuat.z + 2 * eulerToQuat.w * eulerToQuat.y;

    rotateMat[1][0] = 2 * eulerToQuat.x * eulerToQuat.y + 2 * eulerToQuat.w * eulerToQuat.z;
    rotateMat[1][1] = 1 - 2 * eulerToQuat.x * eulerToQuat.x - 2 * eulerToQuat.z * eulerToQuat.z;
    rotateMat[1][2] = 2 * eulerToQuat.y * eulerToQuat.z - 2 * eulerToQuat.w * eulerToQuat.x;

    rotateMat[2][0] = 2 * eulerToQuat.x * eulerToQuat.z - 2 * eulerToQuat.w * eulerToQuat.y;
    rotateMat[2][1] = 2 * eulerToQuat.y * eulerToQuat.z + 2 * eulerToQuat.w * eulerToQuat.x;
    rotateMat[2][2] = 1 - 2 * eulerToQuat.x * eulerToQuat.x - 2 * eulerToQuat.y * eulerToQuat.y;
    rotateMat       = glm::transpose(rotateMat);

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

const vec3& Transform3D::GetPos() const
{
    return m_pos;
}
