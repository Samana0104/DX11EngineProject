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
    // 파일 재귀 참조
    std::filesystem::recursive_directory_iterator iter(g_defaultPath);
    for (auto& file = iter; iter != std::filesystem::end(iter); iter++)
    {
        std::wstring file2 = (*file).path().wstring();
        if (!(*file).is_directory())
            CreateAssetAsFormat(std::filesystem::absolute((*file).path()).wstring());
        // absolue는 절대경로로 바꿔주는거임
    }

    // 작성한 폰트 규격 추가
    for (auto& fontDesc : g_defaultFonts)
        CreateFont(fontDesc.first, fontDesc.second);

    // 작성한 메쉬 추가
    for (auto& meshDesc : g_defaultMeshes)
        CreateMesh(meshDesc.first, meshDesc.second);
}

bool AssetsMgr::CreateTexture(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ 기능인데 구조적 바인딩이라고 pair 객체 바로 변수 값에다 쏴주는 기능임

    if (IsTextureFormat(fileExt))
    {
        TEXTURE_KEY key     = fileName + fileExt;
        auto        texture = std::make_shared<Texture>(m_device, path);
        return m_textures.Add(key, std::move(texture));
    }

    return false;
}

bool AssetsMgr::CreateMesh(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ 기능인데 구조적 바인딩이라고 pair 객체 바로 변수 값에다 쏴주는 기능임

    if (IsMeshFormat(fileExt))
    {
        return true;
    }
    return false;
}

bool AssetsMgr::CreateFont(const FONT_KEY key, const FontDesc& desc)
{
    auto font = std::make_shared<Font>(m_device, desc);
    return m_fonts.Add(key, std::move(font));
}

bool AssetsMgr::CreateShader(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ 기능인데 구조적 바인딩이라고 pair 객체 바로 변수 값에다 쏴주는 기능임

    if (IsShaderFormat(fileExt))
    {
        SHADER_KEY shaderKey  = fileName + fileExt;
        auto&      shaderDesc = g_defaultShaders.at(shaderKey);

        if (shaderDesc.m_shaderType == ShaderType::VERTEX)
        {
            std::shared_ptr<Shader> shader = std::make_shared<VertexShader>(m_device, path, shaderDesc);
            m_shaders.Add(shaderKey, std::move(shader));
        }
        else if (shaderDesc.m_shaderType == ShaderType::PIXEL)
        {
            std::shared_ptr<Shader> shader = std::make_shared<PixelShader>(m_device, path, shaderDesc);
            m_shaders.Add(shaderKey, std::move(shader));
        }

        return true;
    }

    return false;
}

bool AssetsMgr::CreateSound(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ 기능인데 구조적 바인딩이라고 pair 객체 바로 변수 값에다 쏴주는 기능임

    if (IsSoundFormat(path))
    {
        SOUND_KEY key   = fileName + fileExt;
        auto      sound = std::make_shared<HSound>(path);
        return m_sounds.Add(key, std::move(sound));
    }

    return false;
}

bool AssetsMgr::CreateMesh(const MESH_KEY key, const MeshShape shape)
{
    switch (shape)
    {
    case MeshShape::BOX3D:
        std::shared_ptr<Mesh> mesh = std::make_shared<Box3D>(m_device);
        return m_meshes.Add(key, mesh);
    }
    return false;
}

bool AssetsMgr::AddExternalFont(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ 기능인데 구조적 바인딩이라고 pair 객체 바로 변수 값에다 쏴주는 기능임

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
