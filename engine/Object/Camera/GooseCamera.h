/*
author : 변한빛
description : 거위 따라다니는 카메라 헤더파일

version: 1.0.0
date: 2024-12-30
*/
#pragma once

#include "Core.h"
#include "Observer.h"
#include "Camera.h"

namespace HBSoft
{
    class GooseCamera : public Camera
    {
    private:
        vec3  m_movePos;
        float m_lerpSpeed;
        float m_zoom;
        float m_zoomTimer;
        bool  m_isZoomUpDown;

        inline static const float ZOOM_MAX = 110.f;
        inline static const float ZOOM_MIN = 70.f;


    public:
        GooseCamera();

        virtual void Update(const float deltaTime) override;
        virtual void Move(const vec3 pos) override;
    };
}  // namespace HBSoft