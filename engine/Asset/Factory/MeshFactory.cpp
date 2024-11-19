/*
author : ���Ѻ�
description : �޽��� ���� �ϱ� ���� �ҽ� ����

version: 1.1.0
date: 2024-11-19
*/

#include "pch.h"
#include "MeshFactory.h"
using namespace HBSoft;

void MeshFactory::ProcessNode(aiNode* aiNode, const aiScene* aiScene, std::shared_ptr<Mesh>& mesh)
{
    auto a = aiNode->mTransformation;

    for (UINT i = 0; i < aiNode->mNumMeshes; i++)
    {
        aiMesh* aiMesh = aiScene->mMeshes[aiNode->mMeshes[i]];
        ProcessMesh(aiMesh, aiScene, mesh);
    }

    for (UINT i = 0; i < aiNode->mNumChildren; i++)
    {
        ProcessNode(aiNode->mChildren[i], aiScene, mesh);
    }
}

void MeshFactory::ProcessMesh(aiMesh* aiMesh, const aiScene* aiScene, std::shared_ptr<Mesh>& mesh)
{
    UINT meshIndicesNums = 0;
    UINT i               = 0;

    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    // �޽� �̸� �ҷ���
    subMesh->meshName = aiMesh->mName.C_Str();

    // �ε��� ���� �ҷ���
    for (i = 0; i < aiMesh->mNumFaces; i++)
    {
        meshIndicesNums += aiMesh->mFaces[i].mNumIndices;
    }

    // �ε��� ������ŭ ��������
    subMesh->indices.resize(meshIndicesNums);


    // �ε��� ��ȣ�� �´� ��ġ�� ����
    // vertexId�� �ִ� ������ �ϳ��� ���ؽ� ������ ���� �ڴµ� ���� �޽�����
    // �ε��� ��ȣ�� �ߺ��� �ֱ� ������ ���ؽ� ��ȣ�� ���� ������
    for (i = 0; i < aiMesh->mNumFaces; i++)
    {
        aiFace face = aiMesh->mFaces[i];

        for (UINT j = 0; j < face.mNumIndices; j++)
            subMesh->indices[face.mNumIndices * i + j] = face.mIndices[j] + m_vertexId;
    }

    // ���ؽ� ��ȣ�� �´� ��ġ�� ����
    for (i = 0; i < aiMesh->mNumVertices; i++)
    {
        // ��ġ ����
        mesh->m_vertices[m_vertexId + i].p.x = aiMesh->mVertices[i].x;
        mesh->m_vertices[m_vertexId + i].p.y = aiMesh->mVertices[i].y;
        mesh->m_vertices[m_vertexId + i].p.z = aiMesh->mVertices[i].z;

        // �븻 ���� (�븻�� �����ϴ� ���)
        if (aiMesh->HasNormals())
        {
            mesh->m_vertices[m_vertexId + i].n.x = aiMesh->mNormals[i].x;
            mesh->m_vertices[m_vertexId + i].n.y = aiMesh->mNormals[i].y;
            mesh->m_vertices[m_vertexId + i].n.z = aiMesh->mNormals[i].z;
            mesh->m_vertices[m_vertexId + i].n   = glm::normalize(mesh->m_vertices[i].n);
        }

        // �ؽ�ó ��ǥ (ù ��° UV ä���� �ִ� ���)
        if (aiMesh->HasTextureCoords(0))
        {
            mesh->m_vertices[m_vertexId + i].t.x = aiMesh->mTextureCoords[0][i].x;
            mesh->m_vertices[m_vertexId + i].t.y = aiMesh->mTextureCoords[0][i].y;
        }
        else
        {
            mesh->m_vertices[m_vertexId + i].t = vec2(0.0f);  // �ؽ�ó ��ǥ�� ���� �� �⺻��
        }

        // �÷� ������ ������
        if (aiMesh->HasVertexColors(0))
        {
            mesh->m_vertices[m_vertexId + i].c.r = aiMesh->mColors[0][i].r;
            mesh->m_vertices[m_vertexId + i].c.g = aiMesh->mColors[0][i].g;
            mesh->m_vertices[m_vertexId + i].c.b = aiMesh->mColors[0][i].b;
            mesh->m_vertices[m_vertexId + i].c.a = aiMesh->mColors[0][i].a;
        }
        else
        {
            mesh->m_vertices[m_vertexId + i].c = vec4(1.f);
        }
    }

    // ���ؽ� ���̵�� �߰��� ���ؽ���ŭ ������� ���� ����޽��� ���Ű�����
    m_vertexId += i;


    // ��Ƽ���� �ִ��� Ȯ��
    if (aiMesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = aiScene->mMaterials[aiMesh->mMaterialIndex];

        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString filePath;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &filePath);

            auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(HBSoft::ToUnicode(filePath.C_Str()));
            subMesh->textureName     = fileName + fileExt;
            subMesh->hasTexture      = true;
        }
        else
        {
            subMesh->hasTexture = false;
        }
    }

    mesh->m_subMeshes[m_subMeshId++] = subMesh;
}

void MeshFactory::UpdateBoneID(aiNode* aiNode, std::shared_ptr<Mesh>& mesh)
{
    if (aiNode != nullptr)
    {
        if (mesh->m_boneToId.count(aiNode->mName.C_Str()))
        {
            mesh->m_boneToId[aiNode->mName.C_Str()] = m_boneCount++;
        }
        for (UINT i = 0; i < aiNode->mNumChildren; i++)
        {
            UpdateBoneID(aiNode->mChildren[i], mesh);
        }
    }
}

void MeshFactory::FindDeformingBones(const aiScene* aiScene, std::shared_ptr<Mesh>& mesh)
{
    for (UINT i = 0; i < aiScene->mNumMeshes; i++)
    {
        const auto* aiMesh = aiScene->mMeshes[i];
        if (aiMesh->HasBones())
        {
            for (UINT i = 0; i < aiMesh->mNumBones; i++)
            {
                const aiBone* bone = aiMesh->mBones[i];

                // bone�� �����Ǵ� node�� �̸��� ����
                // �ڿ��� node �̸����� �θ� ã�� �� ����
                mesh->m_boneToId[bone->mName.C_Str()] = -1;

                // ����: ���� ������ ������Ʈ ������ �ƴ�

                // ��Ÿ: bone->mWeights == 0�� ��쿡�� ���Խ�����
                // ��Ÿ: bone->mNode = 0�̶� ��� �Ұ�
            }
        }
    }
}

void MeshFactory::InitMesh(const aiScene* aiScene, std::shared_ptr<Mesh>& mesh)
{
    UINT meshVerticesNums = 0;
    m_vertexId            = 0;
    m_subMeshId           = 0;
    m_boneCount           = 0;

    // ���ؽ� ���� ���ؼ� �ϳ��� ���ؽ� ���۷� ��ġ�� ���� ���ؽ� �� ����
    for (UINT i = 0; i < aiScene->mNumMeshes; i++)
        meshVerticesNums += aiScene->mMeshes[i]->mNumVertices;

    mesh->m_subMeshes.resize(aiScene->mNumMeshes);
    mesh->m_vertices.resize(meshVerticesNums);
}

std::shared_ptr<Mesh> MeshFactory::Create(std::shared_ptr<D3Device>& device, const wstringV path)
{
    Assimp::Importer importer;

    std::string wPath = HBSoft::ToMultiByte(path);

    const aiScene* pScene =
    importer.ReadFile(wPath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

    if (pScene)
    {
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

        InitMesh(pScene, mesh);
        FindDeformingBones(pScene, mesh);
        UpdateBoneID(pScene->mRootNode, mesh);

        // 3. ������Ʈ ������� �� �̸� ���� (boneIdToName)
        mesh->m_idToBone.resize(mesh->m_boneToId.size());
        for (auto& boneIdx : mesh->m_boneToId)
            mesh->m_idToBone[boneIdx.second] = boneIdx.first;

        ProcessNode(pScene->mRootNode, pScene, mesh);

        device->CreateVertexBuffer(mesh->m_vertices, mesh->m_vertexBuffer);

        for (UINT i = 0; i < mesh->m_subMeshes.size(); i++)
            device->CreateIndexBuffer(mesh->m_subMeshes[i]->indices, mesh->m_subMeshes[i]->indexBuffer);

        return mesh;
    }
    else
    {
        MessageBoxA(NULL, importer.GetErrorString(), "Load error", MB_OK);
    }

    return nullptr;
}

std::shared_ptr<Mesh> MeshFactory::Create(std::shared_ptr<D3Device>& device, const MeshShape shape)
{
    std::shared_ptr<Mesh> mesh;

    switch (shape)
    {
    case MeshShape::BOX3D:
        mesh = std::make_shared<Box3D>(device);
        break;

    case MeshShape::LINE:
        mesh = std::make_shared<Line>(device);
        break;

    case MeshShape::CUBEMAP:
        mesh = std::make_shared<CubeMap>(device);
        break;

    default:  // ����� ���� �޽� �߰� ���ϸ� ���� �߰���
        assert(false);
    }

    return mesh;
}

std::shared_ptr<Mesh> MeshFactory::CreateMap(std::shared_ptr<D3Device>& device, const UINT width,
                                             const UINT height)
{
    return std::shared_ptr<Mesh>();
}

bool MeshFactory::IsMeshFormat(const wstringV ext)
{
    if (ext.compare(L".fbx") == 0)
        return true;
    else if (ext.compare(L".obj") == 0)
        return true;

    return false;
}
