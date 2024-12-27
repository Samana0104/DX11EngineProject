/*
author : 정찬빈
description : 그리드 맵 메쉬를 만드는 소스 파일

version: 1.0.4
date: 2024-12-11
*/

#include "pch.h"
#include "Grid.h"

using namespace HBSoft;

Grid::Grid(std::shared_ptr<D3Device> device)
{
    assert(CreateVertices(device));
    assert(CreateIndices(device));
    assert(CreateMaterialBuffer(device));
}

bool Grid::CreateVertices(std::shared_ptr<D3Device> device)
{
    const float dx = width / numSlices;   /// 셀 하나 가로크기
    const float dy = height / numStacks;  /// 셀 하나 세로크기

    vec3 leftBottom = vec3(-0.5f * width, -0.5f * height, 0.0f);  // 시작점


    for (int j = 0; j <= numStacks; j++)
    {
        vec3 stackStartPoint = leftBottom + vec3(0.0f, dy * j, 0.0f);  // 시작점으로부터 셀 크기만큼 이동


        for (int i = 0; i <= numSlices; i++)
        {
            Vertex v;

            v.p = stackStartPoint + vec3(dx * i, 0.0f, 0.0f);

            v.n = vec3(0.0f, 0.0f, 0.0f);
            v.c = vec4(0.0f, 0.0f, 1.0f, 1.0f);
            v.t = vec2(float(i) / numSlices, 1.0f - float(j) / numStacks);  // uv 값

            m_vertices.push_back(v);
        }
    }
    std::cout << m_vertices.size() << std::endl;

    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool Grid::CreateIndices(std::shared_ptr<D3Device> device)
{

    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    subMesh->meshName = "GRID";


    for (int j = 0; j < numStacks; j++)
    {

        const int offset = (numSlices + 1) * j;

        for (int i = 0; i < numSlices; i++)
        {

            // 첫번째 삼각형
            subMesh->indices.push_back(offset + i);  /// 0 1 2 3 4 5
            subMesh->indices.push_back(offset + i + numSlices + 1);
            subMesh->indices.push_back(offset + i + 1 + numSlices + 1);

            // 두 번째 삼각형
            subMesh->indices.push_back(offset + i);
            subMesh->indices.push_back(offset + i + 1 + numSlices + 1);
            subMesh->indices.push_back(offset + i + 1);
        }
    }

    subMesh->hasTexture = false;

    assert(device->CreateIndexBuffer(subMesh->indices, subMesh->indexBuffer));
    m_subMeshes.push_back(subMesh);

    return true;
}
