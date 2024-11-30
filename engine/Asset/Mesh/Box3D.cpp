/*
author : 변한빛
description : 3d 박스 모델을 만드는 박스 3d 소스 파일

version: 1.0.4
date: 2024-11-22
*/

#include "pch.h"
#include "Box3D.h"
using namespace HBSoft;

Box3D::Box3D(std::shared_ptr<D3Device> device)
{
    assert(CreateVertices(device));
    assert(CreateIndices(device));
}

bool Box3D::CreateVertices(std::shared_ptr<D3Device> device)
{
    m_vertices.resize(24);

    // 앞면
    m_vertices[0] =
    Vertex({-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[1] =
    Vertex({1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[2] =
    Vertex({1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[3] =
    Vertex({-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // 뒷면
    m_vertices[4] =
    Vertex({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[5] =
    Vertex({-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[6] =
    Vertex({-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[7] =
    Vertex({1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // 오른쪽
    m_vertices[8] =
    Vertex({1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[9] =
    Vertex({1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[10] =
    Vertex({1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[11] =
    Vertex({1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // 왼쪽
    m_vertices[12] =
    Vertex({-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[13] =
    Vertex({-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0});

    m_vertices[14] =
    Vertex({-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[15] =
    Vertex({-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // 윗면
    m_vertices[16] =
    Vertex({-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

    m_vertices[17] =
    Vertex({1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f});

    m_vertices[18] =
    Vertex({1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

    m_vertices[19] =
    Vertex({-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f});

    // 아랫면
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
    m_indices.resize(36);
    int iIndex = 0;

    m_indices[iIndex++] = 0;
    m_indices[iIndex++] = 1;
    m_indices[iIndex++] = 2;
    m_indices[iIndex++] = 0;
    m_indices[iIndex++] = 2;
    m_indices[iIndex++] = 3;
    m_indices[iIndex++] = 4;
    m_indices[iIndex++] = 5;
    m_indices[iIndex++] = 6;
    m_indices[iIndex++] = 4;
    m_indices[iIndex++] = 6;
    m_indices[iIndex++] = 7;
    m_indices[iIndex++] = 8;
    m_indices[iIndex++] = 9;
    m_indices[iIndex++] = 10;
    m_indices[iIndex++] = 8;
    m_indices[iIndex++] = 10;
    m_indices[iIndex++] = 11;
    m_indices[iIndex++] = 12;
    m_indices[iIndex++] = 13;
    m_indices[iIndex++] = 14;
    m_indices[iIndex++] = 12;
    m_indices[iIndex++] = 14;
    m_indices[iIndex++] = 15;
    m_indices[iIndex++] = 16;
    m_indices[iIndex++] = 17;
    m_indices[iIndex++] = 18;
    m_indices[iIndex++] = 16;
    m_indices[iIndex++] = 18;
    m_indices[iIndex++] = 19;
    m_indices[iIndex++] = 20;
    m_indices[iIndex++] = 21;
    m_indices[iIndex++] = 22;
    m_indices[iIndex++] = 20;
    m_indices[iIndex++] = 22;
    m_indices[iIndex++] = 23;

    return device->CreateIndexBuffer(m_indices, m_indexBuffer);
}
