/*
author : ���Ѻ�
description : 2D������ �׷��� ������Ʈ�� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Renderable.h"
#include "Transform2D.h"

namespace HBSoft
{
    struct RenderDesc
    {
        TEXTURE_KEY texKey;
        MESH_KEY    meshKey;
        SHADER_KEY  shaderKey;
    };

    // ���߿� public : Composite
    class Object2D
    {
    protected:
        TEXTURE_KEY m_textureKey = L"1KGCABK.bmp";
        MESH_KEY    m_meshKey    = L"DEFAULT_MESH";
        SHADER_KEY  m_shaderKey  = L"PixelShader.hlsl";
        vec4        m_color      = {1.f, 1.f, 1.f, 1.f};

    public:
        Transform2D m_transform;

    public:
        Object2D()          = default;
        virtual ~Object2D() = default;

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
