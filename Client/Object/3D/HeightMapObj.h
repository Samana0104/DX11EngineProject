/*
author : º¯ÇÑºû
description : ³ôÀÌ ¸ÊÀÇ ¿ÀºêÁ§Æ® Çì´õ ÆÄÀÏ

version: 1.0.8
date: 2024-12-12
*/

#pragma once

#include "3D/Object3D.h"
#include "Factory/MeshFactory.h"
#include "Texture/Texture.h"

namespace HBSoft
{
    struct VertexInfo
    {
        std::vector<UINT> faceIndices;
        vec3              normal;
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

    // ±ÍÂú¾Æ¼­ ÆÛºí¸¯À¸·Î ¹Ù²Þ
    class HeightMapObj : public Object3D
    {
    public:
        MapDesc                  m_mapDesc;
        std::shared_ptr<Texture> m_mapTexture;
        std::shared_ptr<Mesh>    m_mesh;
        std::vector<VertexInfo>  m_vertexInfo;

    private:
        /*
            param : texKey -> ³ôÀÌ¸Ê ÅØ½ºÃÄ Å°
                    scaleXPerCell -> xÃà ±âÁØ ¼¿´ç Å©±â
                    scaleYPerCell -> yÃà ±âÁØ ¼¿´ç Å©±â
                    scaleZPerCell -> zÃà ±âÁØ ¼¿´ç Å©±â
            description :
               ³ôÀÌ ¸Ê ÅØ½ºÃÄ¸¦ °¡Áö°í ¸Ê µð½ºÅ©¸³ÅÍ¸¦ ¸¸µé¾îÁØ´Ù.
        */
        void CreateMapDesc(const TEXTURE_KEY texKey, float scaleXPerCell, float scaleYPerCell,
                           float scaleZPerCell);
        void GenerateVertexNormal();
        void ComputeVertexNormal(UINT vertex);

    public:
        HeightMapObj();
        ~HeightMapObj() = default;

        float GetHeight(vec3 pos);

        virtual void Init() override;
        virtual void Release() override;
        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft
