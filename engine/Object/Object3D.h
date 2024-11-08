/*
author : ���Ѻ�
description : 2D������ �׷��� ������Ʈ�� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-08
*/

#pragma once
#include "Core.h"
#include "Renderable.h"
#include "Transform3D.h"

namespace HBSoft
{
    // struct RenderDesc
    //{
    //     TEXTURE_KEY texKey;
    //     MESH_KEY    meshKey;
    //     SHADER_KEY  shaderKey;
    // };

    // ���߿� public : Composite
    class Object3D
    {
    protected:
        TEXTURE_KEY m_textureKey  = L"1KGCABK.bmp";
        MESH_KEY    m_meshKey     = L"BOX3D";
        SHADER_KEY  m_vsShaderKey = L"VertexShader.hlsl";
        SHADER_KEY  m_psShaderKey = L"PixelShader.hlsl";
        vec4        m_color       = {1.f, 1.f, 1.f, 1.f};

    public:
        Transform3D m_transform;

    public:
        Object3D()          = default;
        virtual ~Object3D() = default;

        void SetColor(const vec4 color);
        void SetTextureKey(const TEXTURE_KEY key);
        void SetMeshKey(const MESH_KEY key);
        void SetShaderKey(const SHADER_KEY key);

        const vec4&        GetColor() const;
        const MESH_KEY&    GetMeshKey() const;
        const TEXTURE_KEY& GetTextureKey() const;
        const SHADER_KEY&  GetShaderKey() const;

        virtual void Update(const float deltaTime);
        virtual void Render();
    };
}  // namespace HBSoft