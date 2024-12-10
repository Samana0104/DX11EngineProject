/*
author : 변한빛, 이지혁
description(변한빛) : 3D상으로 그려질 오브젝트를 정의하기 위한 소스 파일
description(이지혁) : 조명 연산 코드 추가

version: 1.0.9
date: 2024-12-10
*/

#include "pch.h"
#include "Object3D.h"
#include "Camera.h"
using namespace HBSoft;

void Object3D::UpdateDefaultCB()
{
    if (m_camera != nullptr)
    {
        m_cb0.view = m_camera->GetViewMat();
        m_cb0.proj = m_camera->GetProjMat();
    }
    else
    {
        m_cb0.view = mat4(1.0f);
        m_cb0.proj = mat4(1.0f);
    }
    m_cb0.world       = m_transform.m_worldMat;
    m_cb0.normalWorld = glm::transpose(glm::inverse(m_transform.m_worldMat));


    glm::vec3 vPos = glm::vec3(0.0f, 10.0f, 0.0f);
    glm::mat4 matRotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 transformedPos = matRotation * glm::vec4(vPos, 1.0f);
    glm::vec3 vDir = glm::normalize(glm::vec3(transformedPos));
    m_cb0.m_vLightDir = glm::vec4(-vDir, 0/*(std::cos(HTIMER.GetDeltaTime()) * 0.5f + 0.5f) * 3000.0f*/);
    m_cb0.m_vLightPos = glm::vec4(transformedPos.x, transformedPos.y, transformedPos.z, 1.0f);
    
    m_vsShader->SetConstantBuffer(HDEVICE, (void*)&m_cb0, sizeof(m_cb0), 0);
}
