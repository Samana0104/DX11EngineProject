/*
author : 변한빛
description : 메쉬를 생성 하기 위한 소스 파일

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

    // 메쉬 이름 불러옴
    subMesh->meshName = aMesh->mName.C_Str();

    // 인덱스 개수 불러옴
    for (i = 0; i < aMesh->mNumFaces; i++)
    {
        meshIndicesNums += aMesh->mFaces[i].mNumIndices;
    }

    // 인덱스 개수만큼 리사이즈
    subMesh->indices.resize(meshIndicesNums);

    /*
         인덱스 번호에 맞는 위치에 대입
         vertexId가 있는 이유는 버텍스 버퍼를 하나로 만들기 위해 버텍스 리스트 하나에
         모든 정점을 때려 박는데 서브 메쉬마다
         인덱스 번호가 1번 서브메쉬 0번 2번 서브메쉬 0번 이런식으로
         인덱스의 중복이 있기 때문에 버텍스 번호와 같이 더해줌
    */
    for (i = 0; i < aMesh->mNumFaces; i++)
    {
        aiFace face = aMesh->mFaces[i];

        for (UINT j = 0; j < face.mNumIndices; j++)
            subMesh->indices[face.mNumIndices * i + j] = face.mIndices[j] + m_vertexId;
    }

    // 버텍스 번호에 맞는 위치에 대입
    for (i = 0; i < aMesh->mNumVertices; i++)
    {
        // 위치 정보
        mesh->m_vertices[m_vertexId + i].p.x = aMesh->mVertices[i].x;
        mesh->m_vertices[m_vertexId + i].p.y = aMesh->mVertices[i].y;
        mesh->m_vertices[m_vertexId + i].p.z = aMesh->mVertices[i].z;

        // 노말 정보 (노말이 존재하는 경우)
        if (aMesh->HasNormals())
        {
            mesh->m_vertices[m_vertexId + i].n.x = aMesh->mNormals[i].x;
            mesh->m_vertices[m_vertexId + i].n.y = aMesh->mNormals[i].y;
            mesh->m_vertices[m_vertexId + i].n.z = aMesh->mNormals[i].z;
            mesh->m_vertices[m_vertexId + i].n   = glm::normalize(mesh->m_vertices[i].n);
        }

        // 텍스처 좌표 (첫 번째 UV 채널이 있는 경우)
        if (aMesh->HasTextureCoords(0))
        {
            mesh->m_vertices[m_vertexId + i].t.x = aMesh->mTextureCoords[0][i].x;
            mesh->m_vertices[m_vertexId + i].t.y = aMesh->mTextureCoords[0][i].y;
        }
        else
        {
            mesh->m_vertices[m_vertexId + i].t = vec2(1.0f);  // 텍스처 좌표가 없을 때 기본값
        }

        // 컬러 있으면 가져옴
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

    // 버텍스 아이디는 추가된 버텍스만큼 더해줘야 다음 서브메쉬때 갱신가능함
    m_vertexId += i;

    // 머티리얼 있는지 확인
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

    // 버텍스 개수 구해서 하나의 버텍스 버퍼로 합치기 위해 버텍스 수 구함
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

    default:  // 여기다 디폴트 메쉬 추가 안하면 에러 뜨게함
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
