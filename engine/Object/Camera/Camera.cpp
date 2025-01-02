/*
author : ���Ѻ�
description : ī�޶� �����ϱ� ���� �ҽ� ����

version: 1.0.3
date: 2024-11-29
*/

#include "pch.h"
#include "Camera/Camera.h"
using namespace HBSoft;

Camera::Camera()
{
    m_projMode = ProjMode::NOT;
    EventHandler::GetInstance().AddEvent(EventList::DEVICE_CHANGE, this);

    m_viewMat = mat4(1.f);
    m_side    = vec3(1.f, 0.f, 0.f);
    m_up      = vec3(0.f, 1.f, 0.f);
    m_look    = vec3(0.f, 0.f, 1.f);

    m_yaw   = 0.f;
    m_pitch = 0.f;
    m_roll  = 0.f;
}

Camera::~Camera()
{
    EventHandler::GetInstance().DeleteEvent(EventList::DEVICE_CHANGE, this);
}

const mat4 Camera::GetViewMat() const
{
    return m_viewMat;
}

const mat4 Camera::GetProjMat() const
{
    return m_projMat;
}

const vec3 Camera::GetEyePos() const
{
    return m_transform.m_pos;
}

void Camera::SetPerspective(float fov, float projNear, float projFar)
{
    m_fov      = fov;
    m_projNear = projNear;
    m_projFar  = projFar;

    HPoint windowSize = HWINDOW->GetWindowSize();
    // z 0 ~ 1 ���� ����� ������ִ� �Լ�
    m_projMat  = glm::perspectiveFovLH_ZO(fov, windowSize.x, windowSize.y, projNear, projFar);
    m_projMode = ProjMode::PERSPECTIVE;
}

void Camera::SetOrtho(float projNear, float projFar)
{
    HPoint windowSize = HWINDOW->GetWindowSize();
    m_projNear        = projNear;
    m_projFar         = projFar;

    m_projMat = glm::orthoLH_ZO(-windowSize.x * 0.5f,
                                windowSize.x * 0.5f,
                                -windowSize.y * 0.5f,
                                windowSize.y * 0.5f,
                                projNear,
                                projFar);
}

void Camera::SetZoom(const float fov)
{
    HPoint windowSize = HWINDOW->GetWindowSize();
    m_fov             = glm::radians(fov);

    m_projMat = glm::perspectiveFovLH_ZO(m_fov, windowSize.x, windowSize.y, m_projNear, m_projFar);
}

void Camera::ZoomIn(const float fov)
{
    HPoint windowSize  = HWINDOW->GetWindowSize();
    m_fov             += glm::radians(fov);

    m_projMat = glm::perspectiveFovLH_ZO(m_fov, windowSize.x, windowSize.y, m_projNear, m_projFar);
}

void Camera::ZoomOut(const float fov)
{
    HPoint windowSize  = HWINDOW->GetWindowSize();
    m_fov             -= glm::radians(fov);

    m_projMat = glm::perspectiveFovLH_ZO(m_fov, windowSize.x, windowSize.y, m_projNear, m_projFar);
}

void Camera::LookAt(const vec3 eye, const vec3 target, const vec3 up)
{
    m_transform.m_worldMat = glm::lookAtLH(eye, target, up);
    glm::extractEulerAngleXZY(m_transform.m_worldMat, m_pitch, m_roll, m_yaw);
    m_transform.SetLocation(eye);
    m_transform.SetRotation({m_pitch, m_roll, m_yaw});

    m_side = m_viewMat[0];
    m_up   = m_viewMat[1];
    m_look = m_viewMat[2];
}

void Camera::OnNotice(EventList event, void* entity)
{
    if (m_projMode == ProjMode::PERSPECTIVE)
        SetPerspective(m_fov, m_projNear, m_projFar);
}
