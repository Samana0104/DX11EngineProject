/*
author : 변한빛
description : 리소스들을 관리하기 위한 클래스 헤더파일

version: 1.0.0
date: 2024-11-05
*/

#pragma once
#include "DefaultResource.h"
#include "Texture.h"
#include "Mesh2D.h"
#include "Font.h"
#include "Shader.h"
#include "HSound.h"

namespace HBSoft
{
    class AssetsMgr
    {
    private:
        std::shared_ptr<D3Device> m_device;

    public:
        MgrTemplate<Texture> m_textures;
        MgrTemplate<Mesh2D>  m_meshes;
        MgrTemplate<Font>    m_fonts;
        MgrTemplate<Shader>  m_shaders;
        MgrTemplate<HSound>  m_sounds;

    private:
        void CreateDefaultResource();
        void CreateAssetAsFormat(const wstringV path);

        bool IsTextureFormat(const wstringV ext) const;
        bool IsMeshFormat(const wstringV ext) const;
        bool IsFontFormat(const wstringV ext) const;
        bool IsShaderFormat(const wstringV ext) const;
        bool IsSoundFormat(const wstringV ext) const;

    public:
        AssetsMgr(std::shared_ptr<D3Device>& device);

        void Update();

        ~AssetsMgr();
    };
}  // namespace HBSoft
