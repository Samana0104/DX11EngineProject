/*
author : 변한빛
description : 2D공간에서의 회전 스케일 이동을 표현하기 위한 클래스 소스 파일

version: 1.0.0
date: 2024-11-04
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
    m_pos    = {0.f, 0.f};
    m_angle  = 0.f;
    m_scale  = {1.f, 1.f};
    m_trsMat = glm::mat3(1.0f);
}

Transform2D& Transform2D::AddLocation(const vec2 pos)
{
    SetLocation(m_pos + pos);
    return *this;
}

Transform2D& Transform2D::AddRotation(const float angle)
{
    SetRotation(m_angle + angle);
    return *this;
}

Transform2D& Transform2D::AddScale(const vec2 scale)
{
    SetScale(m_scale + scale);
    return *this;
}

Transform2D& Transform2D::AddScaleAsRatio(const float ratio)
{
    SetScale(m_scale * ratio);
    return *this;
}

Transform2D& Transform2D::SetLocation(const vec2 pos)
{
    m_pos          = pos;
    m_trsMat[2][0] = pos.x;
    m_trsMat[2][1] = pos.y;
    return *this;
}

Transform2D& Transform2D::SetRotation(const float angle)
{
    if (glm::abs(angle) >= 360.f)
    {
        // [-360, 360]
        const int angleDivison = glm::abs(static_cast<int>(angle / 360.f));
        m_angle                = angle - static_cast<float>(angleDivison);
    }

    m_angle = angle;
    CalculateScaleRotationMat();
    return *this;
}

Transform2D& Transform2D::SetScale(const vec2 scale)
{
    m_scale = {glm::max(scale.x, 0.f), glm::max(scale.y, 0.f)};
    CalculateScaleRotationMat();
    return *this;
}

const mat3& Transform2D::GetModelMat() const
{
    return m_trsMat;
}

const mat3 Transform2D::GetViewMat() const
{
    return glm::inverse(m_trsMat);
}

const mat3 Transform2D::GetTransposMat() const
{
    mat3 mat(1.f);
    mat[2][0] = m_pos.x;
    mat[2][1] = m_pos.y;

    return mat;
}

const mat3 Transform2D::GetScaleMat() const
{
    mat3 mat(1.f);
    mat[0][0] = m_scale.x;
    mat[1][1] = m_scale.y;
    return mat;
}

const mat3 Transform2D::GetRotationMat() const
{
    mat3  mat(1.f);
    float cos = glm::cos(glm::radians(m_angle));
    float sin = glm::sin(glm::radians(m_angle));

    mat[0][0] = cos;
    mat[0][1] = sin;
    mat[1][0] = -sin;
    mat[1][1] = cos;
    return mat;
}

const vec2& Transform2D::GetLocation() const
{
    return m_pos;
}

const vec2& Transform2D::GetScale() const
{
    return m_scale;
}

float Transform2D::GetAngle() const
{
    return m_angle;
}

Transform2D& Transform2D::operator=(const Transform2D& ref)
{
    vec2  m_pos    = ref.m_pos;
    vec2  m_scale  = ref.m_scale;
    float m_angle  = ref.m_angle;
    mat3  m_trsMat = ref.m_trsMat;

    return *this;
}

void Transform2D::CalculateScaleRotationMat()
{
    float cos = glm::cos(glm::radians(m_angle));
    float sin = glm::sin(glm::radians(m_angle));

    m_trsMat[0][0] = cos * m_scale.x;
    m_trsMat[0][1] = sin * m_scale.x;

    m_trsMat[1][0] = -sin * m_scale.y;
    m_trsMat[1][1] = cos * m_scale.y;
}

vec2 Transform2D::CartesianToNDC(const vec2 pos)
{
    return (pos * 2.f) / m_cartesianSize;
}
