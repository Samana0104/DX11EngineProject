/*
author : 변한빛
description : 높이 맵의 오브젝트 헤더 파일

version: 1.0.7
date: 2024-11-22
*/

#pragma once

#include "Object3D.h"
#include "Factory/MeshFactory.h"
#include "Texture/Texture.h"

namespace HBSoft
{
    struct FaceInfo
    {
        vec3 normal;
    };

    struct VertexInfo
    {
        std::vector<UINT> faceIndices;
    };

    /*
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
    */

    class HeightMapObj : public Object3D
    {
    private:
        MapDesc                  m_mapDesc;
        std::shared_ptr<Texture> m_heightTexture;
        std::vector<FaceInfo>    m_faceInfo;
        std::vector<VertexInfo>  m_vertexInfo;

    private:
        void LoadMapDesc(const TEXTURE_KEY texKey, float scaleXPerCell, float scaleYPerCell,
                         float scaleZPerCell);

    public:
        HeightMapObj();
        ~HeightMapObj() = default;
    };
}  // namespace HBSoft
