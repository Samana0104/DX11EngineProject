#include "pch.h"
#include "ResourceManger.h"
using namespace HBSoft;

void ResourceManager::CreateDafultResource()
{
    CreateDefaultFonts();
    CreateDefaultMeshes();
    CreateDefaultTextures();
    CreateDefaultShaders();
    CreateDefaultSounds();
    CreateDefaultSprites();
}

void ResourceManager::CreateDefaultFonts()
{
    for (auto& font : gFontPath)
        m_font.LoadExternalFontsAsFolder(font);

    for (auto& font : gDefaultFonts)
    {
        if (!m_font.CreateFontResource(font.first, font.second))
            MessageBoxA(NULL, "Not created default font[Key Error]", "[Font creation]", MB_OK);
    }
}

void ResourceManager::CreateDefaultMeshes()
{
    for (auto& mesh : gDefaultMeshes)
    {
        if (!m_mesh.CreateMeshResource(mesh.first, mesh.second))
            MessageBoxA(NULL, "Not created default mesh[Key Error]", "[Mesh creation]", MB_OK);
    }
}

void ResourceManager::CreateDefaultTextures()
{
    for (auto& path : gTexturePath)
        m_texture.CreateTextureAsFolderPath(path);
    // if(!m_texture.CreateTextureComponent(texture))
    //	MessageBoxA(NULL, "Not created default texture[Key Error]", "[Texture creation]",
    //MB_OK);
}

void ResourceManager::CreateDefaultShaders()
{
    for (auto& shader : gDefaultShaders)
    {
        if (!m_shader.CreateShaderResource(shader))
            MessageBoxA(NULL,
                        "Not created default shader[Key Error]",
                        "[Shader creation]",
                        MB_OK);
    }
}

void ResourceManager::CreateDefaultSounds()
{
    for (auto& path : gSoundPath)
        m_sound.CreateSoundAsFolderPath(path);
}

void ResourceManager::CreateDefaultSprites()
{
    for (auto& path : gSpritePath)
        m_sprite.CreateSpriteAsFolderPath(path);
}
