#include "pch.h"
#include "CubeMap.h"
using namespace HBSoft;

CubeMap::CubeMap(std::shared_ptr<D3Device>& device)
{
    std::shared_ptr<Mesh> box = std::make_shared<Box3D>(device);

    m_vertices = box->m_vertices;
    m_indices  = box->m_indices;

    assert(CreateVertex(device));
    assert(CreateIndex(device));
}

bool CubeMap::CreateVertex(std::shared_ptr<D3Device>& device)
{
    std::reverse(m_vertices.begin(), m_vertices.end());

    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool CubeMap::CreateIndex(std::shared_ptr<D3Device>& device)
{

    return device->CreateIndexBuffer(m_indices, m_indexBuffer);
}
