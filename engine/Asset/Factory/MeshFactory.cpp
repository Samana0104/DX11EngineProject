/*
author : ���Ѻ�
description : �޽��� ���� �ϱ� ���� �ҽ� ����

version: 1.1.0
date: 2024-11-20
*/

#include "pch.h"
#include "MeshFactory.h"
using namespace HBSoft;

void MeshFactory::ProcessNode(aiNode* aNode, const aiScene* aScene, std::shared_ptr<Mesh>& mesh)
{
    for (UINT i = 0; i < aNode->mNumMeshes; i++)
    {
        aiMesh* aiMesh = aScene->mMeshes[aNode->mMeshes[i]];
        ProcessMesh(aiMesh, aScene, mesh);
    }

    for (UINT i = 0; i < aNode->mNumChildren; i++)
    {
        ProcessNode(aNode->mChildren[i], aScene, mesh);
    }
}

void MeshFactory::ProcessMesh(const aiMesh* aMesh, const aiScene* aScene, std::shared_ptr<Mesh>& mesh)
{
    UINT meshIndicesNums = 0;
    UINT i               = 0;

    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    // �޽� �̸� �ҷ���
    subMesh->meshName = aMesh->mName.C_Str();

    // �ε��� ���� �ҷ���
    for (i = 0; i < aMesh->mNumFaces; i++)
    {
        meshIndicesNums += aMesh->mFaces[i].mNumIndices;
    }

    // �ε��� ������ŭ ��������
    subMesh->indices.resize(meshIndicesNums);

    /*
         �ε��� ��ȣ�� �´� ��ġ�� ����
         vertexId�� �ִ� ������ ���ؽ� ���۸� �ϳ��� ����� ���� ���ؽ� ����Ʈ �ϳ���
         ��� ������ ���� �ڴµ� ���� �޽�����
         �ε��� ��ȣ�� 1�� ����޽� 0�� 2�� ����޽� 0�� �̷�������
         �ε����� �ߺ��� �ֱ� ������ ���ؽ� ��ȣ�� ���� ������
    */
    for (i = 0; i < aMesh->mNumFaces; i++)
    {
        aiFace face = aMesh->mFaces[i];

        for (UINT j = 0; j < face.mNumIndices; j++)
            subMesh->indices[face.mNumIndices * i + j] = face.mIndices[j] + m_vertexId;
    }

    // ���ؽ� ��ȣ�� �´� ��ġ�� ����
    for (i = 0; i < aMesh->mNumVertices; i++)
    {
        // ��ġ ����
        mesh->m_vertices[m_vertexId + i].p.x = aMesh->mVertices[i].x;
        mesh->m_vertices[m_vertexId + i].p.y = aMesh->mVertices[i].y;
        mesh->m_vertices[m_vertexId + i].p.z = aMesh->mVertices[i].z;

        // �븻 ���� (�븻�� �����ϴ� ���)
        if (aMesh->HasNormals())
        {
            mesh->m_vertices[m_vertexId + i].n.x = aMesh->mNormals[i].x;
            mesh->m_vertices[m_vertexId + i].n.y = aMesh->mNormals[i].y;
            mesh->m_vertices[m_vertexId + i].n.z = aMesh->mNormals[i].z;
            mesh->m_vertices[m_vertexId + i].n   = glm::normalize(mesh->m_vertices[i].n);
        }

        // �ؽ�ó ��ǥ (ù ��° UV ä���� �ִ� ���)
        if (aMesh->HasTextureCoords(0))
        {
            mesh->m_vertices[m_vertexId + i].t.x = aMesh->mTextureCoords[0][i].x;
            mesh->m_vertices[m_vertexId + i].t.y = aMesh->mTextureCoords[0][i].y;
        }
        else
        {
            mesh->m_vertices[m_vertexId + i].t = vec2(1.0f);  // �ؽ�ó ��ǥ�� ���� �� �⺻��
        }

        // �÷� ������ ������
        if (aMesh->HasVertexColors(0))
        {
            mesh->m_vertices[m_vertexId + i].c.r = aMesh->mColors[0][i].r;
            mesh->m_vertices[m_vertexId + i].c.g = aMesh->mColors[0][i].g;
            mesh->m_vertices[m_vertexId + i].c.b = aMesh->mColors[0][i].b;
            mesh->m_vertices[m_vertexId + i].c.a = aMesh->mColors[0][i].a;
        }
        else
        {
            mesh->m_vertices[m_vertexId + i].c = vec4(1.f);
        }
    }

    // ���ؽ� ���̵�� �߰��� ���ؽ���ŭ ������� ���� ����޽��� ���Ű�����
    m_vertexId += i;

    // ��Ƽ���� �ִ��� Ȯ��
    if (aMesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = aScene->mMaterials[aMesh->mMaterialIndex];

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

void MeshFactory::InitMesh(const aiScene* aScene, std::shared_ptr<Mesh>& mesh)
{
    UINT meshVerticesNums = 0;
    m_vertexId            = 0;
    m_subMeshId           = 0;

    // ���ؽ� ���� ���ؼ� �ϳ��� ���ؽ� ���۷� ��ġ�� ���� ���ؽ� �� ����
    for (UINT i = 0; i < aScene->mNumMeshes; i++)
        meshVerticesNums += aScene->mMeshes[i]->mNumVertices;

    mesh->m_subMeshes.resize(aScene->mNumMeshes);
    mesh->m_vertices.resize(meshVerticesNums);
}

std::shared_ptr<Mesh> MeshFactory::Create(std::shared_ptr<D3Device>& device, const wstringV path)
{
    Assimp::Importer importer;

    std::string wPath = HBSoft::ToMultiByte(path);

    const aiScene* aScene =
    importer.ReadFile(wPath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

    if (aScene)
    {
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

        InitMesh(aScene, mesh);
        ProcessNode(aScene->mRootNode, aScene, mesh);

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

    default:  // ����� ����Ʈ �޽� �߰� ���ϸ� ���� �߰���
        assert(false);
    }

    return mesh;
}

std::shared_ptr<Mesh> MeshFactory::CreateHeightMap(std::shared_ptr<D3Device>& device, const UINT width,
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
