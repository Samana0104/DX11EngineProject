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
        vec3 p;
        vec3 n;
        vec4 c;
        vec2 t;
    };

    class Mesh
    {
    public:
        std::vector<std::wstring> m_textureName;   // �ؽ��� ���� �迭
        std::vector<Vertex>       m_vertices;      // ���ؽ� ���ۿ� �迭
        std::vector<UINT>         m_indices;       // �ε���  ���ۿ� �迭
        std::vector<mat4>         m_animationMat;  // �ִϸ��̼� ����� ���

        std::shared_ptr<Mesh>              m_partentMesh;
        std::vector<std::shared_ptr<Mesh>> m_subMeshes;

        bool m_hasAnimation;

        ComPtr<ID3D11Buffer> m_vertexBuffer;
        ComPtr<ID3D11Buffer> m_indexBuffer;

    protected:
        Mesh(bool hasAnimation = false);

    public:
        Mesh(std::shared_ptr<D3Device>& device, const wstringV path);

        void SetVertices(std::shared_ptr<D3Device>& device, const std::vector<Vertex>& vertices);

        ~Mesh() = default;
    };

}  // namespace HBSoft
