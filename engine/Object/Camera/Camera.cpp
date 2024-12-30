/*
author : 변한빛
description : 카메라를 정의하기 위한 소스 파일

version: 1.0.3
date: 2024-11-29
*/

#include "pch.h"
#include "Camera/Camera.h"
using namespace HBSoft;

Camera::Camera()
{
    EventHandler::GetInstance().AddEvent(EventList::DEVICE_CHANGE, this);
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

void Camera::CreatePerspective(float fov, float projNear, float projFar)
{
    m_fov      = fov;
    m_projNear = projNear;
    m_projFar  = projFar;

    HPoint windowSize = HWINDOW->GetWindowSize();
    // z 0 ~ 1 원근 행렬을 만들어주는 함수
    m_projMat = glm::perspectiveFovLH_ZO(fov, windowSize.x, windowSize.y, projNear, projFar);
    m_viewMat = mat4(1.f);

    m_side = vec3(1.f, 0.f, 0.f);
    m_up   = vec3(0.f, 1.f, 0.f);
    m_look = vec3(0.f, 0.f, 1.f);
}

void Camera::CreateOrtho(float projNear, float projFar)
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

    m_viewMat = mat4(1.f);
    m_side    = vec3(1.f, 0.f, 0.f);
    m_up      = vec3(0.f, 1.f, 0.f);
    m_look    = vec3(0.f, 0.f, 1.f);
}

void Camera::ZoomIn(const float scale)
{
    HPoint windowSize = HWINDOW->GetWindowSize();
    m_fov             = glm::radians(scale);

    m_projMat = glm::perspectiveFovLH_ZO(m_fov, windowSize.x, windowSize.y, m_projNear, m_projFar);
}

void Camera::ZoomOut(const float scale) {}

void Camera::LookAt(const vec3 eye, const vec3 target, const vec3 up)
{
    m_transform.m_worldMat = glm::lookAtLH(eye, target, up);

    m_side = m_transform.m_worldMat[0];
    m_up   = m_transform.m_worldMat[1];
    m_look = m_transform.m_worldMat[2];

    m_transform.SetLocation(eye);
}

void Camera::Update(const float deltaTime)
{
#ifdef _DEBUG
    ImGui::SliderFloat("Camera speed", &m_speed, 0.f, 300.f);
#endif

    if (HINPUT->IsKeyPressed(87))  // W
        m_transform.AddLocation(m_look * m_speed * deltaTime);

    if (HINPUT->IsKeyPressed(83))  // S
        m_transform.AddLocation(-m_look * m_speed * deltaTime);

    if (HINPUT->IsKeyPressed(68))  // D
        m_transform.AddLocation(m_side * m_speed * deltaTime);

    if (HINPUT->IsKeyPressed(65))  // A
        m_transform.AddLocation(-m_side * m_speed * deltaTime);


    if (HINPUT->IsKeyPressed(VK_RBUTTON))
    {
        HPoint ndc = HINPUT->GetNDCMousePos();

        m_transform.SetRotation({ndc.y * glm::pi<float>(), -ndc.x * glm::two_pi<float>(), 0.f});

        m_side = m_transform.m_worldMat[0];
        m_up   = m_transform.m_worldMat[1];
        m_look = m_transform.m_worldMat[2];
    }

    m_viewMat = glm::inverse(m_transform.m_worldMat);
    m_frustum.Set(m_viewMat, m_projMat);
}

void Camera::OnNotice(EventList event, void* entity) {}
