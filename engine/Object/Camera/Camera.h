/*
author : 변한빛
description : 카메라를 정의하기 위한 헤더 파일

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
        // 설마 카메라에 스케일 값 주는 미친 사람 없겠지?
        // 줌인 줌아웃 따로 만들었으니 스케일 조정하지 마시오
        Transform3D m_transform;

    public:
        Frustum m_frustum;

    private:
        virtual void OnNotice(EventList event, void* entity);
        // 윈도우 사이즈 변경시 원근행렬 조정 근데 뷰포트 기준으로 둬야함

    public:
        /*
            param : fov -> fov angle(radian) | projNear -> 최소 거리 | projFar -> 최대 거리
            description : fov값 라디안임 주의
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
