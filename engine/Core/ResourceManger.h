#pragma once
#include "DefaultResource.h"
#include "TextureHandler.h"
#include "MeshHandler.h"
#include "FontHandler.h"
#include "ShaderHandler.h"
#include "SoundHandler.h"

namespace HBSoft
{
    class ResourceManager : public Singleton<ResourceManager>
    {
    public:
        TextureHandler m_texture;
        MeshHandler    m_mesh;
        FontHandler    m_font;
        ShaderHandler  m_shader;
        SoundHandler   m_sound;

    private:
        friend class Singleton<ResourceManager>;
        ResourceManager() = default;

        void CreateDefaultFonts();
        void CreateDefaultMeshes();
        void CreateDefaultTextures();
        void CreateDefaultShaders();
        void CreateDefaultSounds();

    public:
        ~ResourceManager();

        void CreateDafultResource();
    };
}  // namespace HBSoft
