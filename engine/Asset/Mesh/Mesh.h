/*
author : 변한빛
description : 메쉬의 기본 리소스를 정의하기 위한 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    enum class MeshShape
    {
        BOX2D    = 1,
        CIRCLE2D = 2
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
    private:
        std::vector<Vertex> m_vertices;
        std::vector<size_t> m_indices;

        ComPtr<ID3D11Buffer> m_vertexBuffer;
        MeshShape            m_meshShape;

    private:
        void UpdateRenderVertices(const mat3& matrix, const vec4& color);

    protected:
        Mesh(MeshShape meshShape);

        void ReserveVertexSize(size_t vertexCount);
        void AddVertexAndUV(const vec2 vertex, const vec2 uv);
        void AddVertexIndex(std::initializer_list<size_t> index);

    public:
        void Draw(const mat3& matrix, const vec4 color = {1.f, 1.f, 1.f, 1.f});
    };
}  // namespace HBSoft
