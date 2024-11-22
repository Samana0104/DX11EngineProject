/*
author : ���Ѻ�
description : ���� ���� ����� ���� �޽� �ҽ� ����

version: 1.0.0
date: 2024-11-22
*/

#include "pch.h"
#include "HeightMap.h"
using namespace HBSoft;

HeightMap::HeightMap(std::shared_ptr<D3Device>& device, const HeightDesc& desc)
{
    // ¦���� ���� �ȵ�
    assert(desc.numCols % 2 == 0 || desc.numRows % 2 == 0);
    CreateHeightMap(device, desc);
}

bool HeightMap::CreateHeightMap(std::shared_ptr<D3Device>& device, const HeightDesc& desc)
{
    m_vertices.resize(desc.numCols * desc.numRows);
    Vertex vertex;

    for (UINT i = 0; i < desc.numRows; i++)
    {
        for (UINT j = 0; j < desc.numCols; j++)
        {
            vertex.p.x = (i - (desc.numRows - 1) * 0.5f) * desc.distanceWidth;
            vertex.p.x = (i - (width - 1) * 0.5f) * distanceW;
        }
    }
    return true;
}

// bool HeightMap::CreateIndex(std::shared_ptr<D3Device>& device)
//{
//     return false;
// }
