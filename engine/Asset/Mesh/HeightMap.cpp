/*
author : 변한빛
description : 높이 맵을 만들기 위한 메쉬 소스 파일

version: 1.0.0
date: 2024-11-22
*/

#include "pch.h"
#include "HeightMap.h"
using namespace HBSoft;

HeightMap::HeightMap(std::shared_ptr<D3Device> device, const MapDesc& desc)
{
#ifdef _DEBUG
    assert(CreateVertices(device, desc));
    assert(CreateIndices(device, desc));
    assert(CreateMaterialBuffer(device));
#else
    CreateVertices(device, desc);
    CreateIndices(device, desc);
    CreateMaterialBuffer(device);
#endif
}

bool HeightMap::CreateVertices(std::shared_ptr<D3Device> device, const MapDesc& desc)
{
    UINT  idx;
    float uvX = 1.f / (desc.numCols - 1.f);
    float uvY = 1.f / (desc.numRows - 1.f);  // for문 생각하면 1.f 빼는게 맞음

    m_vertices.resize(desc.numCols * desc.numRows);

    for (UINT row = 0; row < desc.numRows; row++)
    {
        for (UINT col = 0; col < desc.numCols; col++)
        {
            idx = row * desc.numCols + col;

            m_vertices[idx].p.x = (col - (desc.numCols - 1) * 0.5f) * desc.scaleXPerCell;
            m_vertices[idx].p.y = desc.pixelHeight[idx] * desc.scaleYPerCell;
            m_vertices[idx].p.z = -(row - (desc.numRows - 1) * 0.5f) * desc.scaleZPerCell;

            m_vertices[idx].n = {0.f, 1.f, 0.f};

            m_vertices[idx].c = {1.f, 1.f, 1.f, 1.f};

            m_vertices[idx].t.x = uvX * col;
            m_vertices[idx].t.y = uvY * row;
        }
    }

    return device->CreateVertexBuffer(m_vertices, m_vertexBuffer);
}

bool HeightMap::CreateIndices(std::shared_ptr<D3Device> device, const MapDesc& desc)
{
    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    UINT curIdx = 0;
    UINT nextRow, nextCol;

    subMesh->meshName = "HeightMap";

    subMesh->indices.resize(desc.numFaces * 3);

    for (UINT row = 0; row < desc.numRows - 1; row++)
    {
        for (UINT col = 0; col < desc.numCols - 1; col++)
        {
            nextRow = row + 1;
            nextCol = col + 1;

            /*
                노션 메쉬 생성 기준 123 / 134 형식으로 만듬
            */
            subMesh->indices[curIdx]     = row * desc.numCols + col;
            subMesh->indices[curIdx + 1] = row * desc.numCols + nextCol;
            subMesh->indices[curIdx + 2] = nextRow * desc.numCols + nextCol;

            subMesh->indices[curIdx + 3] = subMesh->indices[curIdx];
            subMesh->indices[curIdx + 4] = subMesh->indices[curIdx + 2];
            subMesh->indices[curIdx + 5] = nextRow * desc.numCols + col;

            curIdx += 6;
        }
    }

    device->CreateIndexBuffer(subMesh->indices, subMesh->indexBuffer);
    m_subMeshes.push_back(subMesh);

    return true;
}
