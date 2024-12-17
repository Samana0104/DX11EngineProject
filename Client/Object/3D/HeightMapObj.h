/*
author : ���Ѻ�
description : ���� ���� ������Ʈ ��� ����

version: 1.0.9
date: 2024-11-25
*/

#pragma once

#include "3D/Object3D.h"
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
        std::shared_ptr<Texture> m_mapTexture;
        std::shared_ptr<Mesh>    m_mesh;
        std::vector<FaceInfo>    m_faceInfo;
        std::vector<VertexInfo>  m_vertexInfo;

    private:
        /*
            param : texKey -> ���̸� �ؽ��� Ű
                    scaleXPerCell -> x�� ���� ���� ũ��
                    scaleYPerCell -> y�� ���� ���� ũ��
                    scaleZPerCell -> z�� ���� ���� ũ��
            description :
               ���� �� �ؽ��ĸ� ������ �� ��ũ���͸� ������ش�.
        */
        void CreateMapDesc(const TEXTURE_KEY texKey, float scaleXPerCell, float scaleYPerCell,
                           float scaleZPerCell);

    public:
        HeightMapObj();
        ~HeightMapObj() = default;

        float        GetHeight(float x, float z);
        virtual void Init() override;

        virtual void Release() override;
        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft
