/*
author : ������
description : 3D���������� ȸ�� ������ �̵��� ǥ���ϱ� ���� Ŭ���� ��� ����

version: 1.0.2
date: 2024-11-08
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    class Transform3D
    {
    private:
        vec3 m_pos;
        vec3 m_scale;
        vec3 m_eulerAngle;
        mat4 m_worldMat;

    public:
        Transform3D();

        void         InitTransform();
        Transform3D& AddLocation(const vec3 pos);
        Transform3D& AddRotation(const vec3 aulerangle);
        Transform3D& AddScale(const vec3 scale);
        Transform3D& SetLocation(const vec3 pos);
        Transform3D& SetRotation(const vec3 eulerangle);
        Transform3D& SetScale(const vec3 scale);

        float GetRoll() const;
        float GetPitch() const;
        float GetYaw() const;
    };
}  // namespace HBSoft
