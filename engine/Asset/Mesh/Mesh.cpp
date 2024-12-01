/*
author : 변한빛
description : 메쉬의 기본 리소스를 정의하기 위한 소스 파일

version: 1.0.0
date: 2024-11-08
*/

#include "pch.h"
#include "Mesh.h"
using namespace HBSoft;

Mesh::Mesh()
    : m_vertexBuffer(nullptr)
{}

void Mesh::SetVertices(std::shared_ptr<D3Device> device, const std::vector<Vertex>& vertices)
{
    m_vertices = vertices;
    UpdateVertices(device);
}

void Mesh::SetVertex(std::shared_ptr<D3Device> device, const Vertex& vertex, const UINT idx)
{
    m_vertices[idx] = vertex;
    UpdateVertices(device);
}

void Mesh::UpdateVertices(std::shared_ptr<D3Device> device)
{
    device->m_context->UpdateSubresource(m_vertexBuffer.Get(), 0, NULL, &m_vertices.at(0), 0, 0);
}
