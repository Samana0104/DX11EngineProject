/*
author : ���Ѻ�
description : ī�޶� �����ϱ� ���� ��� ����

version: 1.0.3
date: 2024-11-29
*/

#pragma once

#include "Core.h"
#include "Observer.h"
#include "Camera/Frustum.h"
#include "3D/Transform3D.h"

namespace HBSoft
{
    enum ProjMode
    {
        PERSPECTIVE = 0,
        ORTHO       = 1,
        NOT         = 2
    };

    class Camera : public Observer
    {
    protected:
        float m_fov;  // radian angle
        float m_projNear;
        float m_projFar;

        vec3 m_side;  // x
        vec3 m_up;    // y
        vec3 m_look;  // z

        float m_yaw;
        float m_pitch;
        float m_roll;

        mat4 m_projMat;
        mat4 m_viewMat;

        ProjMode m_projMode;
        // ���� ī�޶� ������ �� �ִ� ��ģ ��� ������?
        // ���� �ܾƿ� ���� ��������� ������ �������� ���ÿ�
        Transform3D m_transform;

    public:
        Frustum m_frustum;

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

        void SetPerspective(float fov, float projNear, float projFar);
        void SetOrtho(float projNear, float projFar);

        void SetZoom(const float fov);
        void ZoomIn(const float fov);
        void ZoomOut(const float fov);

        void LookAt(const vec3 eye, const vec3 target, const vec3 up);

        virtual void Move(const vec3 pos)          = 0;
        virtual void Update(const float deltaTime) = 0;
    };
}  // namespace HBSoft
