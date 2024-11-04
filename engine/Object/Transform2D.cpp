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
    m_location = {0.f, 0.f};
    m_angle    = 0.f;
    m_scale    = {1.f, 1.f};
    m_trsMat   = glm::mat3(1.0f);
}

Transform2D& Transform2D::AddLocation(const vec2 pos)
{
    SetLocation(m_location + pos);
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
    m_location     = pos;
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

void Transform2D::MultiplyToTRSMat(const mat3& mat)
{
    m_trsMat = mat * m_trsMat;
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
    mat[2][0] = m_location.x;
    mat[2][1] = m_location.y;

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
    return m_location;
}

const vec2& Transform2D::GetScale() const
{
    return m_scale;
}

float Transform2D::GetAngle() const
{
    return m_angle;
}

RECT_F Transform2D::GetCartesianRectF() const
{
    return {m_location.x - m_scale.x * 0.5f,
            m_location.y + m_scale.y * 0.5f,
            m_location.x + m_scale.x * 0.5f,
            m_location.y - m_scale.y * 0.5f};
}

RECT_F Transform2D::GetCartesianScaleRectF() const
{
    return {-m_scale.x * 0.5f, m_scale.y * 0.5f, m_scale.x * 0.5f, -m_scale.y * 0.5f};
}

RECT_F Transform2D::GetPixelRectF() const
{
    RECT_F cartesianRect = GetCartesianRectF();
    vec2   leftTop       = CartesianToPixel({cartesianRect.left, cartesianRect.top});
    vec2   rightBottom   = CartesianToPixel({cartesianRect.right, cartesianRect.bottom});

    return {leftTop.x, leftTop.y, rightBottom.x, rightBottom.y};
}

Transform2D* Transform2D::operator->()
{
    return this;
}

Transform2D& Transform2D::operator=(const Transform2D& _ref)
{
    vec2  m_location = _ref.m_location;
    vec2  m_scale    = _ref.m_scale;
    float m_angle    = _ref.m_angle;
    mat3  m_trsMat   = _ref.m_trsMat;

    return *this;
}

void Transform2D::SetCartesianSize(const vec2 _pos)
{
    Transform2D::m_cartesianSize = _pos;
}

vec2 Transform2D::GetCartesianSize()
{
    return m_cartesianSize;
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

vec2 Transform2D::CalculateTRSAsVec(const vec2 pos)
{
    const vec2 scaledVec  = Transform2D::ResizeScale(pos, m_scale);
    const vec2 rotatedVec = Transform2D::RotateAsAngle(scaledVec, m_angle);
    return rotatedVec + m_location;
}

RECT_F Transform2D::CartesianToPixelRect(const RECT_F rect)
{
    vec2 leftTop     = CartesianToPixel({rect.left, rect.top});
    vec2 rightBottom = CartesianToPixel({rect.right, rect.bottom});
    return {leftTop.x, leftTop.y, rightBottom.x, rightBottom.y};
}

vec2 Transform2D::CartesianToNDC(const vec2 pos)
{
    return (pos / m_cartesianSize) * 2.f;
}

vec2 Transform2D::CartesianToPixel(const vec2 pos)
{
    float leftTopX = D3Device::GetInstance().m_viewPort.TopLeftX;
    float leftTopY = D3Device::GetInstance().m_viewPort.TopLeftY;

    const vec2 viewportSize = D3Device::GetInstance().GetViewportSize();

    return {leftTopX + pos.x * viewportSize.x / m_cartesianSize.x + 0.5f * viewportSize.x,
            leftTopY - pos.y * viewportSize.y / m_cartesianSize.y + 0.5f * viewportSize.y};
}

vec2 Transform2D::PixelToCartesian(const vec2 pos)
{
    // pixel to cartesian in Window range
    // -> (Pos.x - Window.X/2,  -Pos.y + Window.Y/2) => [-Window/2, Window/2]
    // -> (Pos.x - Window.X/2,  -Pos.y + Window.Y/2) / Window => [-1, 1]
    // -> (cartesian/2) *((Pos.x - Window.X/2,  -Pos.y + Window.Y/2) / Window) => [-cartesianSize/2,
    // cartesianSize/2]
    /* column major, matrix expression
    [ cartesian/Window(x)		0			-cartesian/2(x)
         0			  cartesian/Window(y)	-cartesian/2(y)
         0						0				1
    */
    // viewport 기준으로 맞춤
    float leftTopX = D3Device::GetInstance().m_viewPort.TopLeftX;
    float leftTopY = D3Device::GetInstance().m_viewPort.TopLeftY;

    const vec2 viewportSize = D3Device::GetInstance().GetViewportSize();

    return {m_cartesianSize.x * (pos.x - leftTopX) / viewportSize.x - m_cartesianSize.x / 2,
            -m_cartesianSize.y * (pos.y - leftTopY) / viewportSize.y + m_cartesianSize.y / 2};
}

vec2 Transform2D::PixelToNDC(const vec2 pos, const vec2 rectSize)
{
    const vec2 normalizedVec = pos / rectSize;
    return {normalizedVec.x * 2.f - 1.f, -(normalizedVec.y * 2.f - 1.f)};
}

vec2 Transform2D::CartesianToPolar(const vec2 pos)
{
    return {glm::length(pos), glm::atan(pos.y / pos.x)};
}

vec2 Transform2D::PolarToCartesian(const vec2 pos)
{
    // _pos = (r,theta)
    return {pos.x * glm::cos(pos.y), pos.x * glm::sin(pos.y)};
}

vec2 Transform2D::RotateAsAngle(const vec2 pos, const float angle)
{
    return RotateAsRadian(pos, glm::radians(angle));
}

vec2 Transform2D::RotateAsRadian(const vec2 pos, const float radian)
{
    return {pos.x * glm::cos(radian) - pos.y * glm::sin(radian),
            pos.x * glm::sin(radian) + pos.y * glm::cos(radian)};
}

vec2 Transform2D::ResizeScale(const vec2 pos, const vec2 scale)
{
    return {pos.x * scale.x, pos.y * scale.y};
}
