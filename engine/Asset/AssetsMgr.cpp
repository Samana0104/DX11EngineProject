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
    CreateResFromPath();
    CreateResFromDefault();
}

AssetsMgr::~AssetsMgr()
{
    m_fonts.Clear();
    m_meshes.Clear();
    m_shaders.Clear();
    m_sounds.Clear();
    m_textures.Clear();

    FontFactory::ClearExternalAllFonts();
    SoundFactory::ReleaseFmodSystem();
}

void AssetsMgr::Update()
{
    auto& soundResources = m_sounds.GetAll();

    for (auto& sound : soundResources)
        sound.second->Update();
}

void AssetsMgr::CreateResFromPath()
{
    // 파일 재귀 참조
    std::filesystem::recursive_directory_iterator iter(g_defaultPath);
    for (auto& file = iter; iter != std::filesystem::end(iter); iter++)
    {
        std::wstring file2 = (*file).path().wstring();
        if (!(*file).is_directory())
            CreateAsset(std::filesystem::absolute((*file).path()).wstring());
        // absolue는 절대경로로 바꿔주는거임
    }
}

void AssetsMgr::CreateAsset(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ 기능인데 구조적 바인딩이라고 pair 객체 바로 변수 값에다 쏴주는 기능임
    if (TextureFactory::IsTextureFormat(fileExt))
    {
        TEXTURE_KEY key = fileName + fileExt;
        m_textures.Add(key, TextureFactory::Create(m_device, path));
    }
    else if (MeshFactory::IsMeshFormat(fileExt))
    {
        MESH_KEY key = fileName + fileExt;
        m_meshes.Add(key, MeshFactory::Create(m_device, path));
    }
    else if (ShaderFactory::IsShaderFormat(fileExt))
    {
        SHADER_KEY key = fileName + fileExt;
        m_shaders.Add(key, ShaderFactory::Create(m_device, path, g_defaultShaders.at(key)));
    }
    else if (SoundFactory::IsSoundFormat(fileExt))
    {
        SOUND_KEY key = fileName + fileExt;
        m_sounds.Add(key, SoundFactory::Create(path));
    }
    else if (FontFactory::IsFontFormat(fileExt))
    {
        FontFactory::RegisterExternalFont(fileExt);
    }
}

void AssetsMgr::CreateResFromDefault()
{
    // 작성한 폰트 규격 추가
    for (auto& fontDesc : g_defaultFonts)
        m_fonts.Add(fontDesc.first, FontFactory::CreateFromDesc(m_device, fontDesc.second));

    // 작성한 메쉬 추가
    for (auto& meshDesc : g_defaultMeshes)
        m_meshes.Add(meshDesc.first, MeshFactory::Create(m_device, meshDesc.second));
}
