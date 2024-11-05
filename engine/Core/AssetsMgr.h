/*
author : ���Ѻ�
description : ���ҽ����� �����ϱ� ���� Ŭ���� �������

version: 1.0.0
date: 2024-11-05
*/

#pragma once
#include "DefaultResource.h"
#include "TextureHandler.h"
#include "MeshHandler.h"
#include "FontHandler.h"
#include "ShaderHandler.h"
#include "SoundHandler.h"

namespace HBSoft
{
    class AssetsMgr
    {
    private:
        std::shared_ptr<D3Device> m_device;

    public:
        TextureHandler m_texture;
        MeshHandler    m_mesh;
        FontHandler    m_font;
        ShaderHandler  m_shader;
        SoundHandler   m_sound;

    private:
        void CreateDefaultFonts();
        void CreateDefaultMeshes();
        void CreateDefaultTextures();
        void CreateDefaultShaders();
        void CreateDefaultSounds();

    public:
        AssetsMgr(std::shared_ptr<D3Device>& device);
        ~AssetsMgr();

        void CreateDafultResource();
    };
}  // namespace HBSoft
