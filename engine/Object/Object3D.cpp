/*
author : 변한빛
description : 3D상으로 그려질 오브젝트를 정의하기 위한 소스 파일

version: 1.0.5
date: 2024-11-11
*/

#include "pch.h"
#include "Object3D.h"
using namespace HBSoft;

void Object3D::Update(const float deltaTime)
{
    m_cb.model = m_transform.m_worldMat;
}

void Object3D::Render()
{
    std::shared_ptr<Mesh> mesh = HASSET->m_meshes[m_meshKey];

    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    HASSET->m_shaders[m_vsShaderKey]->SetConstantBuffer(HDEVICE, (void*)&m_cb, sizeof(m_cb), 0);

    HASSET->m_shaders[m_vsShaderKey]->SetUpToContext(HDEVICE);
    HASSET->m_shaders[m_psShaderKey]->SetUpToContext(HDEVICE);

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


    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());
    // DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼
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

void Object3D::SetMatrix(mat4 viewMat, mat4 projMat)
{
    m_cb.view = viewMat;
    m_cb.proj = projMat;
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
