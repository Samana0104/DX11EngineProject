/*
author : 변한빛
description : 디버그 카메라를 정의하기 위한 소스 파일

version: 1.0.0
date: 2024-12-30
*/

#include "pch.h"
#include "DebugCamera.h"
using namespace HBSoft;

DebugCamera::DebugCamera()
    : m_speed(10.f), m_accel(10.f)
{}

void DebugCamera::Update(const float deltaTime)
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

void DebugCamera::Move(const vec3 pos)
{
    m_transform.SetLocation(pos);
}
