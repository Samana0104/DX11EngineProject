/*
author : 변한빛
description :
    높이 맵을 만들기 위한 메쉬 헤더 파일
    디스크립터 채워서 넘겨주면 만들어준다.

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
