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
    m_worldMat   = glm::mat4(1.0f);
}

Transform3D& Transform3D::AddLocation(const vec3 pos)
{
    SetLocation(m_pos + pos);
    return *this;
}

Transform3D& Transform3D::AddRotation(const vec3 eulerAngle)
{
    SetRotation(m_eulerAngle + eulerAngle);
    return *this;
}

Transform3D& Transform3D::AddScale(const vec3 scale)
{

    SetScale(m_scale + scale);
    return *this;
}

Transform3D& Transform3D::SetLocation(const vec3 pos)
{
    m_pos            = pos;
    m_worldMat[3][0] = pos.x;
    m_worldMat[3][1] = pos.y;
    m_worldMat[3][2] = pos.z;
    return *this;
}

Transform3D& Transform3D::SetRotation(const vec3 eulerAngle)
{
    return *this;
}

Transform3D& Transform3D::SetScale(const vec3 scale)
{
    return *this;
}

const mat4& Transform3D::GetWorldMat() const
{
    return m_worldMat;
}
