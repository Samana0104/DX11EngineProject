/*
author : 변한빛
description : 메쉬의 기본 리소스를 정의하기 위한 헤더 파일

version: 1.0.0
date: 2024-11-08
*/

#pragma once
#include "pch.h"
#include "AnimationClip.h"

namespace HBSoft
{
    // 기본 메쉬 만들꺼면 여기 열거형에 추가하고
    // 메쉬 클래스 상속하고 에셋 매니저에 따로 작성하고 디폴트 메쉬에 추가할 것
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
        // 오브젝트 애니메이션도 지원
        std::map<std::string, int> objectIndex;  // 오브젝트(뼈 포함)인덱스
        std::map<std::string, int> parentIndex;  // 오브젝트(뼈 포함)부모 인덱스
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
        std::vector<Vertex>                   m_vertices;  // 버텍스 버퍼용 배열
        std::vector<std::shared_ptr<SubMesh>> m_subMeshes;

        // 이 두개는 건들지 마셈 로더에서 알아서 함
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
