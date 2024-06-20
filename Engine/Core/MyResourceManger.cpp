#include "pch.h"
#include "MyResourceManger.h"
using namespace MyProject;

void MyResourceManager::CreateDafultResource()
{
	CreateDefaultFonts();
	CreateDefaultMeshes();
	CreateDefaultTextures();
	CreateDefaultShaders();
}

void MyResourceManager::CreateDefaultFonts()
{
	for (auto& font : gDefaultFonts)
	{
		if(!mFont.CreateFontComponent(font.first, font.second))
			MessageBoxA(NULL, "Not created default font[Key Error]", "[Font creation]", MB_OK);
	}
}

void MyResourceManager::CreateDefaultMeshes()
{
	for (auto& mesh : gDefaultMeshes)
	{
		if(!mMesh.CreateMesh(mesh.first, mesh.second))
			MessageBoxA(NULL, "Not created default mesh[Key Error]", "[Mesh creation]", MB_OK);
	}
}

void MyResourceManager::CreateDefaultTextures()
{
	mTexture.CreateTextureAsFolderPath(gTexturePath);
	//if(!mTexture.CreateTextureComponent(texture))
	//	MessageBoxA(NULL, "Not created default texture[Key Error]", "[Texture creation]", MB_OK);
}

void MyResourceManager::CreateDefaultShaders()
{
	for (auto& shader : gDefaultShaders)
	{
		if(!mShader.CreateShader(shader))
			MessageBoxA(NULL, "Not created default shader[Key Error]", "[Shader creation]", MB_OK);
	}
}
