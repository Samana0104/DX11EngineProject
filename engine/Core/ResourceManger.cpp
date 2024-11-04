#include "pch.h"
#include "ResourceManger.h"
using namespace HBSoft;

ResourceManager::~ResourceManager() {}

void ResourceManager::CreateDafultResource()
{
    CreateDefaultFonts();
    CreateDefaultMeshes();
    CreateDefaultTextures();
    CreateDefaultShaders();
    CreateDefaultSounds();
}

void ResourceManager::CreateDefaultFonts()
{
    for (auto& font : g_fontPath)
        m_font.LoadExternalFontsAsFolder(font);

    for (auto& font : g_defaultFonts)
    {
        if (!m_font.CreateFontResource(font.first, font.second))
            MessageBoxA(NULL, "Not created default font[Key Error]", "[Font creation]", MB_OK);
    }
}

void ResourceManager::CreateDefaultMeshes()
{
    for (auto& mesh : g_defaultMeshes)
    {
        if (!m_mesh.CreateMeshResource(mesh.first, mesh.second))
            MessageBoxA(NULL, "Not created default mesh[Key Error]", "[Mesh creation]", MB_OK);
    }
}

void ResourceManager::CreateDefaultTextures()
{
    for (auto& path : g_texturePath)
        m_texture.CreateTextureAsFolderPath(path);
    // if(!m_texture.CreateTextureComponent(texture))
    //	MessageBoxA(NULL, "Not created default texture[Key Error]", "[Texture creation]",
    // MB_OK);
}

void ResourceManager::CreateDefaultShaders()
{
    for (auto& shader : g_defaultShaders)
    {
        if (!m_shader.CreateShaderResource(shader))
            MessageBoxA(NULL, "Not created default shader[Key Error]", "[Shader creation]", MB_OK);
    }
}

void ResourceManager::CreateDefaultSounds()
{
    for (auto& path : g_soundPath)
        m_sound.CreateSoundAsFolderPath(path);
}
