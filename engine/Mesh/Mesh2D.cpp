/*
author : 변한빛
description : 메쉬의 기본 리소스를 정의하기 위한 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Mesh2D.h"
using namespace HBSoft;

Mesh2D::Mesh2D(MeshShape meshShape)
    : m_meshShape(meshShape)
{}

void Mesh2D::ReserveVertexSize(size_t vertexCount)
{
    if (vertexCount <= 2)
        vertexCount = 3;

    m_vertices.reserve(vertexCount);
    m_uv.reserve(vertexCount);
    m_uv.reserve(vertexCount);
    m_renderVertices.reserve((vertexCount - 2) * 3);  // -> 삼각형 갯수
    m_indices.reserve((vertexCount - 2) * 3);
}

void Mesh2D::AddVertexAndUV(const vec2 vertex, const vec2 uv)
{
    m_vertices.emplace_back(vertex);
    m_uv.emplace_back(uv);
}

void Mesh2D::AddVertexIndex(std::initializer_list<size_t> index)
{
    for (auto idx : index)
    {
        m_indices.emplace_back(idx);
        m_renderVertices.push_back({
            Transform2D::CartesianToNDC(m_vertices[idx]),
            {1.f, 1.f, 1.f, 1.f},
            m_uv[idx]
        });
    }

    m_tempUV = m_uv;
}

void Mesh2D::CreateMesh(const HPoint meshCom)
{
#ifdef _DEBUG
    _ASSERT(CreateVertexBuffer());
#else
    CreateVertexBuffer();
#endif
}

void Mesh2D::SetUVVertex(const size_t uvVertex, const vec2 uv)
{
    try
    {
        m_tempUV.at(uvVertex) = uv;
    }
    catch (std::out_of_range e)
    {
        MessageBoxA(NULL, e.what(), "UV indexing error[Mesh2D]", MB_OK);
    }
}

bool Mesh2D::CreateVertexBuffer()
{
    HRESULT                hr;
    D3D11_BUFFER_DESC      bd = {};
    D3D11_SUBRESOURCE_DATA sd = {};

    bd.ByteWidth = sizeof(Vertex2D) * static_cast<UINT>(m_renderVertices.size());
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    sd.pSysMem = m_renderVertices.data();

    hr = m_device.m_d3dDevice->CreateBuffer(&bd, &sd, m_vertexBuffer.GetAddressOf());

    return SUCCEEDED(hr);
}

void Mesh2D::SetIAVertexBuffer()
{
    UINT StartSlot  = 0;
    UINT NumBuffers = 1;
    UINT pStrides   = sizeof(Vertex2D);  // 1개의 정점 크기
    UINT pOffsets   = 0;                 // 버퍼에 시작 인덱스

    m_device.m_context->IASetVertexBuffers(StartSlot,
                                           NumBuffers,
                                           m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);
}

void Mesh2D::UpdateRenderVertices(const mat3& matrix, const vec4& color)
{
    vec3              dim2ToDim3;
    std::vector<vec2> copyVertices(m_vertices.size());

    for (size_t i = 0; i < m_vertices.size(); i++)
    {
        dim2ToDim3      = vec3({m_vertices[i], 1.f});
        copyVertices[i] = matrix * dim2ToDim3;
    }

    for (size_t i = 0; i < m_indices.size(); i++)
    {
        m_renderVertices[i] = {Transform2D::CartesianToNDC(copyVertices[m_indices[i]]),
                               color,
                               m_tempUV[m_indices[i]]};
    }

    m_device.m_context->UpdateSubresource(m_vertexBuffer.Get(), 0, NULL, m_renderVertices.data(), 0, 0);
}

void Mesh2D::Draw(const mat3& _matrix, const vec4 _color)
{
    UpdateRenderVertices(_matrix, _color);
    SetIAVertexBuffer();
    PostRender();
}

void Mesh2D::PostRender()
{
    m_tempUV = m_uv;  // 원본 UV 복귀
}
