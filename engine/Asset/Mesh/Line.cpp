/*
author : 변한빛
description : 라인을 만들기 위한 버텍스 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Line.h"
using namespace HBSoft;

Line::Line(std::shared_ptr<D3Device> device)
    : Mesh(false)
{
    assert(CreateVertices(device));
    assert(CreateIndices(device));
}

bool Line::CreateVertices(std::shared_ptr<D3Device> device)
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

bool Line::CreateIndices(std::shared_ptr<D3Device> device)
{
    m_indices.resize(2);
    int iIndex = 0;

    m_indices[iIndex++] = 0;
    m_indices[iIndex++] = 1;
    return device->CreateIndexBuffer(m_indices, m_indexBuffer);
}
