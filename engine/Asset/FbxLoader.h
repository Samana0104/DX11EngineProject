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
    struct SkinningData
    {
        std::vector<float> weights;
        std::vector<int>   boneIdx;
    };

    class FbxLoader
    {
    private:
        FbxManager*  m_fbxManager;
        FbxImporter* m_fbxImporter;
        FbxScene*    m_fbxScene;

        std::vector<SkinningData> m_skinningData;
        std::vector<FbxMesh*>     m_fbxMeshes;
        std::vector<FbxNode*>     m_fbxNodes;

        int m_vertexIdx;

    private:
        bool InitFbxLoader(const wstringV filePath);
        void ReleaseFbxManager();


        void InitMesh(std::shared_ptr<Mesh> mesh);
        void ProcessNode(FbxNode* fNode, std::shared_ptr<Mesh> mesh);
        bool ProcessBorn(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh);
        void ProcessMesh(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh);

        int        GetSubMaterialPolygonIndex(int polyIdx, FbxLayerElementMaterial* fMaterial);
        FbxVector2 GetUV(FbxLayerElementUV* uvSet, int vertexPosIdx, int vertexUVIdx);
        FbxColor   GetColor(FbxLayerElementVertexColor* vertexColorSet, int vertexPosIdx,
                            int vertexColorIdx);
        FbxVector4 GetNormal(FbxLayerElementNormal* vertexNormalSet, int vertexPosIdx,
                             int vertexNormalIdx);

        void LoadAnimation(std::shared_ptr<Mesh> mesh);

        mat4 ConvertFbxMatToGlmMat(FbxAMatrix& fMat);

    public:
        FbxLoader();
        ~FbxLoader() = default;

        std::shared_ptr<Mesh> Load(std::shared_ptr<D3Device> device, const wstringV filePath);
    };
}  // namespace HBSoft
