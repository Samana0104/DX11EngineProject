/*
author : 변한빛
description : 3D상으로 그려질 오브젝트를 정의하기 위한 소스 파일

version: 1.0.5
date: 2024-11-11
*/

#include "pch.h"
#include "Object3D.h"
#include "Camera.h"
using namespace HBSoft;

Object3D::Object3D()
    : m_camera(nullptr)
{
    Init();
}

void Object3D::Init()
{
    SetTextureKey(L"1KGCABK.bmp");
    SetMeshKey(L"BOX3D");
    SetVSShaderKey(L"VertexShader.hlsl");
    SetPSShaderKey(L"PixelShader.hlsl");
}

void Object3D::Release() {}

void Object3D::Update(const float deltaTime)
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
    m_cb0.world    = m_transform.m_worldMat;
    m_cb0.invWorld = glm::inverse(m_transform.m_worldMat);
    m_vsShader->SetConstantBuffer(HDEVICE, (void*)&m_cb0, sizeof(m_cb0), 0);
}

void Object3D::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);

    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);

    // DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼
    HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    HDEVICE->m_context->PSSetShaderResources(0, 1, m_texture->GetSRV().GetAddressOf());


    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());
    HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_indices.size(), 0, 0);
}

void Object3D::SetTextureKey(const TEXTURE_KEY key)
{
    m_texture = HASSET->m_textures[key];
}

void Object3D::SetMeshKey(const MESH_KEY key)
{
    m_mesh = HASSET->m_meshes[key];
}

void Object3D::SetVSShaderKey(const SHADER_KEY key)
{
    m_vsShader = HASSET->m_shaders[key];
}

void Object3D::SetPSShaderKey(const SHADER_KEY key)
{
    m_psShader = HASSET->m_shaders[key];
}

void Object3D::SetCamera(Camera* camera)
{
    if (camera != nullptr)
        m_camera = camera;
}
