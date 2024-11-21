/*
author : ���Ѻ�
description : �޽��� ���� �ϱ� ���� �ҽ� ����

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

        // �� �������δ� ä���� �ִϸ��̼� 1�������ΰ� ����
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

void MeshFactory::ProcessNode(aiNode* aNode, const aiScene* aScene, std::shared_ptr<Mesh>& mesh,
                              mat4& tr)
{
    if (mesh->m_boneToId.count(aNode->mName.C_Str()))
    {
        const aiNode* parentNode        = FindParent(aNode->mParent, mesh);
        const auto    boneId            = mesh->m_boneToId[aNode->mName.C_Str()];
        mesh->m_globalTransform[boneId] = tr;

        if (parentNode != nullptr)
        {
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
        ProcessNode(aNode->mChildren[i], aScene, mesh, tr);
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

    if (aMesh->HasBones())
    {
        std::vector<std::vector<float>> boneWeights;
        std::vector<std::vector<UINT>>  boneIndices;

        boneWeights.resize(aMesh->mNumVertices);
        boneIndices.resize(aMesh->mNumVertices);
        mesh->m_bindPoseMat.resize(mesh->m_boneToId.size());

        int count = 0;
        for (UINT i = 0; i < aMesh->mNumBones; i++)
        {
            const aiBone* bone   = aMesh->mBones[i];
            const UINT    boneId = mesh->m_boneToId[bone->mName.C_Str()];

            mesh->m_bindPoseMat[boneId] =
            mesh->m_globalTransform[boneId] * glm::transpose(glm::make_mat4x4(&bone->mOffsetMatrix.a1));

            // �� ���� ������ �ִ� Vertex�� ����
            for (UINT j = 0; j < bone->mNumWeights; j++)
            {
                aiVertexWeight weight = bone->mWeights[j];
                assert(weight.mVertexId < boneIndices.size());
                boneIndices[weight.mVertexId].push_back(boneId);
                boneWeights[weight.mVertexId].push_back(weight.mWeight);
            }
        }

        for (int i = 0; i < boneIndices.size(); i++)
        {
            for (int j = 0; j < boneIndices[i].size(); j++)
            {
                mesh->m_vertices[m_vertexId + i].boneIdx[j]    = boneIndices[i][j];
                mesh->m_vertices[m_vertexId + i].boneWeight[j] = boneWeights[i][j];
            }
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

void MeshFactory::UpdateBoneID(const aiNode* aNode, std::shared_ptr<Mesh>& mesh)
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

                mesh->m_boneToId[aBone->mName.C_Str()] = -1;
            }
        }
    }
}

void MeshFactory::ComputeGlobalTransforms(const aiNode* node, const mat4& parentTransform,
                                          std::shared_ptr<Mesh>& mesh)
{
    // Assimp�� ��ȯ ����� Row-Major, Transpose�� ���� glm�� Column-Major�� ��ȯ
    mat4 localTransform = glm::transpose(glm::make_mat4(&node->mTransformation.a1));

    // �θ��� �۷ι� Ʈ�������� ���� ����� ���� Ʈ�������� ���Ͽ� �۷ι� Ʈ������ ���
    mat4 globalTransform = parentTransform * localTransform;

    // ����� ��� �̸��� Ű�� �Ͽ� ����

    if (mesh->m_boneToId.count(node->mName.C_Str()))
    {
        const UINT boneId = mesh->m_boneToId[node->mName.C_Str()];

        mesh->m_globalTransform[boneId] = globalTransform;
    }

    // �ڽ� ���鿡 ���� ��������� ó��
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ComputeGlobalTransforms(node->mChildren[i], globalTransform, mesh);
    }
}

void MeshFactory::InitMesh(const aiScene* aScene, std::shared_ptr<Mesh>& mesh)
{
    UINT meshVerticesNums = 0;
    m_vertexId            = 0;
    m_subMeshId           = 0;
    m_boneCount           = 0;

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
        FindDeformingBones(aScene, mesh);
        UpdateBoneID(aScene->mRootNode, mesh);

        // 3. ������Ʈ ������� �� �̸� ���� (boneIdToName)
        mesh->m_idToBone.resize(mesh->m_boneToId.size());
        for (auto& boneIdx : mesh->m_boneToId)
            mesh->m_idToBone[boneIdx.second] = boneIdx.first;

        mesh->m_boneParentIdx.resize(mesh->m_boneToId.size(), -1);
        mesh->m_globalTransform.resize(mesh->m_boneToId.size());
        mat4 tr(1.f);
        ComputeGlobalTransforms(aScene->mRootNode, tr, mesh);
        ProcessNode(aScene->mRootNode, aScene, mesh, tr);

        // �ִϸ��̼� ���� �б�
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

    default:  // ����� ����Ʈ �޽� �߰� ���ϸ� ���� �߰���
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
