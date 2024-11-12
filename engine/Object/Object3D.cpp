/*
author : ���Ѻ�
description : 3D������ �׷��� ������Ʈ�� �����ϱ� ���� �ҽ� ����

version: 1.0.5
date: 2024-11-11
*/

#include "pch.h"
#include "Object3D.h"
using namespace HBSoft;

void Object3D::Update(const float deltaTime)
{
    m_cb.view = glm::mat4(1.f);
    m_cb.proj = glm::perspectiveFovLH_ZO(glm::radians(90.f),
                                         HWINDOW->GetSize().x,
                                         HWINDOW->GetSize().y,
                                         1.f,
                                         10000.f);

    m_transform.SetLocation({0.f, 0.f, 5.f});

    if (HINPUT->IsKeyPressed(VK_F1))
        m_transform.AddRotation({0.f, 0.f, 1.f}, 10 * deltaTime);
    else if (HINPUT->IsKeyPressed(VK_F2))
        m_transform.AddRotation({0.f, 1.f, 0.f}, 10 * deltaTime);
    else if (HINPUT->IsKeyPressed(VK_F3))
        m_transform.AddRotation({1.f, 0.f, 0.f}, 10 * deltaTime);

    m_cb.model = m_transform.GetWorldMat();
    HASSET->m_shaders[m_vsShaderKey]->SetConstantBuffer(HDEVICE, (void*)&m_cb, sizeof(m_cb), 0);
}

void Object3D::Render()
{
    std::shared_ptr<Mesh> mesh = HASSET->m_meshes[m_meshKey];

    std::shared_ptr<Shader> vsShader = HASSET->m_shaders[m_vsShaderKey];
    std::shared_ptr<Shader> psShader = HASSET->m_shaders[m_psShaderKey];

    UINT pStrides = sizeof(Vertex);  // 1���� ���� ũ��
    UINT pOffsets = 0;               // ���ۿ� ���� �ε���

    HDEVICE->m_context->IASetInputLayout(vsShader->GetIALayout().Get());
    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);
    HDEVICE->m_context->IASetIndexBuffer(mesh->m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    HDEVICE->m_context->PSSetShaderResources(0,
                                             1,
                                             HASSET->m_textures[m_textureKey]->GetSRV().GetAddressOf());

    HDEVICE->m_context->VSSetConstantBuffers(
    0,
    1,
    HASSET->m_shaders[m_vsShaderKey]->GetConstantBuffer(0).GetAddressOf());

    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->VSSetShader(vsShader->GetVertexShader().Get(), nullptr, 0);
    HDEVICE->m_context->PSSetShader(psShader->GetPixselShader().Get(), nullptr, 0);
    HDEVICE->m_context->RSSetViewports(1, &HDEVICE->m_viewPort);
    HDEVICE->m_context->RSSetState(HDEVICE->m_rsState.Get());
    HDEVICE->m_context->OMSetDepthStencilState(HDEVICE->m_dsState.Get(), 0);
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());
    // DXGI_FORMAT_R32_UINT�� �ε��� ������ Ÿ���� UINT�� �׷�
    HDEVICE->m_context->DrawIndexed((UINT)mesh->m_indices.size(), 0, 0);
}

void Object3D::SetColor(const vec4 color)
{
    m_color = color;
}

void Object3D::SetTextureKey(const TEXTURE_KEY key)
{
    m_textureKey = key;
}

void Object3D::SetMeshKey(const MESH_KEY key)
{
    m_meshKey = key;
}

void Object3D::SetVSShaderKey(const SHADER_KEY key)
{
    m_vsShaderKey = key;
}

void Object3D::SetPSShaderKey(const SHADER_KEY key)
{
    m_psShaderKey = key;
}

const vec4& Object3D::GetColor() const
{
    return m_color;
}

const MESH_KEY& Object3D::GetMeshKey() const
{
    return m_meshKey;
}

const TEXTURE_KEY& Object3D::GetTextureKey() const
{
    return m_textureKey;
}

const SHADER_KEY& Object3D::GetVSShaderKey() const
{
    return m_vsShaderKey;
}

const SHADER_KEY& Object3D::GetPSShaderKey() const
{
    return m_psShaderKey;
}