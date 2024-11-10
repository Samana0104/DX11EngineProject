/*
author : 변한빛
description : 카메라를 정의하기 위한 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Object3D.h"

namespace HBSoft
{
    class Camera : public Object3D
    {
    private:
        float m_fov;
        float m_projNear;
        float m_projFar; // near에 왜 디파인 걸려있는거야

        // 설마 카메라에 스케일 값 주는 미친 사람 없겠지?
        // 줌인 줌아웃 따로 만들었으니 스케일 조정하지 마시오

    public:
        Camera(float fov, float projNear, float projFar);
        const mat4 GetViewMat() const;
        const mat4 GetProjMat() const;

        void ZoomIn(const float scale);
        void ZoomOut(const float scale);

        void LookAtObject(Object3D& obj);
    };
}  // namespace HBSoft
