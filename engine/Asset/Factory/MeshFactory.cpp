/*
author : 변한빛
description : 메쉬를 생성 하기 위한 소스 파일

version: 1.1.0
date: 2024-11-19
*/

#include "pch.h"
#include "MeshFactory.h"
using namespace HBSoft;

void MeshFactory::ProcessNode(aiNode* node, const aiScene* scene, std::shared_ptr<Mesh>& mesh)
{
    auto a = node->mTransformation;

    for (UINT i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(aiMesh, scene, mesh);
    }

    for (UINT i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, mesh);
    }
}

void MeshFactory::ProcessMesh(aiMesh* aiMesh, const aiScene* scene, std::shared_ptr<Mesh>& mesh)
{
    UINT meshIndicesNums = 0;
    UINT i               = 0;

    std::shared_ptr<SubMesh> subMesh = std::make_shared<SubMesh>();

    for (i = 0; i < aiMesh->mNumFaces; i++)
    {
        meshIndicesNums += aiMesh->mFaces[i].mNumIndices;
    }

    subMesh->indices.resize(meshIndicesNums);

    for (i = 0; i < aiMesh->mNumFaces; i++)
    {
        aiFace face = aiMesh->mFaces[i];

        for (UINT j = 0; j < face.mNumIndices; j++)
            subMesh->indices[face.mNumIndices * i + j] = face.mIndices[j] + m_vertexId;
    }

    for (i = 0; i < aiMesh->mNumVertices; i++)
    {
        // 위치 정보
        mesh->m_vertices[m_vertexId + i].p.x = aiMesh->mVertices[i].x;
        mesh->m_vertices[m_vertexId + i].p.y = aiMesh->mVertices[i].y;
        mesh->m_vertices[m_vertexId + i].p.z = aiMesh->mVertices[i].z;

        // 노말 정보 (노말이 존재하는 경우)
        if (aiMesh->HasNormals())
        {
            mesh->m_vertices[m_vertexId + i].n.x = aiMesh->mNormals[i].x;
            mesh->m_vertices[m_vertexId + i].n.y = aiMesh->mNormals[i].y;
            mesh->m_vertices[m_vertexId + i].n.z = aiMesh->mNormals[i].z;
            mesh->m_vertices[m_vertexId + i].n   = glm::normalize(mesh->m_vertices[i].n);
        }

        // 텍스처 좌표 (첫 번째 UV 채널이 있는 경우)
        if (aiMesh->HasTextureCoords(0))
        {
            mesh->m_vertices[m_vertexId + i].t.x = aiMesh->mTextureCoords[0][i].x;
            mesh->m_vertices[m_vertexId + i].t.y = aiMesh->mTextureCoords[0][i].y;
        }
        else
        {
            mesh->m_vertices[m_vertexId + i].t = vec2(0.0f);  // 텍스처 좌표가 없을 때 기본값
        }

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

    m_vertexId += i;

    if (aiMesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[aiMesh->mMaterialIndex];

        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString filePath;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &filePath);

            auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(HBSoft::ToUnicode(filePath.C_Str()));
            subMesh->textureName     = fileName + fileExt;
        }
    }

    mesh->m_subMeshes[m_subMeshId++] = subMesh;
}

std::shared_ptr<Mesh> MeshFactory::Create(std::shared_ptr<D3Device>& device, const wstringV path)
{
    Assimp::Importer importer;

    std::string wPath = HBSoft::ToMultiByte(path);

    const aiScene* pScene =
    importer.ReadFile(wPath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

    if (pScene)
    {
        std::shared_ptr<Mesh> mesh             = std::make_shared<Mesh>();
        UINT                  meshVerticesNums = 0;
        m_vertexId                             = 0;
        m_subMeshId                            = 0;


        // 버텍스 개수 구해서 하나의 버텍스 버퍼로 합침
        for (UINT i = 0; i < pScene->mNumMeshes; i++)
            meshVerticesNums += pScene->mMeshes[i]->mNumVertices;

        mesh->m_subMeshes.resize(pScene->mNumMeshes);
        mesh->m_vertices.resize(meshVerticesNums);

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

    default:  // 여기다 만든 메쉬 추가 안하면 에러 뜨게함
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
