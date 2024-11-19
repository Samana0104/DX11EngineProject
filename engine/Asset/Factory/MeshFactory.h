/*
author : 변한빛
description : 메쉬를 생성 하기 위한 소스 파일

version: 1.0.7
date: 2024-11-17
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

    private:
        static void ProcessNode(aiNode* node, const aiScene* scene, std::shared_ptr<Mesh>& mesh);
        static void ProcessMesh(aiMesh* aiMesh, const aiScene* scene, std::shared_ptr<Mesh>& mesh);

    public:
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device>& device, const wstringV path);
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device>& device, const MeshShape shape);
        static std::shared_ptr<Mesh> CreateMap(std::shared_ptr<D3Device>& device, const UINT width,
                                               const UINT height);

        static bool IsMeshFormat(const wstringV ext);
    };
}  // namespace HBSoft
