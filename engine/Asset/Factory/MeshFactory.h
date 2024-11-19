/*
author : ���Ѻ�
description : �޽��� ���� �ϱ� ���� �ҽ� ����

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
        inline static UINT m_vertexId = 0;  // �ǵ��� ������ �ܺ� �� �ҷ��� �� ����ȭ������ ����
        inline static UINT m_subMeshId = 0;  // �ǵ��� ������ �ܺ� �� �ҷ��� �� ����ȭ������ ����

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
