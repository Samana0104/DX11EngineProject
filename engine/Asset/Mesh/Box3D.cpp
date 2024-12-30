/*
author : º¯ÇÑºû
description : 3d ¹Ú½º ¸ðµ¨À» ¸¸µå´Â ¹Ú½º 3d ¼Ò½º ÆÄÀÏ

version: 1.0.4
date: 2024-11-22
*/

#include "pch.h"
#include "Box3D.h"
using namespace HBSoft;

Box3D::Box3D(std::shared_ptr<D3Device> device)
{
#ifdef _DEBUG
    assert(CreateVertices(device));
    assert(CreateIndices(device));
    assert(CreateMaterialBuffer(device));
#else
    CreateVertices(device);
    CreateIndices(device);
    CreateMaterialBuffer(device);
#endif
}

bool Box3D::CreateVertices(std::shared_ptr<D3Device> device)
{
    m_vertices.resize(24);

    // ¾Õ¸é
    m_vertices[0] =
    Vertex({-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[1] =
    Vertex({1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[2] =
    Vertex({1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[3] =
    Vertex({-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // µÞ¸é
    m_vertices[4] =
    Vertex({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[5] =
    Vertex({-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[6] =
    Vertex({-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[7] =
    Vertex({1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // ¿À¸¥ÂÊ
    m_vertices[8] =
    Vertex({1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[9] =
    Vertex({1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[10] =
    Vertex({1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[11] =
    Vertex({1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // ¿ÞÂÊ
    m_vertices[12] =
    Vertex({-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[13] =
    Vertex({-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0});

    m_vertices[14] =
    Vertex({-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[15] =
    Vertex({-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // À­¸é
    m_vertices[16] =
    Vertex({-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[17] =
    Vertex({1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[18] =
    Vertex({1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[19] =
    Vertex({-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // ¾Æ·§¸é
    m_vertices[20] =
    Vertex({-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[21] =
    Vertex({1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[22] =
    Vertex({1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[23] =
    Vertex({-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool Box3D::CreateIndices(std::shared_ptr<D3Device> device)
{
    int iIndex = 0;

    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    subMesh->meshName = "Box3D";

    subMesh->indices.resize(36);

    subMesh->indices[iIndex++] = 0;
    subMesh->indices[iIndex++] = 1;
    subMesh->indices[iIndex++] = 2;
    subMesh->indices[iIndex++] = 0;
    subMesh->indices[iIndex++] = 2;
    subMesh->indices[iIndex++] = 3;
    subMesh->indices[iIndex++] = 4;
    subMesh->indices[iIndex++] = 5;
    subMesh->indices[iIndex++] = 6;
    subMesh->indices[iIndex++] = 4;
    subMesh->indices[iIndex++] = 6;
    subMesh->indices[iIndex++] = 7;
    subMesh->indices[iIndex++] = 8;
    subMesh->indices[iIndex++] = 9;
    subMesh->indices[iIndex++] = 10;
    subMesh->indices[iIndex++] = 8;
    subMesh->indices[iIndex++] = 10;
    subMesh->indices[iIndex++] = 11;
    subMesh->indices[iIndex++] = 12;
    subMesh->indices[iIndex++] = 13;
    subMesh->indices[iIndex++] = 14;
    subMesh->indices[iIndex++] = 12;
    subMesh->indices[iIndex++] = 14;
    subMesh->indices[iIndex++] = 15;
    subMesh->indices[iIndex++] = 16;
    subMesh->indices[iIndex++] = 17;
    subMesh->indices[iIndex++] = 18;
    subMesh->indices[iIndex++] = 16;
    subMesh->indices[iIndex++] = 18;
    subMesh->indices[iIndex++] = 19;
    subMesh->indices[iIndex++] = 20;
    subMesh->indices[iIndex++] = 21;
    subMesh->indices[iIndex++] = 22;
    subMesh->indices[iIndex++] = 20;
    subMesh->indices[iIndex++] = 22;
    subMesh->indices[iIndex++] = 23;

    subMesh->hasTexture = false;

    device->CreateIndexBuffer(subMesh->indices, subMesh->indexBuffer);
    m_subMeshes.push_back(subMesh);

    return true;
}

void Box3D::CreateAutoCollision()
{
    m_autoCollision.aabb.min = vec3(-1.f, -1.f, -1.f);
    m_autoCollision.aabb.max = vec3(1.f, 1.f, 1.f);

    m_autoCollision.sphere.SetRangeFromAABB(m_autoCollision.aabb);
}
