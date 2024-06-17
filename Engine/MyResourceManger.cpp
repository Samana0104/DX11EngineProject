#include "pch.h"
#include "MyResourceManger.h"
using namespace MyProject;

void MyResourceManager::CreateDafultResource()
{
	CreateDefaultFonts();
	CreateDefaultMeshes();
	CreateDefaultTextures();
}

void MyResourceManager::CreateDefaultFonts()
{
	for (auto& font : gDefaultFonts)
	{
		if(!mFontHandler.CreateFontComponent(font.first, font.second))
			MessageBoxA(NULL, "Not created default font[Key Error]", font.first.c_str(), MB_OK);
	}
}

void MyResourceManager::CreateDefaultMeshes()
{
	for (auto& mesh : gDefaultMeshes)
	{
		if(!mMeshHandler.CreateMesh(mesh.first, mesh.second))
			MessageBoxA(NULL, "Not created default mesh[Key Error]", mesh.first.c_str(), MB_OK);
	}
}

void MyResourceManager::CreateDefaultTextures()
{
	for (auto& texture : gDefaultTextures)
	{
		if(!mTextureHandler.CreateTextureComponent(texture.first, texture.second))
			MessageBoxA(NULL, "Not created default texture[Key Error]", texture.first.c_str(), MB_OK);
	}
}
