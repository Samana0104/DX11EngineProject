/*
author : 변한빛
description : 2D상으로 그려질 오브젝트를 정의하기 위한 소스 파일

version: 1.0.4
date: 2024-11-30
*/

#include "pch.h"
#include "Object2D.h"
using namespace HBSoft;

void Object2D::Init()
{
    /*SetTextureKey(L"mainui.jpg");*/
    // SetTextureKey(L"mainui.jpg");
    // SetMeshKey(L"BOX2D");
    // SetVSShaderKey(L"VertexShader.hlsl");
    // SetPSShaderKey(L"PixelShader.hlsl");
}

void Object2D::UpdateDefaultCB()
{
    if (m_camera != nullptr)
    {
        mat3 view(1.f);
        view[2]    = m_camera->GetViewMat()[3];
        view[2][2] = 1.f;
        m_cb0.view = view;
    }
    else
    {
        m_cb0.view = mat4(1.0f);
    }

    m_cb0.world = m_transform.m_worldMat;
    m_vsShader->SetConstantBuffer(HDEVICE, (void*)&m_cb0, sizeof(m_cb0), 0);
}

void Object2D::Render()
{
    // UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    // UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    // m_vsShader->SetUpToContext(HDEVICE);
    // m_psShader->SetUpToContext(HDEVICE);

    // HDEVICE->m_context->IASetVertexBuffers(0,
    //                                        1,
    //                                        m_mesh->m_vertexBuffer.GetAddressOf(),
    //                                        &pStrides,
    //                                        &pOffsets);

    //// DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼
    // HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    // HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // HDEVICE->m_context->PSSetShaderResources(0, 1, m_texture->GetSRV().GetAddressOf());


    // HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    // HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());
    // HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_indices.size(), 0, 0);
}
