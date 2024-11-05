/*
author : 변한빛
description : 리소스들을 관리하기 위한 클래스 소스파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "AssetsMgr.h"
using namespace HBSoft;

AssetsMgr::AssetsMgr(std::shared_ptr<D3Device>& device)
    : m_device(device)
{}

AssetsMgr::~AssetsMgr()
{
    m_font.Clear();
    m_mesh.Clear();
    m_shader.Clear();
    m_sound.Clear();
    m_texture.Clear();
}

void AssetsMgr::CreateDafultResource()
{
    CreateDefaultFonts();
    CreateDefaultMeshes();
    CreateDefaultTextures();
    CreateDefaultShaders();
    CreateDefaultSounds();
}

void AssetsMgr::CreateDefaultFonts()
{
    for (auto& font : g_fontPath)
        m_font.LoadExternalFontsAsFolder(font);

    for (auto& font : g_defaultFonts)
    {
        if (!m_font.CreateFontResource(font.first, font.second))
            MessageBoxA(NULL, "Not created default font[Key Error]", "[Font creation]", MB_OK);
    }
}

void AssetsMgr::CreateDefaultMeshes()
{
    for (auto& mesh : g_defaultMeshes)
    {
        if (!m_mesh.CreateMeshResource(mesh.first, mesh.second))
            MessageBoxA(NULL, "Not created default mesh[Key Error]", "[Mesh creation]", MB_OK);
    }
}

void AssetsMgr::CreateDefaultTextures()
{
    for (auto& path : g_texturePath)
        m_texture.CreateTextureAsFolderPath(path);
    // if(!m_texture.CreateTextureComponent(texture))
    //	MessageBoxA(NULL, "Not created default texture[Key Error]", "[Texture creation]",
    // MB_OK);
}

void AssetsMgr::CreateDefaultShaders()
{
    for (auto& shader : g_defaultShaders)
    {
        if (!m_shader.CreateShaderResource(shader))
            MessageBoxA(NULL, "Not created default shader[Key Error]", "[Shader creation]", MB_OK);
    }
}

void AssetsMgr::CreateDefaultSounds()
{
    for (auto& path : g_soundPath)
        m_sound.CreateSoundAsFolderPath(path);
}
