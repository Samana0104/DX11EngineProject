#include "pch.h"
#include "Line.h"
using namespace HBSoft;

Line::Line(std::shared_ptr<D3Device>& device)
    : Mesh(false)
{
    assert(CreateVertex(device));
    assert(CreateIndex(device));
}

bool Line::CreateVertex(std::shared_ptr<D3Device>& device)
{
    m_vertices.resize(2);

    m_vertices[0].p = vec3(0.0f, 0.0f, 0.0f);
    m_vertices[0].n = vec3(0.0f, 0.0f, 0.0f);
    m_vertices[0].c = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_vertices[0].t = vec2(0.0f, 0.0f);

    m_vertices[1].p = vec3(0.0f, 0.0f, 1.0f);
    m_vertices[1].n = vec3(0.0f, 0.0f, 0.0f);
    m_vertices[1].c = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_vertices[1].t = vec2(1.0f, 0.0f);
    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool Line::CreateIndex(std::shared_ptr<D3Device>& device)
{
    m_indices.resize(2);
    int iIndex = 0;

    m_indices[iIndex++] = 0;
    m_indices[iIndex++] = 1;
    return device->CreateIndexBuffer(m_indices, m_indexBuffer);
}
