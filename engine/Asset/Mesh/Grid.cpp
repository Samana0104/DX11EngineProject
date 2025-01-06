/*
author : ������
description : �׸��� �� �޽��� ����� �ҽ� ����

version: 1.0.4
date: 2024-12-11
*/

#include "pch.h"
#include "Grid.h"

using namespace HBSoft;

Grid::Grid(std::shared_ptr<D3Device> device)
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

bool Grid::CreateVertices(std::shared_ptr<D3Device> device)
{
    const float dx = width / numSlices;   /// �� �ϳ� ����ũ��
    const float dy = height / numStacks;  /// �� �ϳ� ����ũ��

    vec3 leftTop = vec3(-0.5f * width, 0.5f * height, 0.0f);  // ������


    for (int i = 0; i <= numStacks; i++)
    {
        vec3 stackStartPoint = leftTop + vec3(0.0f, -dy * i, 0.0f);  // ���������κ��� �� ũ�⸸ŭ �̵�


        for (int j = 0; j <= numSlices; j++)
        {
            Vertex v;

            v.p = stackStartPoint + vec3(dx * j, 0.0f, 0.0f);

            v.n = vec3(0.0f, 0.0f, 0.0f);
            v.c = vec4(1.0f, 0.0f, 0.0f, 1.0f);
            // v.t = vec2(float(i) / numSlices, 1.0f - float(j) / numStacks);  // uv ��

            m_vertices.push_back(v);
        }
    }
    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool Grid::CreateIndices(std::shared_ptr<D3Device> device)
{

    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    subMesh->meshName = "GRID";


    for (int i = 0; i < numStacks; i++)
    {
        int Row     = (numSlices + 1) * (i);
        int nextRow = (numSlices + 1) * (i + 1);

        for (int j = 0; j < numSlices; j++)
        {
            // ù��° �ﰢ��
            subMesh->indices.push_back(Row + j);
            subMesh->indices.push_back(Row + j + 1);
            subMesh->indices.push_back(nextRow + j + 1);  /// 0 1 2 3 4 5

            // �� ��° �ﰢ��
            subMesh->indices.push_back(Row + j);
            subMesh->indices.push_back(nextRow + j + 1);
            subMesh->indices.push_back(nextRow + j);
        }
    }

    subMesh->hasTexture = false;

    device->CreateIndexBuffer(subMesh->indices, subMesh->indexBuffer);
    m_subMeshes.push_back(subMesh);

    return true;
}
