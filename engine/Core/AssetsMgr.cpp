/*
author : 변한빛
description : 리소스들을 관리하기 위한 클래스 소스파일

version: 1.0.3
date: 2024-11-07
*/

#include "pch.h"
#include "AssetsMgr.h"
using namespace HBSoft;

AssetsMgr::AssetsMgr(std::shared_ptr<D3Device>& device)
    : m_device(device)
{
    CreateDefaultResource();
}

void AssetsMgr::Update()
{
    auto& soundResources = m_sounds.GetAll();

    for (auto& sound : soundResources)
        sound.second->Update();
}

AssetsMgr::~AssetsMgr()
{
    m_fonts.Clear();
    m_meshes.Clear();
    m_shaders.Clear();
    m_sounds.Clear();
    m_textures.Clear();
}

void AssetsMgr::CreateDefaultResource()
{
    // 파일 재귀 참조
    std::filesystem::directory_iterator iter(g_defaultPath);
    for (auto& file = iter; iter != std::filesystem::end(iter); iter++)
    {
        if (!(*file).is_directory())
            CreateAssetAsFormat((*file).path().wstring());
    }
}

void AssetsMgr::CreateAssetAsFormat(wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);

    if (IsTextureFormat(fileExt))
    {
        return;
    }
    else if (IsMeshFormat(fileExt))
    {
        return;
    }
    else if (IsFontFormat(fileExt))
    {
        Font::AddExternalFont(path);
    }
    else if (IsShaderFormat(fileExt))
    {
        return;
    }
    else if (IsSoundFormat(fileExt))
    {
        SOUND_KEY key = fileName + fileExt;

        auto sound = std::make_unique<HSound>(path);
        m_sounds.Add(key, std::move(sound));
        return;
    }
    else
    {
        MessageBoxW(NULL, L"Not supported format", fileExt.c_str(), MB_OK);
    }
}

bool AssetsMgr::IsTextureFormat(const wstringV ext) const
{
    if (ext.compare(L"png") == 0)
        return true;
    else if (ext.compare(L"jpg") == 0)
        return true;
    else if (ext.compare(L"bmp") == 0)
        return true;

    return false;
}

bool AssetsMgr::IsMeshFormat(const wstringV ext) const
{
    return false;
}

bool AssetsMgr::IsFontFormat(const wstringV ext) const
{
    if (ext.compare(L"ttf") == 0)
        return true;

    return false;
}

bool AssetsMgr::IsShaderFormat(const wstringV ext) const
{
    if (ext.compare(L"hlsl") == 0)
        return true;

    return false;
}

bool AssetsMgr::IsSoundFormat(const wstringV ext) const
{
    if (ext.compare(L"mp3") == 0)
        return true;
    else if (ext.compare(L"wav") == 0)
        return true;

    return false;
}

void AssetsMgr::CreateResource()
{
    CreateFonts();
    CreateMeshes();
    CreateTextures();
    CreateShaders();
    CreateSounds();
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
