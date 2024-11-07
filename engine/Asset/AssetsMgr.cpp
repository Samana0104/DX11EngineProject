/*
author : ���Ѻ�
description : ���ҽ����� �����ϱ� ���� Ŭ���� �ҽ�����

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

AssetsMgr::~AssetsMgr()
{
    m_fonts.Clear();
    m_meshes.Clear();
    m_shaders.Clear();
    m_sounds.Clear();
    m_textures.Clear();

    for (auto& font : m_loadedFonts)
        RemoveFontResourceEx(font.data(), FR_PRIVATE, 0);
}

void AssetsMgr::CreateAssetAsFormat(const wstringV path)
{
    AddExternalFont(path);

    CreateTexture(path);
    CreateMesh(path);
    CreateShader(path);
    CreateSound(path);
}

void AssetsMgr::Update()
{
    auto& soundResources = m_sounds.GetAll();

    for (auto& sound : soundResources)
        sound.second->Update();
}

void AssetsMgr::CreateDefaultResource()
{
    // ���� ��� ����
    std::filesystem::recursive_directory_iterator iter(g_defaultPath);
    for (auto& file = iter; iter != std::filesystem::end(iter); iter++)
    {
        std::wstring file2 = (*file).path().wstring();
        if (!(*file).is_directory())
            CreateAssetAsFormat((*file).path().wstring());
    }

    for (auto& fontDesc : g_defaultFonts)
        CreateFont(fontDesc.first, fontDesc.second);
}

bool AssetsMgr::CreateTexture(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ ����ε� ������ ���ε��̶�� pair ��ü �ٷ� ���� ������ ���ִ� �����

    if (IsTextureFormat(fileExt))
    {
        TEXTURE_KEY key     = fileName + fileExt;
        auto        texture = std::make_unique<Texture>(m_device, path);
        return m_textures.Add(key, std::move(texture));
    }

    return false;
}

bool AssetsMgr::CreateMesh(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ ����ε� ������ ���ε��̶�� pair ��ü �ٷ� ���� ������ ���ִ� �����

    if (IsMeshFormat(fileExt))
    {
        return true;
    }
    return false;
}

bool AssetsMgr::CreateFont(const FONT_KEY key, const FontDesc& desc)
{
    auto font = std::make_unique<Font>(m_device, desc);
    return m_fonts.Add(key, std::move(font));
}

bool AssetsMgr::CreateShader(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ ����ε� ������ ���ε��̶�� pair ��ü �ٷ� ���� ������ ���ִ� �����

    if (IsShaderFormat(fileExt))
    {
        SHADER_KEY shaderKey  = fileName + fileExt;
        auto&      shaderDesc = g_defaultShaders.at(shaderKey);

        if (shaderDesc.m_shaderType == ShaderType::VERTEX)
        {
            std::unique_ptr<Shader> shader = std::make_unique<VertexShader>(m_device, path, shaderDesc);
            m_shaders.Add(shaderKey, std::move(shader));
        }
        else if (shaderDesc.m_shaderType == ShaderType::PIXEL)
        {
            std::unique_ptr<Shader> shader = std::make_unique<PixelShader>(m_device, path, shaderDesc);
            m_shaders.Add(shaderKey, std::move(shader));
        }

        return true;
    }

    return false;
}

bool AssetsMgr::CreateSound(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ ����ε� ������ ���ε��̶�� pair ��ü �ٷ� ���� ������ ���ִ� �����

    if (IsSoundFormat(path))
    {
        SOUND_KEY key   = fileName + fileExt;
        auto      sound = std::make_unique<HSound>(path);
        return m_sounds.Add(key, std::move(sound));

        return true;
    }

    return false;
}

bool AssetsMgr::AddExternalFont(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ ����ε� ������ ���ε��̶�� pair ��ü �ٷ� ���� ������ ���ִ� �����

    if (!IsFontFormat(fileExt))
        return false;

    if (!m_loadedFonts.contains(path))
    {
        AddFontResourceEx(path.data(), FR_PRIVATE, 0);
        m_loadedFonts.insert(path);
        return true;
    }

    return false;
}

bool AssetsMgr::IsTextureFormat(const wstringV ext) const
{
    if (ext.compare(L".png") == 0)
        return true;
    else if (ext.compare(L".jpg") == 0)
        return true;
    else if (ext.compare(L".bmp") == 0)
        return true;

    return false;
}

bool AssetsMgr::IsMeshFormat(const wstringV ext) const
{
    return false;
}

bool AssetsMgr::IsFontFormat(const wstringV ext) const
{
    if (ext.compare(L".ttf") == 0)
        return true;

    return false;
}

bool AssetsMgr::IsShaderFormat(const wstringV ext) const
{
    if (ext.compare(L".hlsl") == 0)
        return true;
    auto test = ext.compare(L".hlsl");
    return false;
}

bool AssetsMgr::IsSoundFormat(const wstringV ext) const
{
    if (ext.compare(L".mp3") == 0)
        return true;
    else if (ext.compare(L".wav") == 0)
        return true;

    return false;
}
