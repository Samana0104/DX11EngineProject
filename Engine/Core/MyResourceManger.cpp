#include "pch.h"
#include "MyResourceManger.h"
using namespace MyProject;

void MyResourceManager::CreateDafultResource()
{
	CreateDefaultFonts();
	CreateDefaultMeshes();
	CreateDefaultTextures();
	CreateDefaultShaders();
	CreateDefaultSounds();
	CreateDefaultSprites();
}

void MyResourceManager::CreateDefaultFonts()
{
	for(auto& font : gFontPath)
		mFont.LoadExternalFontsAsFolder(font);

	for (auto& font : gDefaultFonts)
	{
		if(!mFont.CreateFontResource(font.first, font.second))
			MessageBoxA(NULL, "Not created default font[Key Error]", "[Font creation]", MB_OK);
	}

}

void MyResourceManager::CreateDefaultMeshes()
{
	for (auto& mesh : gDefaultMeshes)
	{
		if(!mMesh.CreateMeshResource(mesh.first, mesh.second))
			MessageBoxA(NULL, "Not created default mesh[Key Error]", "[Mesh creation]", MB_OK);
	}
}

void MyResourceManager::CreateDefaultTextures()
{
	for(auto& path : gTexturePath)
		mTexture.CreateTextureAsFolderPath(path);
	//if(!mTexture.CreateTextureComponent(texture))
	//	MessageBoxA(NULL, "Not created default texture[Key Error]", "[Texture creation]", MB_OK);
}

void MyResourceManager::CreateDefaultShaders()
{
	for (auto& shader : gDefaultShaders)
	{
		if(!mShader.CreateShaderResource(shader))
			MessageBoxA(NULL, "Not created default shader[Key Error]", "[Shader creation]", MB_OK);
	}
}

void MyResourceManager::CreateDefaultSounds()
{
	for(auto& path : gSoundPath)
		mSound.CreateSoundAsFolderPath(path);
}

void MyResourceManager::CreateDefaultSprites()
{
	for (auto& path : gSpritePath)
		mSprite.CreateSpriteAsFolderPath(path);
}

