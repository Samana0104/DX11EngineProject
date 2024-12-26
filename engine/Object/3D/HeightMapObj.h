/*
author : ���Ѻ�
description : ���� ���� ������Ʈ ��� ����

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

    // �����Ƽ� �ۺ����� �ٲ�
    class HeightMapObj : public Object3D
    {
    public:
        MapDesc                  m_mapDesc;
        std::shared_ptr<Texture> m_mapTexture;
        std::shared_ptr<Mesh>    m_mesh;
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
