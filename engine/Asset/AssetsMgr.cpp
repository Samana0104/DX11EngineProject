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
    // ���� ��� ����
    std::filesystem::recursive_directory_iterator iter(g_defaultPath);
    for (auto& file = iter; iter != std::filesystem::end(iter); iter++)
    {
        std::wstring file2 = (*file).path().wstring();
        if (!(*file).is_directory())
            CreateAsset(std::filesystem::absolute((*file).path()).wstring());
        // absolue�� �����η� �ٲ��ִ°���
    }
}

void AssetsMgr::CreateAsset(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ ����ε� ������ ���ε��̶�� pair ��ü �ٷ� ���� ������ ���ִ� �����
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
    // �ۼ��� ��Ʈ �԰� �߰�
    for (auto& fontDesc : g_defaultFonts)
        m_fonts.Add(fontDesc.first, FontFactory::CreateFromDesc(m_device, fontDesc.second));

    // �ۼ��� �޽� �߰�
    for (auto& meshDesc : g_defaultMeshes)
        m_meshes.Add(meshDesc.first, MeshFactory::Create(m_device, meshDesc.second));
}
