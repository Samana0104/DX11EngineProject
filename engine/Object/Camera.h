/*
author : 변한빛
description : 카메라를 정의하기 위한 헤더 파일

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
        float m_projFar;  // near에 왜 디파인 걸려있는거야

        vec3 m_side;  // x
        vec3 m_up;    // y
        vec3 m_look;  // z

        float m_speed = 10.f;
        float m_accel = 10.f;

        mat4 m_projMat;
        // 설마 카메라에 스케일 값 주는 미친 사람 없겠지?
        // 줌인 줌아웃 따로 만들었으니 스케일 조정하지 마시오

    private:
        virtual void OnNotice(EventList event, void* entity);
        // 윈도우 사이즈 변경시 원근행렬 조정 근데 뷰포트 기준으로 둬야함

    public:
        /*
            param : fov -> fov angle(radian) | projNear -> 최소 거리 | projFar -> 최대 거리
            description : fov값 라디안임 주의
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
