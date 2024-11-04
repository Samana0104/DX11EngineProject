#pragma once
#include "pch.h"
#include "Transform2D.h"
#include "Texture.h"

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
        std::vector<vec2>     m_tempUV;  // UV 좌표 관리를 위해서 억지로 넣음
        std::vector<size_t>   m_indices;
        std::vector<Vertex2D> m_renderVertices;

        ComPtr<ID3D11Buffer> m_vertexBuffer;
        MeshShape            m_meshShape;
        POINT_F              m_meshCom;  // 무게중심

    protected:
        D3Device& m_device = D3Device::GetInstance();
        Window&   m_window = Window::GetInstance();

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
        void CreateMesh(const POINT_F meshCom = {0.f, 0.f});
        void SetUVVertex(const size_t uvVertex, const vec2 uv);

    public:
        POINT_F GetMeshCom() const;

        void Draw(const mat3& matrix, const vec4 color = {1.f, 1.f, 1.f, 1.f});

        virtual void SetUVVertexAsRect(const RECT_F& rect, const vec2& imageSize) = 0;
    };
}  // namespace HBSoft
