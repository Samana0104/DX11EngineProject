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

bool Box2D::CreateVertices(std::shared_ptr<D3Device>& device)
{
    m_vertices.resize(4);

    m_vertices[0] =
    Vertex({-1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[1] =
    Vertex({1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[2] =
    Vertex({1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[3] =
    Vertex({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool Box2D::CreateIndices(std::shared_ptr<D3Device>& device)
{
    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    subMesh->meshName = "Box2D(Plane)";

    subMesh->indices.push_back(0);
    subMesh->indices.push_back(1);
    subMesh->indices.push_back(2);
    subMesh->indices.push_back(0);
    subMesh->indices.push_back(2);
    subMesh->indices.push_back(3);

    subMesh->hasTexture = false;

    assert(device->CreateIndexBuffer(subMesh->indices, subMesh->indexBuffer));
    m_subMeshes.push_back(subMesh);

    return true;
}
