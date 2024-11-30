/*
author : 변한빛
description : 큐브 맵 메쉬를 만드는 소스 파일

version: 1.0.4
date: 2024-11-22
*/

#include "pch.h"
#include "CubeMap.h"
using namespace HBSoft;

CubeMap::CubeMap(std::shared_ptr<D3Device> device)
{
    std::shared_ptr<Mesh> box = std::make_shared<Box3D>(device);

    m_vertices = box->m_vertices;
    m_indices  = box->m_indices;

    assert(CreateVertices(device));
    assert(CreateIndices(device));
}

bool CubeMap::CreateVertices(std::shared_ptr<D3Device> device)
{
    std::reverse(m_vertices.begin(), m_vertices.end());

    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool CubeMap::CreateIndices(std::shared_ptr<D3Device> device)
{

    return device->CreateIndexBuffer(m_indices, m_indexBuffer);
}
