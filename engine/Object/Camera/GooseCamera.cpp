/*
author : 변한빛
description : 거위 따라다니는 카메라 헤더파일

version: 1.0.0
date: 2024-12-30
*/
#include "pch.h"
#include "GooseCamera.h"
using namespace HBSoft;

GooseCamera::GooseCamera()
{
    m_lerpSpeed = 3.f;
    m_movePos   = vec3(0.f);
    m_zoomTimer = 2.f;
    m_zoom      = 90.f;
}

void GooseCamera::Update(const float deltaTime)
{
    if (glm::length(m_movePos - m_transform.m_pos) < 0.001f)
    {
        m_transform.SetLocation(m_movePos);
    }
    else
    {
        m_transform.AddLocation((m_movePos - m_transform.m_pos) * m_lerpSpeed * deltaTime);
    }

    if (HINPUT->IsKeyDown(0x41))
    {
        if (m_zoomTimer >= 1.f && m_zoom > ZOOM_MIN)
        {
            m_isZoomUpDown = false;
            m_zoomTimer    = 0.f;
        }
    }

    if (HINPUT->IsKeyDown(0x53))
    {
        if (m_zoomTimer >= 1.f && m_zoom < ZOOM_MAX)
        {
            m_isZoomUpDown = true;
            m_zoomTimer    = 0.f;
        }
    }

    if (m_zoomTimer < 1.f)
    {
        m_zoomTimer += deltaTime;

        if (m_zoomTimer >= 1.f)
        {
            if (m_isZoomUpDown)
                m_zoom += 20.f;
            else
                m_zoom -= 20.f;

            SetZoom(m_zoom);
        }
        else
        {
            glm::clamp<float>(m_zoomTimer, 0.f, 1.f);

            if (m_isZoomUpDown)
                SetZoom(m_zoom + m_zoomTimer * 20.f);
            else
                SetZoom(m_zoom - m_zoomTimer * 20.f);
        }
    }

    m_viewMat = glm::inverse(m_transform.m_worldMat);
    m_frustum.Set(m_viewMat, m_projMat);
}

void GooseCamera::Move(const vec3 pos)
{
    m_movePos = pos;
}
