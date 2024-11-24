/*
author : ���Ѻ�
description : 3D���������� ȸ�� ������ �̵��� ǥ���ϱ� ���� Ŭ���� ��� ����

version: 1.1
date: 2024-11-15
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    class Transform3D
    {
        // �����Ƽ� �ۺ������� �δµ� ���� �ڽ� ������ �Լ� ���ʼ�

    public:
        vec3 m_pos;
        quat m_rotator;
        vec3 m_scale;

        mat4 m_worldMat;

    private:
        void CalculateWorldMat();

    public:
        Transform3D();

        void         InitTransform();
        Transform3D& SetLocation(const vec3 pos);
        Transform3D& AddLocation(const vec3 pos);

        Transform3D& AddRotation(const vec3& axis, const float radian);
        Transform3D& AddRotation(const vec3& euelerAngle);
        /*
            param : axis -> ȸ�� �� | radian -> ����
            description : �ش� ������Ʈ�� �� �������� ���� ũ�⸸ŭ ȸ��
        */
        Transform3D& SetRotation(const vec3& axis, const float radian);
        Transform3D& SetRotation(const vec3& eulerAngle);

        Transform3D& AddScale(const vec3 scale);
        Transform3D& AddScale(const float scale);
        Transform3D& SetScale(const vec3 scale);
        Transform3D& SetScale(const float scale);
    };
}  // namespace HBSoft