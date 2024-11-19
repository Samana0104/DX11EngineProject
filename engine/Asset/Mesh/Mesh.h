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

    struct SubMesh
    {
        std::wstring         textureName;
        std::vector<UINT>    indices;
        ComPtr<ID3D11Buffer> indexBuffer;
        std::vector<mat4>    animationMat;
    };

    class Mesh
    {
    public:
        std::vector<std::wstring> m_textureName;  // �ؽ��� ���� �迭
        std::vector<Vertex>       m_vertices;     // ���ؽ� ���ۿ� �迭
        std::vector<UINT>         m_indices;      // �ε���  ���ۿ� �迭

        std::vector<std::shared_ptr<SubMesh>> m_subMeshes;

        bool m_hasAnimation;

        ComPtr<ID3D11Buffer> m_vertexBuffer;
        ComPtr<ID3D11Buffer> m_indexBuffer;


    public:
        Mesh(bool hasAnimation = false);
        ~Mesh() = default;

        void SetVertices(std::shared_ptr<D3Device>& device, const std::vector<Vertex>& vertices);
    };

}  // namespace HBSoft
