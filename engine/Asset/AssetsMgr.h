/*
author : 변한빛
description : 리소스들을 관리하기 위한 클래스 헤더파일

version: 1.0.0
date: 2024-11-05
*/

#pragma once
#include "DefaultResource.h"
#include "Texture/Texture.h"
#include "Mesh/Mesh.h"
#include "Font/Font.h"
#include "Shader/VertexShader.h"
#include "Shader/PixelShader.h"
#include "Sound/HSound.h"
#include "MeshFactory.h"

namespace HBSoft
{
    class AssetsMgr
    {
    private:
        std::shared_ptr<D3Device> m_device;
        std::set<wstringV>        m_loadedFonts;

    public:
        MgrTemplate<Texture> m_textures;
        MgrTemplate<Mesh>    m_meshes;
        MgrTemplate<Font>    m_fonts;
        MgrTemplate<Shader>  m_shaders;
        MgrTemplate<HSound>  m_sounds;

    private:
        void CreateDefaultResource();
        void CreateAssetAsFormat(const wstringV path);

        bool IsTextureFormat(const wstringV ext) const;
        bool IsFontFormat(const wstringV ext) const;
        bool IsShaderFormat(const wstringV ext) const;
        bool IsSoundFormat(const wstringV ext) const;

    public:
        AssetsMgr(std::shared_ptr<D3Device>& device);

        bool CreateTexture(const wstringV path);
        bool CreateFont(const FONT_KEY key, const FontDesc& desc);
        bool CreateShader(const wstringV path);
        bool CreateSound(const wstringV path);
        // bool CreateMesh(const wstringV path); 나중에 assimploader에서 쓸 예정

        bool AddExternalFont(const wstringV path);

        void Update();

        ~AssetsMgr();
    };
}  // namespace HBSoft
