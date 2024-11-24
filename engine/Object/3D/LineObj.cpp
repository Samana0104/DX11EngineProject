/*
author : ���Ѻ�
description : ������ �׸��� ���� Ŭ���� �ҽ� ����

version: 1.0.7
date: 2024-11-12
*/

#include "pch.h"
#include "LineObj.h"
using namespace HBSoft;

LineObj::LineObj()
{
    SetMeshKey(L"LINE");
    SetVSShaderKey(L"LineVertex.hlsl");
    SetPSShaderKey(L"LinePixel.hlsl");
}

void LineObj::Draw(vec3 start, vec3 end, vec4 color)
{
    Vertex v1, v2;

    v1.p = start;
    v1.c = color;
    v2.p = end;
    v2.c = color;

    m_mesh->SetVertices(HDEVICE, {v1, v2});

    UINT pStrides = sizeof(Vertex);  // 1���� ���� ũ��
    UINT pOffsets = 0;               // ���ۿ� ���� �ε���

    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);

    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);
    HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    HDEVICE->m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_indices.size(), 0, 0);
}