/*
author : 변한빛
description : 메쉬를 생성 하기 위한 소스 파일

version: 1.1.0
date: 2024-11-20
*/

#include "pch.h"
#include "MeshFactory.h"
using namespace HBSoft;

const aiNode* MeshFactory::FindParent(const aiNode* aNode, std::shared_ptr<Mesh>& mesh)
{
    if (aNode == nullptr)
        return nullptr;
    else if (mesh->m_boneToId.count(aNode->mName.C_Str()) > 0)
        return aNode;

    return FindParent(aNode->mParent, mesh);
}

void MeshFactory::ReadAnimation(const aiScene* aScene, std::shared_ptr<Mesh>& mesh)
{
    mesh->m_aniClip.resize(aScene->mNumAnimations);

    for (UINT i = 0; i < aScene->mNumAnimations; i++)
    {
        const aiAnimation* ani         = aScene->mAnimations[i];
        mesh->m_aniClip[i].duration    = ani->mDuration;
        mesh->m_aniClip[i].ticksPerSec = ani->mDuration;
        mesh->m_aniClip[i].numChannels = ani->mNumChannels;

        mesh->m_aniClip[i].keys.resize(mesh->m_boneToId.size());

        // 내 예상으로는 채널이 애니메이션 1프레임인거 같음
        for (UINT c = 0; c < ani->mNumChannels; c++)
        {
            const aiNodeAnim* nodeAnim = ani->mChannels[c];
            const int         boneId   = mesh->m_boneToId[nodeAnim->mNodeName.C_Str()];

            mesh->m_aniClip[i].keys[boneId].resize(nodeAnim->mNumPositionKeys);

            for (UINT k = 0; k < nodeAnim->mNumPositionKeys; k++)
            {
                const auto pos                           = nodeAnim->mPositionKeys[k].mValue;
                const auto rot                           = nodeAnim->mRotationKeys[k].mValue;
                const auto scale                         = nodeAnim->mScalingKeys[k].mValue;
                mesh->m_aniClip[i].keys[boneId][k].pos   = vec3(pos.x, pos.y, pos.z);
                mesh->m_aniClip[i].keys[boneId][k].scale = vec3(scale.x, scale.y, scale.z);
                mesh->m_aniClip[i].keys[boneId][k].rot   = quat(rot.w, rot.x, rot.y, rot.z);
            }
        }
    }
}

void MeshFactory::ProcessNode(aiNode* aNode, const aiScene* aScene, std::shared_ptr<Mesh>& mesh)
{
    auto a = aNode->mTransformation;

    if (mesh->m_boneToId.count(aNode->mName.C_Str()))
    {
        const aiNode* parentNode = FindParent(aNode->mParent, mesh);

        if (parentNode != nullptr)
        {
            const auto boneId             = mesh->m_boneToId[aNode->mName.C_Str()];
            mesh->m_boneParentIdx[boneId] = mesh->m_boneToId[parentNode->mName.C_Str()];
        }
    }

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

void MeshFactory::ProcessMesh(aiMesh* aMesh, const aiScene* aScene, std::shared_ptr<Mesh>& mesh)
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
            mesh->m_vertices[m_vertexId + i].t = vec2(0.0f);  // 텍스처 좌표가 없을 때 기본값
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

    if (aMesh->HasBones())
    {
        subMesh->boneWeights.resize(aMesh->mNumVertices);
        subMesh->boneIndices.resize(aMesh->mNumVertices);

        subMesh->offsetMatrices.resize(mesh->m_boneToId.size());
        subMesh->boneTransforms.resize(mesh->m_boneToId.size());

        int count = 0;
        for (UINT i = 0; i < aMesh->mNumBones; i++)
        {
            const aiBone* bone = aMesh->mBones[i];

            // 디버깅
            // cout << "BoneMap " << count++ << " : " << bone->mName.C_Str()
            //     << " NumBoneWeights = " << bone->mNumWeights << endl;

            const UINT boneId = mesh->m_boneToId[bone->mName.C_Str()];

            subMesh->offsetMatrices[i] = glm::transpose(glm::make_mat4(&bone->mOffsetMatrix.a1));

            // 이 뼈가 영향을 주는 Vertex의 개수
            for (UINT j = 0; j < bone->mNumWeights; j++)
            {
                aiVertexWeight weight = bone->mWeights[j];
                assert(weight.mVertexId < subMesh->boneIndices.size());
                subMesh->boneIndices[weight.mVertexId].push_back(boneId);
                subMesh->boneWeights[weight.mVertexId].push_back(weight.mWeight);
            }
        }

        // 예전에는 Vertex 하나에 영향을 주는 Bone은 최대 4개
        // 요즘은 더 많을 수도 있는데 모델링 소프트웨어에서 조정하거나
        // 읽어들이면서 weight가 너무 작은 것들은 뺄 수도 있음
    }

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

void MeshFactory::UpdateBoneID(aiNode* aNode, std::shared_ptr<Mesh>& mesh)
{
    if (aNode != nullptr)
    {
        if (mesh->m_boneToId.count(aNode->mName.C_Str()))
        {
            mesh->m_boneToId[aNode->mName.C_Str()] = m_boneCount++;
        }
        for (UINT i = 0; i < aNode->mNumChildren; i++)
        {
            UpdateBoneID(aNode->mChildren[i], mesh);
        }
    }
}

void MeshFactory::FindDeformingBones(const aiScene* aScene, std::shared_ptr<Mesh>& mesh)
{
    for (UINT i = 0; i < aScene->mNumMeshes; i++)
    {
        const auto* aMesh = aScene->mMeshes[i];
        if (aMesh->HasBones())
        {
            for (UINT j = 0; j < aMesh->mNumBones; j++)
            {
                const aiBone* aBone = aMesh->mBones[j];

                // bone과 대응되는 node의 이름은 동일
                // 뒤에서 node 이름으로 부모를 찾을 수 있음
                mesh->m_boneToId[aBone->mName.C_Str()] = -1;

                // 주의: 뼈의 순서가 업데이트 순서는 아님

                // 기타: bone->mWeights == 0일 경우에도 포함시켰음
                // 기타: bone->mNode = 0이라서 사용 불가
            }
        }
    }
}

void MeshFactory::InitMesh(const aiScene* aScene, std::shared_ptr<Mesh>& mesh)
{
    UINT meshVerticesNums = 0;
    m_vertexId            = 0;
    m_subMeshId           = 0;
    m_boneCount           = 0;

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
        FindDeformingBones(aScene, mesh);
        UpdateBoneID(aScene->mRootNode, mesh);

        // 3. 업데이트 순서대로 뼈 이름 저장 (boneIdToName)
        mesh->m_idToBone.resize(mesh->m_boneToId.size());
        for (auto& boneIdx : mesh->m_boneToId)
            mesh->m_idToBone[boneIdx.second] = boneIdx.first;

        mesh->m_boneParentIdx.resize(mesh->m_boneToId.size(), -1);

        ProcessNode(aScene->mRootNode, aScene, mesh);

        // 애니메이션 정보 읽기
        if (aScene->HasAnimations())
            ReadAnimation(aScene, mesh);

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
