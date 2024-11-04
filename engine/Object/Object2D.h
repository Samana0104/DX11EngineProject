/*
author : ���Ѻ�
description : 2D������ �׷��� ������Ʈ�� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "ResourceManger.h"
#include "Composite.h"

namespace HBSoft
{
    // ���߿� public : Composite
    class Object2D
    {
    protected:
        TEXTURE_KEY m_textureKey = std::move(L"1KGCABK.bmp");
        MESH_KEY    m_meshKey    = std::move(L"DEFAULT_MESH");
        SHADER_KEY  m_shaderKey  = std::move(L"PixelShader.hlsl");
        vec4        m_color      = {1.f, 1.f, 1.f, 1.f};

        ResourceManager& m_manager = ResourceManager::GetInstance();

    public:
        Transform2D m_transform;

    public:
        Object2D()          = default;
        virtual ~Object2D() = default;

        void SetColor(const vec4 _color);
        void SetTextureKey(const TEXTURE_KEY _key);
        void SetMeshKey(const MESH_KEY _key);
        void SetShaderKey(const SHADER_KEY _key);

        // �̰Ŵ� ������Ʈ�� �־�� �� �Լ��ΰ�...
        void SetImageScale();

        const vec4&        GetColor() const;
        const MESH_KEY&    GetMeshKey() const;
        const TEXTURE_KEY& GetTextureKey() const;
        const SHADER_KEY&  GetShaderKey() const;

        virtual void Update(const float deltaTime);
        virtual void Render();
    };
}  // namespace HBSoft
