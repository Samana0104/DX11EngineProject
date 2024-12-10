/*
author : ���Ѻ�
description : ť�� �� �޽��� ����� �ҽ� ����

version: 1.0.4
date: 2024-11-22
*/

#include "pch.h"
#include "CubeMap.h"
using namespace HBSoft;

CubeMap::CubeMap(std::shared_ptr<D3Device> device)
{
    std::shared_ptr<Mesh> box = std::make_shared<Box3D>(device);

    m_vertices  = box->m_vertices;
    m_subMeshes = box->m_subMeshes;

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
    m_subMeshes[0]->indexBuffer->Release();
    m_subMeshes[0]->meshName = "Cube(Box inverse)";
    return device->CreateIndexBuffer(m_subMeshes[0]->indices, m_subMeshes[0]->indexBuffer);
}
