/*
author : ������, ���Ѻ�
description : 2D���������� ȸ�� ������ �̵��� ǥ���ϱ� ���� Ŭ���� �ҽ� ����

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
    m_worldMat = mat4(1.f);
    CalculateWorldMat();
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

Transform2D& Transform2D::AddRotation(const float angle)
{
    return SetRotation(m_angle + angle);
}

Transform2D& Transform2D::SetRotation(const float angle)
{
    m_angle = angle;
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

const HPoint Transform2D::ConvertScreenToNDC(const HPoint& windowSize, const HPoint& pos)
{
    return {2.f * pos.x / windowSize.x - 1.f, -2.f * pos.y / windowSize.y + 1.f};
}

const HRect Transform2D::ConvertScreenToNDC(const HPoint& windowSize, const HRect& rect)
{
    HPoint p1, p2;
    p1 = HPoint(rect.left, rect.top);
    p2 = HPoint(rect.right, rect.bottom);

    return {ConvertScreenToNDC(windowSize, p1), ConvertScreenToNDC(windowSize, p2)};
}

const HPoint Transform2D::ConvertNDCToScreen(const HPoint& windowSize, const HPoint& pos)
{
    return {(pos.x + 1.f) * 0.5f * windowSize.x, (pos.y - 1.f) * -0.5f * windowSize.y};
}

const HRect Transform2D::ConvertNDCToScreen(const HPoint& windowSize, const HRect& rect)
{
    HPoint p1, p2;
    p1 = HPoint(rect.left, rect.top);
    p2 = HPoint(rect.right, rect.bottom);

    return {ConvertNDCToScreen(windowSize, p1), ConvertNDCToScreen(windowSize, p2)};
}

void Transform2D::CalculateWorldMat()
{
    m_worldMat[0][0] = glm::cos(m_angle);
    m_worldMat[0][1] = glm::sin(m_angle);
    m_worldMat[1][0] = -glm::sin(m_angle);
    m_worldMat[1][1] = glm::cos(m_angle);

    m_worldMat[0] *= m_scale.x;
    m_worldMat[1] *= m_scale.y;

    m_worldMat[2][2] = 1.f;

    m_worldMat[3][0] = m_pos.x;
    m_worldMat[3][1] = m_pos.y;
    m_worldMat[3][2] = 0.f;
    m_worldMat[3][3] = 1.f;
}
