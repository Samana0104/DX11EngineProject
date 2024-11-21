/*
author : ���Ѻ�
description : �޽��� �⺻ ���ҽ��� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-08
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    // �⺻ �޽� ���鲨�� ���� �������� �߰��ϰ�
    // �޽� Ŭ���� ����ϰ� ���� �Ŵ����� ���� �ۼ��ϰ� ����Ʈ �޽��� �߰��� ��
    enum class MeshShape
    {
        BOX2D    = 1,
        CIRCLE2D = 2,
        BOX3D    = 3,
        LINE     = 4,
        CUBEMAP  = 5
    };

    struct Vertex
    {
        vec3  p;  // position
        vec3  n;  // normal
        vec4  c;  // color
        vec2  t;  // texture coordinate
        UINT  boneIdx[8]    = {0, 0, 0, 0, 0, 0, 0, 0};
        float boneWeight[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
    };

    struct AnimationClip
    {

        struct Key
        {
            vec3 pos;
            vec3 scale;
            quat rot;

            mat4 GetWorldMat() { return glm::translate(pos) * glm::toMat4(rot) * glm::scale(scale); }
        };

        std::string                   name;         // Name of this animation clip
        std::vector<std::vector<Key>> keys;         // m_key[boneIdx][frameIdx]
        int                           numChannels;  // Number of bones
        int                           numKeys;      // Number of frames of this animation clip
        double                        duration;     // Duration of animation in ticks
        double                        ticksPerSec;  // Frames per second
    };

    struct SubMesh
    {
        ComPtr<ID3D11Buffer> indexBuffer;
        std::vector<UINT>    indices;
        std::string          meshName;
        std::wstring         textureName;
        bool                 hasTexture;
    };

    class Mesh
    {
    public:
        std::vector<std::wstring> m_textureName;  // �ؽ��� ���� �迭
        std::vector<Vertex>       m_vertices;     // ���ؽ� ���ۿ� �迭
        std::vector<UINT>         m_indices;      // �ε���  ���ۿ� �迭

        std::vector<std::shared_ptr<SubMesh>> m_subMeshes;
        std::map<std::string, UINT>           m_boneToId;
        std::vector<std::string>              m_idToBone;
        std::vector<int>                      m_boneParentIdx;
        std::vector<mat4>                     m_globalTransform;
        std::vector<mat4>                     m_bindPoseMat;
        std::vector<AnimationClip>            m_aniClip;

        bool m_hasAnimation;

        ComPtr<ID3D11Buffer> m_vertexBuffer;
        ComPtr<ID3D11Buffer> m_indexBuffer;


    public:
        Mesh(bool hasAnimation = false);
        ~Mesh() = default;

        void SetVertices(std::shared_ptr<D3Device>& device, const std::vector<Vertex>& vertices);
    };

}  // namespace HBSoft
