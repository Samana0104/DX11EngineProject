/*
author : ���Ѻ�
description : ī�޶� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Object3D.h"
#include "Observer.h"

namespace HBSoft
{
    class Camera : public Object3D, Observer
    {
    private:
        float m_fov;  // radian angle
        float m_projNear;
        float m_projFar;  // near�� �� ������ �ɷ��ִ°ž�

        vec3 m_side;  // x
        vec3 m_up;    // y
        vec3 m_look;  // z

        float m_speed = 10.f;
        float m_accel = 10.f;

        mat4 m_projMat;
        // ���� ī�޶� ������ �� �ִ� ��ģ ��� ������?
        // ���� �ܾƿ� ���� ��������� ������ �������� ���ÿ�

    private:
        virtual void OnNotice(EventList event, void* entity);
        // ������ ������ ����� ������� ���� �ٵ� ����Ʈ �������� �־���

    public:
        /*
            param : fov -> fov angle(radian) | projNear -> �ּ� �Ÿ� | projFar -> �ִ� �Ÿ�
            description : fov�� ������ ����
        */
        Camera(float fov, float projNear, float projFar);
        ~Camera();

        const mat4 GetViewMat() const;
        const mat4 GetProjMat() const;
        const vec3 GetEyePos() const;

        void ZoomIn(const float scale);
        void ZoomOut(const float scale);

        void LookAt(const vec3 eye, const vec3 target, const vec3 up);
        void LookAtObject(Object3D& obj);

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft
