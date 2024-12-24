/*
author : 변한빛
description : fbx load를 위한 클래스 소스 파일

version: 1.0.0
date: 2024-12-23
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

        AABB m_autoColAABB;
        bool m_isColInitialized;
        // 애니메이션 수 / 본 개수 / 프레임 개수

    private:
        bool InitFbxLoader(const wstringV filePath);
        void ReleaseFbxManager();

        void ProcessNode(FbxNode* fNode, std::shared_ptr<Mesh> mesh, int curIdx, int parentIdx);
        bool ProcessBorn(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh);
        void ProcessMesh(FbxMesh* fMesh, std::shared_ptr<Mesh> mesh);
        void ProcessKeyFrame(std::vector<std::shared_ptr<AnimationClip>>& loadedAni);

        int        GetSubMaterialPolygonIndex(int polyIdx, FbxLayerElementMaterial* fMaterial);
        FbxVector2 GetUV(FbxLayerElementUV* uvSet, int vertexPosIdx, int vertexUVIdx);
        FbxColor   GetColor(FbxLayerElementVertexColor* vertexColorSet, int vertexPosIdx,
                            int vertexColorIdx);
        FbxVector4 GetNormal(FbxLayerElementNormal* vertexNormalSet, int vertexPosIdx,
                             int vertexNormalIdx);
        void       GetMaterial(std::shared_ptr<SubMesh> subMesh, FbxSurfaceMaterial* fMaterial);


        void LoadAnimation(std::shared_ptr<Mesh>                        mesh,
                           std::vector<std::shared_ptr<AnimationClip>>& animations);

        mat4 ConvertFbxMatToGlmMat(FbxAMatrix& fMat);

        /*
            param : vertices -> 버텍스 집합 | compareV -> 비교할 버텍스
            return : vertex index
            description :
               비교할 버텍스가 버텍스 집합에 있는지 확인하고 있다면 버텍스 집합의 인덱스를 반환하고
               그렇지 않다면 NOT_EXISTED_VERTEX를 반환한다.
        */
        int GenBuffer(const std::vector<Vertex>& vertices, const Vertex& compareV);

    public:
        FbxLoader();
        ~FbxLoader() = default;

        void Load(const wstringV filePath, std::shared_ptr<Mesh> loadedMesh,
                  std::vector<std::shared_ptr<AnimationClip>>& loadedAni);
    };
}  // namespace HBSoft
