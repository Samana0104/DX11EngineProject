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
        quat m_rtQuat;
        mat4 m_worldMat;

    private:
        void CalculateWorldMat();

    public:
        Transform3D();

        void         InitTransform();
        Transform3D& SetLocation(const vec3 pos);

        Transform3D& AddRotation(const vec3 axis, const float radian);

        /*
            param : axis -> ȸ�� �� | radian -> ȸ�� �� ���� ��
            description : �ش� ������Ʈ�� ȸ�� �� ��������
        */
        Transform3D& SetRotation(const vec3 axis, const float radian);

        Transform3D& SetScale(const vec3 scale);

        const mat4& GetWorldMat() const;

        float GetRoll() const;
        float GetPitch() const;
        float GetYaw() const;
    };
}  // namespace HBSoft
