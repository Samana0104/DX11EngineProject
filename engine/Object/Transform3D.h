/*
author : 변한빛
description : 3D공간에서의 회전 스케일 이동을 표현하기 위한 클래스 헤더 파일

version: 1.0.5
date: 2024-11-14
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

        mat4 m_worldMat;

    private:
        void CalculateWorldMat();

    public:
        Transform3D();

        void         InitTransform();
        Transform3D& SetLocation(const vec3 pos);
        Transform3D& AddLocation(const vec3 pos);

        Transform3D& AddRotation(const vec3& axis, const float radian);

        /*
            param : axis -> 회전 축 | radian -> 라디안
            description : 해당 오브젝트를 축 기준으로 라디안 크기만큼 회전
        */
        Transform3D& SetRotation(const vec3& axis, const float radian);
        Transform3D& SetRotation(const vec3& eulerAngle);

        Transform3D& SetScale(const vec3 scale);

        const mat4& GetWorldMat() const;
        const vec3& GetPos() const;
    };
}  // namespace HBSoft
