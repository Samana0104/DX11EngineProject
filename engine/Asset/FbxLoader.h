/*
author : 변한빛
description : fbx load를 위한 클래스 소스 파일

version: 1.0.0
date: 2024-11-25
*/

#pragma once

#include "Mesh/Mesh.h"

namespace HBSoft
{
    class FbxLoader
    {
    private:
        FbxManager*  m_fbxManager;
        FbxImporter* m_fbxImporter;
        FbxScene*    m_fbxScene;

        UINT m_vertexIdx;   // 건들지 마세요 외부 모델 불러올 때 최적화용으로 쓰임
        UINT m_subMeshIdx;  // 건들지 마세요 외부 모델 불러올 때 최적화용으로 쓰임
        std::vector<FbxMesh*> m_subMeshes;
        std::vector<FbxNode*> m_subNodes;

    private:
        void InitFbxManager();
        void ReleaseFbxManager();

        void InitMesh(std::shared_ptr<Mesh> mesh);
        void ProcessNode(FbxNode* fNode);
        void ProcessMesh(FbxMesh* fMesh, FbxNode* fNode, std::shared_ptr<Mesh> mesh);

        int        GetSubMaterialPolygonIndex(int polyIdx, FbxLayerElementMaterial* fMaterial);
        FbxVector2 GetUV(FbxLayerElementUV* uvSet, int vertexPosIdx, int vertexUVIdx);
        FbxColor   GetColor(FbxLayerElementVertexColor* vertexColorSet, int vertexPosIdx,
                            int vertexColorIdx);
        FbxVector4 GetNormal(FbxLayerElementNormal* vertexNormalSet, int vertexPosIdx,
                             int vertexNormalIdx);

    public:
        FbxLoader();
        ~FbxLoader() = default;

        std::shared_ptr<Mesh> Load(std::shared_ptr<D3Device> device, const wstringV filePath);
    };
}  // namespace HBSoft
