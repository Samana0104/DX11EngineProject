/*
author : ���Ѻ�
description : ���ҽ����� �����ϱ� ���� Ŭ���� �������

version: 1.1
date: 2024-11-17
*/

#pragma once
#include "DefaultResource.h"
#include "Factory/SoundFactory.h"
#include "Factory/MeshFactory.h"
#include "Factory/FontFactory.h"
#include "Factory/ShaderFactory.h"
#include "Factory/TextureFactory.h"

namespace HBSoft
{
    class AssetsMgr
    {
    private:
        std::shared_ptr<D3Device> m_device;

    public:
        MgrTemplate<Texture> m_textures;
        MgrTemplate<Mesh>    m_meshes;
        MgrTemplate<Font>    m_fonts;
        MgrTemplate<Shader>  m_shaders;
        MgrTemplate<HSound>  m_sounds;

    private:
        void CreateResFromDefault();
        void CreateResFromPath();

        void CreateAsset(const wstringV path);

    public:
        AssetsMgr(std::shared_ptr<D3Device>& device);

        void Update();

        ~AssetsMgr();
    };
}  // namespace HBSoft
