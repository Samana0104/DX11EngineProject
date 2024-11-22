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
    struct HeightDesc
    {
        UINT               numCols;
        UINT               numRows;
        float              distanceWidth;
        float              distanceHeight;
        std::vector<float> heights;
    };

    class HeightMap : public Mesh
    {
    private:
        bool CreateHeightMap(std::shared_ptr<D3Device>& device, const HeightDesc& desc);

    public:
        HeightMap(std::shared_ptr<D3Device>& device, const HeightDesc& desc);
        ~HeightMap() = default;
    };
}  // namespace HBSoft
