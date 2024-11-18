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
        static void ProcessNode(aiNode* node, const aiScene* scene);
        static void ProcessMesh(aiMesh* mesh, const aiScene* scene);

    public:
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device>& device, const wstringV path);
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device>& device, const MeshShape shape);
        static std::shared_ptr<Mesh> CreateMap(std::shared_ptr<D3Device>& device, const UINT width,
                                               const UINT height);

        static bool IsMeshFormat(const wstringV ext);
    };
}  // namespace HBSoft
