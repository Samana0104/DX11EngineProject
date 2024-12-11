/*
author : 변한빛
description : fbx load를 위한 클래스 소스 파일

version: 1.0.0
date: 2024-11-25
*/

#pragma once

#include <fbxsdk.h>

#ifdef _DEBUG
    #pragma comment(lib, "debug/fbxsdk/libfbxsdk-md.lib")
    #pragma comment(lib, "debug/fbxsdk/libxml2-md.lib")
    #pragma comment(lib, "debug/fbxsdk/zlib-md.lib")
#else
    #pragma comment(lib, "release/fbxsdk/libfbxsdk-md.lib")
    #pragma comment(lib, "release/fbxsdk/libxml2-md.lib")
    #pragma comment(lib, "release/fbxsdk/zlib-md.lib")
#endif

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
        // 애니메이션 수 / 본 개수 / 프레임 개수

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


        void LoadAnimation(std::shared_ptr<Mesh> mesh);

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

        std::shared_ptr<Mesh> Load(const wstringV filePath);
    };
}  // namespace HBSoft
