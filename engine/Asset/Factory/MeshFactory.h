/*
author : ���Ѻ�
description : �޽��� ���� �ϱ� ���� �ҽ� ����

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
        inline static UINT m_vertexId = 0;  // �ǵ��� ������ �ܺ� �� �ҷ��� �� ����ȭ������ ����
        inline static UINT m_subMeshId = 0;  // �ǵ��� ������ �ܺ� �� �ҷ��� �� ����ȭ������ ����
        inline static UINT m_boneCount = 0;  // �ǵ��� ������ �ܺ� �� �ҷ��� �� ����ȭ������ ����

    private:
        // ���߿� 3DLoadAndSave.h�� �ű� ����
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
