/*
author : 변한빛
description : 메쉬를 생성 하기 위한 소스 파일

version: 1.1.0
date: 2024-11-20
*/

#pragma once
#include "pch.h"
#include "Mesh/Mesh.h"
#include "Mesh/Box3D.h"
#include "Mesh/Line.h"
#include "Mesh/CubeMap.h"

namespace HBSoft
{
    class MeshFactory
    {
    private:
        inline static UINT m_vertexId = 0;  // 건들지 마세요 외부 모델 불러올 때 최적화용으로 쓰임
        inline static UINT m_subMeshId = 0;  // 건들지 마세요 외부 모델 불러올 때 최적화용으로 쓰임
        inline static UINT m_boneCount = 0;  // 건들지 마세요 외부 모델 불러올 때 최적화용으로 쓰임

    private:
        // 나중에 3DLoadAndSave.h로 옮길 예정
        static void InitMesh(const aiScene* aScene, std::shared_ptr<Mesh>& mesh);
        static void ProcessNode(aiNode* aNode, const aiScene* aScene, std::shared_ptr<Mesh>& mesh);
        static void ProcessMesh(aiMesh* aMesh, const aiScene* aScene, std::shared_ptr<Mesh>& mesh);
        static void UpdateBoneID(aiNode* aNode, std::shared_ptr<Mesh>& mesh);
        static void FindDeformingBones(const aiScene* aScene, std::shared_ptr<Mesh>& mesh);
        static const aiNode* FindParent(const aiNode* aNode, std::shared_ptr<Mesh>& mesh);
        static void          ReadAnimation(const aiScene* scene, std::shared_ptr<Mesh>& mesh);

    public:
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device>& device, const wstringV path);
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device>& device, const MeshShape shape);
        static std::shared_ptr<Mesh> CreateMap(std::shared_ptr<D3Device>& device, const UINT width,
                                               const UINT height);

        static bool IsMeshFormat(const wstringV ext);
    };
}  // namespace HBSoft
