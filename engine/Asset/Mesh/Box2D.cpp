/*
author : 정찬빈
description : 박스2D 메쉬를 만드는 소스 파일

version: 1.0.0
date: 2024-11-27
*/

#include "pch.h"
#include "Box2D.h"
using namespace HBSoft;

Box2D::Box2D(std::shared_ptr<D3Device> device)
{
    assert(CreateVertices(device));
    assert(CreateIndices(device));
}

bool HBSoft::Box2D::CreateVertices(std::shared_ptr<D3Device>& device)
{
    m_vertices.resize(4);

    m_vertices[0] =
    Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    m_vertices[1] =
    Vertex({-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[2] =
    Vertex({1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[3] =
    Vertex({1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool HBSoft::Box2D::CreateIndices(std::shared_ptr<D3Device>& device)
{
    m_indices.resize(6);

    m_indices.push_back(0);
    m_indices.push_back(1);
    m_indices.push_back(2);
    m_indices.push_back(0);
    m_indices.push_back(2);
    m_indices.push_back(3);

    return device->CreateIndexBuffer(m_indices, m_indexBuffer);
}
