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

        UINT m_boneCounter;
        UINT m_vertexIdx;   // 건들지 마세요 외부 모델 불러올 때 최적화용으로 쓰임
        UINT m_subMeshIdx;  // 건들지 마세요 외부 모델 불러올 때 최적화용으로 쓰임
        std::vector<std::vector<float>> m_fbxWeightIndices;
        std::vector<std::vector<UINT>>  m_fbxBoneIndices;
        std::vector<FbxMesh*>           m_fbxSubMeshes;
        std::vector<FbxNode*>           m_fbxBoneNodes;

    private:
        void InitFbxManager();
        void ReleaseFbxManager();

        void     InitMesh(std::shared_ptr<Mesh> mesh);
        void     ProcessNode(FbxNode* fNode, std::shared_ptr<Mesh> mesh);
        FbxNode* FindParentBone(FbxNode* fNode);
        void     ProcessBorn(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh);
        void     ProcessMesh(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh);

        int        GetSubMaterialPolygonIndex(int polyIdx, FbxLayerElementMaterial* fMaterial);
        FbxVector2 GetUV(FbxLayerElementUV* uvSet, int vertexPosIdx, int vertexUVIdx);
        FbxColor   GetColor(FbxLayerElementVertexColor* vertexColorSet, int vertexPosIdx,
                            int vertexColorIdx);
        FbxVector4 GetNormal(FbxLayerElementNormal* vertexNormalSet, int vertexPosIdx,
                             int vertexNormalIdx);

        void LoadNodeAnimation(std::shared_ptr<Mesh> mesh);

        mat4 ConvertFbxMatToGlmMat(FbxAMatrix& fMat);

    public:
        FbxLoader();
        ~FbxLoader() = default;

        std::shared_ptr<Mesh> Load(std::shared_ptr<D3Device> device, const wstringV filePath);
    };
}  // namespace HBSoft
