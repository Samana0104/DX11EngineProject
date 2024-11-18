/*
author : 변한빛
description : 메쉬를 생성 하기 위한 소스 파일

version: 1.0.7
date: 2024-11-17
*/

#include "pch.h"
#include "MeshFactory.h"
using namespace HBSoft;

void MeshFactory::ProcessNode(aiNode* node, const aiScene* scene)
{

    // std::cout << node->mName.C_Str() << " : " << node->mNumMeshes << " "
    //           << node->mNumChildren << std::endl;

    for (UINT i = 0; i < node->mNumMeshes; i++)
    {

        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);

        // for (auto& v : newMesh.vertices)
        //{
        //     v.position = DirectX::SimpleMath::Vector3::Transform(v.position, m);
        // }

        // meshes.push_back(newMesh);
    }

    for (UINT i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

void MeshFactory::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    //// Data to fill
    // std::vector<Vertex>   vertices;
    // std::vector<uint32_t> indices;

    //// Walk through each of the mesh's vertices
    // for (UINT i = 0; i < mesh->mNumVertices; i++)
    //{
    //     Vertex vertex;

    //    vertex.position.x = mesh->mVertices[i].x;
    //    vertex.position.y = mesh->mVertices[i].y;
    //    vertex.position.z = mesh->mVertices[i].z;

    //    vertex.normal.x = mesh->mNormals[i].x;
    //    vertex.normal.y = mesh->mNormals[i].y;
    //    vertex.normal.z = mesh->mNormals[i].z;
    //    vertex.normal.Normalize();

    //    if (mesh->mTextureCoords[0])
    //    {
    //        vertex.texcoord.x = (float)mesh->mTextureCoords[0][i].x;
    //        vertex.texcoord.y = (float)mesh->mTextureCoords[0][i].y;
    //    }

    //    vertices.push_back(vertex);
    //}

    // for (UINT i = 0; i < mesh->mNumFaces; i++)
    //{
    //     aiFace face = mesh->mFaces[i];
    //     for (UINT j = 0; j < face.mNumIndices; j++)
    //         indices.push_back(face.mIndices[j]);
    // }

    // MeshData newMesh;
    // newMesh.vertices = vertices;
    // newMesh.indices  = indices;

    //// http://assimp.sourceforge.net/lib_html/materials.html
    // if (mesh->mMaterialIndex >= 0)
    //{
    //     aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    //    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    //    {
    //        aiString filepath;
    //        material->GetTexture(aiTextureType_DIFFUSE, 0, &filepath);

    //        std::string fullPath =
    //        this->basePath + std::string(std::filesystem::path(filepath.C_Str()).filename().string());

    //        newMesh.textureFilename = fullPath;
    //    }
    //}

    // return newMesh;
}

std::shared_ptr<Mesh> MeshFactory::Create(std::shared_ptr<D3Device>& device, const wstringV path)
{
    Assimp::Importer importer;
    std::string      wPath = HBSoft::ToMultiByte(path);

    const aiScene* pScene =
    importer.ReadFile(wPath, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

    if (pScene)
    {
        ProcessNode(pScene->mRootNode, pScene);
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

    return false;
}
