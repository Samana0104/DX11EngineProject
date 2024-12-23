/*
author : 변한빛
description : 리소스들을 관리하기 위한 클래스 헤더파일

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
#include "Factory/AnimationFactory.h"

namespace HBSoft
{
    class AssetsMgr
    {
    private:
        std::shared_ptr<D3Device> m_device;

    public:
        MgrTemplate<Texture, TEXTURE_KEY>         m_textures;
        MgrTemplate<Mesh, MESH_KEY>               m_meshes;
        MgrTemplate<Font, FONT_KEY>               m_fonts;
        MgrTemplate<Shader, SHADER_KEY>           m_shaders;
        MgrTemplate<HSound, SOUND_KEY>            m_sounds;
        MgrTemplate<AnimationClip, ANIMATION_KEY> m_animations;

    private:
        void CreateResFromDefault();
        void CreateResFromPath();

        void CreateAsset(const wstringV path);

    public:
        AssetsMgr(std::shared_ptr<D3Device> device);

        void Update();

        ~AssetsMgr();
    };
}  // namespace HBSoft
