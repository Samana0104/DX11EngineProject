/*
author : 변한빛
description : 라인을 그리기 위한 클래스 소스 파일

version: 1.0.8
date: 2024-11-29
*/

#include "pch.h"
#include "LineObj.h"
using namespace HBSoft;

LineObj::LineObj()
{
    m_mesh = MeshFactory::Create(HDEVICE, MeshShape::LINE);
    m_easyRender.SetVSShader(L"LineVertex.hlsl");
    m_easyRender.SetPSShader(L"LinePixel.hlsl");
    m_easyRender.SetTopology(ERTopology::LINE_LIST);
    m_easyRender.SetMesh(m_mesh);
    m_easyRender.SetTexture(nullptr);
}

void LineObj::Render() {}

void LineObj::Update(const float deltaTime)
{
    UpdateDefaultCB();
}

void LineObj::Init() {}

void LineObj::Release() {}

void LineObj::Draw(vec3 start, vec3 end, vec4 color)
{
    Vertex v1, v2;

    v1.p = start;
    v1.c = color;
    v2.p = end;
    v2.c = color;

    m_mesh->SetVertices(HDEVICE, {v1, v2});

    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    m_easyRender.SetEntireState();
    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);
    HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[0]->indexBuffer.Get(),
                                         DXGI_FORMAT_R32_UINT,
                                         0);
    HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[0]->indices.size(), 0, 0);
}
