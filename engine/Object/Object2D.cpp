/*
author : ���Ѻ�
description : 2D������ �׷��� ������Ʈ�� �����ϱ� ���� �ҽ� ����

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Object2D.h"
using namespace HBSoft;

void Object2D::SetImageScale()
{
    vec2 windowSize    = Window::GetInstance().GetWindowSizeVec2();
    vec2 imageSize     = m_manager.m_texture[m_textureKey]->GetTextureSizeVec2();
    vec2 cartesianSize = m_transform.GetCartesianSize();

    m_transform.SetScale((imageSize / windowSize) * cartesianSize);
}

void Object2D::SetColor(const vec4 color)
{
    m_color = color;
}

void Object2D::SetTextureKey(const TEXTURE_KEY key)
{
    m_textureKey = key;
}

void Object2D::SetMeshKey(const MESH_KEY key)
{
    m_meshKey = key;
}

void Object2D::SetShaderKey(const SHADER_KEY key)
{
    m_shaderKey = key;
}

const vec4& Object2D::GetColor() const
{
    return m_color;
}

const MESH_KEY& Object2D::GetMeshKey() const
{
    return m_meshKey;
}

const TEXTURE_KEY& Object2D::GetTextureKey() const
{
    return m_textureKey;
}

const SHADER_KEY& Object2D::GetShaderKey() const
{
    return m_shaderKey;
}

void Object2D::Update(const float _deltaTime) {}

void Object2D::Render()
{
    m_manager.m_shader[m_shaderKey]->SetUpConfiguration();
    m_manager.m_texture[m_textureKey]->Render();
    m_manager.m_mesh[m_meshKey]->Draw(m_transform.GetModelMat(), m_color);
}
