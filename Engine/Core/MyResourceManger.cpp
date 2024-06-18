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
		if(!mFontHandler.CreateFontComponent(font.first, font.second))
			MessageBoxA(NULL, "Not created default font[Key Error]", "[Font creation]", MB_OK);
	}
}

void MyResourceManager::CreateDefaultMeshes()
{
	for (auto& mesh : gDefaultMeshes)
	{
		if(!mMeshHandler.CreateMesh(mesh.first, mesh.second))
			MessageBoxA(NULL, "Not created default mesh[Key Error]", "[Mesh creation]", MB_OK);
	}
}

void MyResourceManager::CreateDefaultTextures()
{
	for (auto& texture : gDefaultTextures)
	{
		if(!mTextureHandler.CreateTextureComponent(texture))
			MessageBoxA(NULL, "Not created default texture[Key Error]", "[Texture creation]", MB_OK);
	}
}

void MyResourceManager::CreateDefaultShaders()
{
	for (auto& shader : gDefaultShaders)
	{
		if(!mShaderHandler.CreateShader(shader))
			MessageBoxA(NULL, "Not created default shader[Key Error]", "[Shader creation]", MB_OK);
	}
}
