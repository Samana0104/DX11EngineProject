/*
author : ���Ѻ�
description : �޽��� �⺻ ���ҽ��� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-08
*/

#pragma once
#include "pch.h"
#include "AnimationClip.h"

namespace HBSoft
{
    // �⺻ �޽� ���鲨�� ���� �������� �߰��ϰ�
    // �޽� Ŭ���� ����ϰ� ���� �Ŵ����� ���� �ۼ��ϰ� ����Ʈ �޽��� �߰��� ��
    enum class MeshShape
    {
        BOX2D   = 1,
        BOX3D   = 2,
        CIRCLE  = 3,
        LINE    = 4,
        CUBEMAP = 5
    };

    struct Vertex
    {
        vec3  p;  // position
        vec3  n;  // normal
        vec4  c;  // color
        vec2  t;  // texture coordinate
        UINT  i[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        float w[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};

        bool operator==(const Vertex& ref)
        {
            if (p != ref.p)
                return false;

            if (n != ref.n)
                return false;

            if (c != ref.c)
                return false;

            if (t != ref.t)
                return false;

            return true;
        }
    };

    struct Born
    {
        // ������Ʈ �ִϸ��̼ǵ� ����
        std::map<std::string, int> objectIndex;  // ������Ʈ(�� ����)�ε���
        std::map<std::string, int> parentIndex;  // ������Ʈ(�� ����)�θ� �ε���
        std::map<std::string, int> bornIndex;
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
        std::vector<Vertex>                   m_vertices;  // ���ؽ� ���ۿ� �迭
        std::vector<std::shared_ptr<SubMesh>> m_subMeshes;

        // �� �ΰ��� �ǵ��� ���� �δ����� �˾Ƽ� ��
        Born m_born;

        std::vector<std::shared_ptr<AnimationClip>> m_animations;

        ComPtr<ID3D11Buffer> m_vertexBuffer;

    public:
        Mesh();
        ~Mesh() = default;

        void SetVertices(std::shared_ptr<D3Device> device, const std::vector<Vertex>& vertices);
        void SetVertex(std::shared_ptr<D3Device> device, const Vertex& vertex, const UINT idx);
        void UpdateVertices(std::shared_ptr<D3Device> device);
    };

}  // namespace HBSoft
