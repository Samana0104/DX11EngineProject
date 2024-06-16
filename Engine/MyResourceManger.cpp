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
			MessageBoxA(NULL, "Existed default font[Key Error]", font.first.c_str(), MB_OK);
	}
}

void MyResourceManager::CreateDefaultMeshes()
{
	for (auto& mesh : gDefaultMeshes)
	{
		mMeshHandler.CreateMesh(mesh.first, mesh.second.first, mesh.second.second);
	}


}

void MyResourceManager::CreateDefaultTextures()
{

}
