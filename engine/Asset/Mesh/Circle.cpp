/*
author : 정찬빈, 변한빛
description : 원을 만드는 소스 파일

version: 1.0.0
date: 2024-11-30
*/

#include "pch.h"
#include "Circle.h"
using namespace HBSoft;

Circle::Circle(std::shared_ptr<D3Device> device)
{
#ifdef _DEBUG
    assert(CreateVertices(device));
    assert(CreateIndices(device));
#else
    CreateVertices(device);
    CreateIndices(device);
#endif
}

bool Circle::CreateVertices(std::shared_ptr<D3Device> device)
{
    m_vertices.push_back(
    {vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec2(0.5f, 0.5f)});

    m_triangles        = 100;
    const float radius = 1.0f;

    for (int i = 0; i <= m_triangles; i++)
    {
        float theta = 2.0f * glm::pi<float>() * i / m_triangles;
        float x     = cosf(theta) * radius;
        float y     = sinf(theta) * radius;

        m_vertices.push_back({vec3(x, y, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec4(1.0f, 1.0f, 1.0f, 1.0f),
                              vec2(0.5f + (x / (2.0f * radius)), 0.5f - (y / (2.0f * radius)))});
    }

    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool Circle::CreateIndices(std::shared_ptr<D3Device> device)
{
    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    subMesh->meshName = "Circle";

    for (int i = 1; i <= m_triangles; i++)
    {
        subMesh->indices.push_back(0);
        subMesh->indices.push_back(i + 1);
        subMesh->indices.push_back(i);
    }

    subMesh->hasTexture = false;

    device->CreateIndexBuffer(subMesh->indices, subMesh->indexBuffer);
    m_subMeshes.push_back(subMesh);

    return true;
}
