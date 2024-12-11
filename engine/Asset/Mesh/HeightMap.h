/*
author : ���Ѻ�
description :
    ���� ���� ����� ���� �޽� ��� ����
    ��ũ���� ä���� �Ѱ��ָ� ������ش�.

version: 1.0.0
date: 2024-11-22
*/
#pragma once

#include "Mesh\Mesh.h"
#include "Texture\Texture.h"

namespace HBSoft
{
    struct MapDesc
    {
        UINT               numCols;
        UINT               numRows;
        UINT               numFaces;
        float              scaleXPerCell;
        float              scaleYPerCell;
        float              scaleZPerCell;
        std::vector<float> pixelHeight;
    };

    class HeightMap : public Mesh
    {
    private:
        bool CreateVertices(std::shared_ptr<D3Device> device, const MapDesc& desc);
        bool CreateIndices(std::shared_ptr<D3Device> device, const MapDesc& desc);

    public:
        HeightMap(std::shared_ptr<D3Device> device, const MapDesc& desc);
        ~HeightMap() = default;
    };
}  // namespace HBSoft
