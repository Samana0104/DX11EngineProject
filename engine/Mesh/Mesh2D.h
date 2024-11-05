/*
author : 변한빛
description : 메쉬의 기본 리소스를 정의하기 위한 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"
#include "Transform2D.h"

namespace HBSoft
{
    enum class MeshShape
    {
        CUSTOM   = 0,
        BOX2D    = 1,
        CIRCLE2D = 2
    };

    struct Vertex2D
    {
        vec2 position;
        vec4 color;
        vec2 uv;
    };

    class Mesh2D
    {
    private:
        std::vector<vec2>     m_vertices;
        std::vector<vec2>     m_uv;
        std::vector<size_t>   m_indices;
        std::vector<Vertex2D> m_renderVertices;

        ComPtr<ID3D11Buffer> m_vertexBuffer;
        MeshShape            m_meshShape;

    private:
        bool CreateVertexBuffer();
        void SetIAVertexBuffer();
        void UpdateRenderVertices(const mat3& matrix, const vec4& color);

        void PostRender();

    protected:
        Mesh2D(MeshShape meshShape);

        void ReserveVertexSize(size_t vertexCount);
        void AddVertexAndUV(const vec2 vertex, const vec2 uv);
        void AddVertexIndex(std::initializer_list<size_t> index);
        void CreateMesh(const HPoint meshCom = {0.f, 0.f});
        void SetUVVertex(const size_t uvVertex, const vec2 uv);

    public:
        void Draw(const mat3& matrix, const vec4 color = {1.f, 1.f, 1.f, 1.f});

        virtual void SetUVVertexAsRect(const HRect& rect, const vec2& imageSize) = 0;
    };
}  // namespace HBSoft
