/*
author : ���Ѻ�
description : ī�޶� �����ϱ� ���� ��� ����

version: 1.0.3
date: 2024-11-29
*/

#pragma once

#include "Core.h"
#include "Observer.h"
#include "Frustum.h"
#include "3D\Transform3D.h"

namespace HBSoft
{
    class Camera : public Observer
    {
    private:
        float m_fov;  // radian angle
        float m_projNear;
        float m_projFar;

        vec3 m_side;  // x
        vec3 m_up;    // y
        vec3 m_look;  // z

        float m_speed = 10.f;
        float m_accel = 10.f;

        mat4 m_projMat;
        mat4 m_viewMat;

    public:
        // ���� ī�޶� ������ �� �ִ� ��ģ ��� ������?
        // ���� �ܾƿ� ���� ��������� ������ �������� ���ÿ�
        Transform3D m_transform;
        Frustum     m_frustum;

    private:
        virtual void OnNotice(EventList event, void* entity);
        // ������ ������ ����� ������� ���� �ٵ� ����Ʈ �������� �־���

    public:
        /*
            param : fov -> fov angle(radian) | projNear -> �ּ� �Ÿ� | projFar -> �ִ� �Ÿ�
            description : fov�� ������ ����
        */
        Camera();
        ~Camera();

        const mat4 GetViewMat() const;
        const mat4 GetProjMat() const;
        const vec3 GetEyePos() const;

        void CreatePerspective(float fov, float projNear, float projFar);
        void CreateOrtho(float projNear, float projFar);

        void ZoomIn(const float scale);
        void ZoomOut(const float scale);

        void LookAt(const vec3 eye, const vec3 target, const vec3 up);
        void Update(const float deltaTime);
    };
}  // namespace HBSoft
