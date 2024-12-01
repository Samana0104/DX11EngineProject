/*
author : ������, ���Ѻ�
description : 2D���������� ȸ�� ������ �̵��� ǥ���ϱ� ���� Ŭ���� ��� ����

version: 1.0.0
date: 2024-11-26
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    class Transform2D
    {
    public:
        vec2  m_pos;
        vec2  m_scale;
        float m_angle;  // radian
        mat4  m_worldMat;

    private:
        void CalculateWorldMat();

    public:
        Transform2D();

        void         InitTransform();
        Transform2D& AddLocation(const vec2 pos);
        Transform2D& SetLocation(const vec2 pos);

        Transform2D& AddRotation(const float angle);
        Transform2D& SetRotation(const float angle);

        Transform2D& AddScale(const vec2 scale);
        Transform2D& AddScale(const float scale);

        Transform2D& SetScale(const vec2 scale);
        Transform2D& SetScale(const float scale);

        static HPoint ConvertScreenToNDC(const HPoint& windowSize, const HPoint& pos);
    };

}  // namespace HBSoft
