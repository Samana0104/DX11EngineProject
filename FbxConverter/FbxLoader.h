/*
author : ���Ѻ�
description : fbx load�� ���� Ŭ���� �ҽ� ����

version: 1.0.0
date: 2024-11-25
*/

#pragma once

#include "pch.h"
#include "Mesh/Mesh.h"

namespace HBSoft
{
#define MIN_WEIGHT_TOLERANCE 0.0001
#define NOT_EXISTED_VERTEX   -1

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

        std::vector<SkinningData>                   m_skinningData;
        std::vector<FbxMesh*>                       m_fbxMeshes;
        std::vector<FbxNode*>                       m_fbxNodes;
        std::vector<FbxNode*>                       m_fbxBornNodes;
        std::vector<std::vector<std::vector<mat4>>> m_fbxAniMat;
        // �ִϸ��̼� �� / �� ���� / ������ ����

    private:
        bool InitFbxLoader(const wstringV filePath);
        void ReleaseFbxManager();

        void ProcessNode(FbxNode* fNode, std::shared_ptr<Mesh> mesh, int curIdx, int parentIdx);
        bool ProcessBorn(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh);
        void ProcessMesh(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh);

        int        GetSubMaterialPolygonIndex(int polyIdx, FbxLayerElementMaterial* fMaterial);
        FbxVector2 GetUV(FbxLayerElementUV* uvSet, int vertexPosIdx, int vertexUVIdx);
        FbxColor   GetColor(FbxLayerElementVertexColor* vertexColorSet, int vertexPosIdx,
                            int vertexColorIdx);
        FbxVector4 GetNormal(FbxLayerElementNormal* vertexNormalSet, int vertexPosIdx,
                             int vertexNormalIdx);
        void       GetMaterial(std::shared_ptr<SubMesh> subMesh, FbxSurfaceMaterial* fMaterial);


        void LoadAnimation(std::shared_ptr<Mesh> mesh);

        mat4 ConvertFbxMatToGlmMat(FbxAMatrix& fMat);

        /*
            param : vertices -> ���ؽ� ���� | compareV -> ���� ���ؽ�
            return : vertex index
            description :
               ���� ���ؽ��� ���ؽ� ���տ� �ִ��� Ȯ���ϰ� �ִٸ� ���ؽ� ������ �ε����� ��ȯ�ϰ�
               �׷��� �ʴٸ� NOT_EXISTED_VERTEX�� ��ȯ�Ѵ�.
        */
        int GenBuffer(const std::vector<Vertex>& vertices, const Vertex& compareV);

    public:
        FbxLoader();
        ~FbxLoader() = default;

        std::shared_ptr<Mesh> Load(const wstringV filePath);
    };
}  // namespace HBSoft
