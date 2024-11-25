/*
author : 변한빛
description : 메쉬의 기본 리소스를 정의하기 위한 헤더 파일

version: 1.0.0
date: 2024-11-08
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    // 기본 메쉬 만들꺼면 여기 열거형에 추가하고
    // 메쉬 클래스 상속하고 에셋 매니저에 따로 작성하고 디폴트 메쉬에 추가할 것
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
        UINT  i[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        float w[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
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
        std::vector<std::wstring> m_textureName;  // 텍스쳐 담을 배열
        std::vector<Vertex>       m_vertices;     // 버텍스 버퍼용 배열
        std::vector<UINT>         m_indices;      // 인덱스  버퍼용 배열

        std::vector<std::shared_ptr<SubMesh>> m_subMeshes;

        std::vector<std::string>           m_idxToBone;
        std::map<std::string, UINT>        m_boneToIdx;
        std::map<std::string, std::string> m_bornParent;
        std::vector<mat4>                  m_bindPoseMat;
        std::vector<std::vector<mat4>>     m_animationMat;

        bool m_hasAnimation;

        ComPtr<ID3D11Buffer> m_vertexBuffer;
        ComPtr<ID3D11Buffer> m_indexBuffer;


    public:
        Mesh(bool hasAnimation = false);
        ~Mesh() = default;

        void SetVertices(std::shared_ptr<D3Device> device, const std::vector<Vertex>& vertices);
        void SetVertex(std::shared_ptr<D3Device> device, const Vertex& vertex, const UINT idx);
    };

}  // namespace HBSoft
