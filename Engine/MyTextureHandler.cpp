#include "pch.h"
#include "MyTextureHandler.h"
using namespace MyProject;

void MyTextureHandler::CreateTexture(const std::string _key, const wstringV _texturePath)
{
	auto texture = std::make_shared<MyTexture>(_texturePath);
	AddComponent(_key, texture);
}

void MyTextureHandler::AddTexture(const std::string _key, std::shared_ptr<MyTexture>& _texture)
{
	if (!AddComponent(_key, _texture))
	{
		MessageBoxA(NULL, "exist texture[Key Error]", "Texture Error", MB_OK);
	}
}
