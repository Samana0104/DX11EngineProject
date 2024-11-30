/*
author : 정찬빈, 변한빛
description : 2D공간에서의 회전 스케일 이동을 표현하기 위한 클래스 소스 파일

version: 1.0.0
date: 2024-11-27
*/

#include "pch.h"
#include "Transform2D.h"
using namespace HBSoft;

Transform2D::Transform2D()
{
    InitTransform();
}

void Transform2D::InitTransform()
{
    m_pos      = vec2(0.f, 0.f);
    m_scale    = vec2(1.f, 1.f);
    m_angle    = 0.f;
    m_worldMat = mat3(1.f);
}

Transform2D& Transform2D::AddLocation(const vec2 pos)
{
    return SetLocation(m_pos + pos);
}

Transform2D& Transform2D::SetLocation(const vec2 pos)
{
    m_pos = pos;
    CalculateWorldMat();
    return *this;
}

Transform2D& Transform2D::SetRotation(const float radian)
{
    m_angle = radian;
    CalculateWorldMat();
    return *this;
}

Transform2D& Transform2D::AddScale(const vec2 scale)
{
    return SetScale(m_scale + scale);
}

Transform2D& Transform2D::AddScale(const float scale)
{
    return SetScale(m_scale + vec2(scale, scale));
}

Transform2D& Transform2D::SetScale(const vec2 scale)
{
    m_scale = scale;
    CalculateWorldMat();
    return *this;
}

Transform2D& Transform2D::SetScale(const float scale)
{
    m_scale = vec2(scale, scale);
    CalculateWorldMat();
    return *this;
}

void Transform2D::CalculateWorldMat()
{
    m_worldMat[0][0] = glm::cos(m_angle);
    m_worldMat[0][1] = glm::sin(m_angle);
    m_worldMat[1][0] = -glm::sin(m_angle);
    m_worldMat[1][1] = glm::cos(m_angle);

    m_worldMat[0] *= m_scale.x;
    m_worldMat[1] *= m_scale.y;

    m_worldMat[2][0] = m_pos.x;
    m_worldMat[2][1] = m_pos.y;
    m_worldMat[2][2] = 1.f;
}
