/*
author : ���Ѻ�
description : ť����� �׸��� ���� Ŭ���� �ҽ� ����

version: 1.0.8
date: 2024-11-29
*/

#include "pch.h"
#include "CubeMapObj.h"
using namespace HBSoft;

CubeMapObj::CubeMapObj()
{
    m_texture  = HASSET->m_textures[L"cubeTest.dds"];
    m_cubeMesh = HASSET->m_meshes[L"CUBEMAP"];
    m_vsShader = HASSET->m_shaders[L"CubeVertex.hlsl"];
    m_psShader = HASSET->m_shaders[L"CubePixel.hlsl"];

    m_transform.SetScale({1000.f, 1000.f, 1000.f});
}

void CubeMapObj::Update(const float deltaTime)
{
    UpdateDefaultCB();
}

void CubeMapObj::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1���� ���� ũ��
    UINT pOffsets = 0;               // ���ۿ� ���� �ε���

    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);

    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_cubeMesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);

    // DXGI_FORMAT_R32_UINT�� �ε��� ������ Ÿ���� UINT�� �׷�
    HDEVICE->m_context->IASetIndexBuffer(m_cubeMesh->m_subMeshes[0]->indexBuffer.Get(),
                                         DXGI_FORMAT_R32_UINT,
                                         0);
    HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    HDEVICE->m_context->PSSetShaderResources(0, 1, m_texture->GetSRV().GetAddressOf());


    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());
    HDEVICE->m_context->DrawIndexed((UINT)m_cubeMesh->m_subMeshes[0]->indices.size(), 0, 0);
}

void CubeMapObj::Release() {}

void CubeMapObj::Init() {}
