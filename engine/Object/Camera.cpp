/*
author : 변한빛
description : 카메라를 정의하기 위한 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Camera.h"
using namespace HBSoft;

Camera::Camera(float fov, float projNear, float projFar)
    : m_fov(fov), m_projNear(projNear), m_projFar(projFar)
{
    HPoint windowSize = HWINDOW->GetSize();
    // z 0 ~ 1 원근 행렬을 만들어주는 함수
    m_projMat = glm::perspectiveFovLH_ZO(fov, windowSize.x, windowSize.y, projNear, projFar);

    m_side = vec3(1.f, 0.f, 0.f);
    m_up   = vec3(0.f, 1.f, 0.f);
    m_look = vec3(0.f, 0.f, 1.f);
}

const mat4 Camera::GetViewMat() const
{
    return glm::inverse(m_transform.GetWorldMat());
}

const mat4 Camera::GetProjMat() const
{
    return m_projMat;
}

const vec3 Camera::GetEyePos() const
{
    return m_transform.GetPos();
}

void Camera::ZoomIn(const float scale)
{
    HPoint windowSize = HWINDOW->GetSize();
    m_fov             = glm::radians(scale);

    m_projMat = glm::perspectiveFovLH_ZO(m_fov, windowSize.x, windowSize.y, m_projNear, m_projFar);
}

void Camera::ZoomOut(const float scale) {}

void Camera::LookAt(const vec3 eye, const vec3 target, const vec3 up)
{
    m_transform.SetLocation(eye);
    mat3 rotMat = glm::lookAtLH(eye, target, up);

    m_side = rotMat[0];
    m_up   = rotMat[1];
    m_side = rotMat[2];
}

void Camera::LookAtObject(Object3D& obj) {}

void Camera::Update(const float deltaTime)
{

    if (HINPUT->IsKeyPressed(87))  // W
        m_transform.AddLocation(m_look * 0.01f);
    else if (HINPUT->IsKeyPressed(83))  // S
        m_transform.AddLocation(m_look * -0.01f);
    else if (HINPUT->IsKeyPressed(68))  // D
        m_transform.AddLocation(m_side * 0.01f);
    else if (HINPUT->IsKeyPressed(65))  // A
        m_transform.AddLocation(m_side * -0.01f);
}

void Camera::Render() {}
