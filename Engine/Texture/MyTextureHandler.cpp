#include "pch.h"
#include "MyTextureHandler.h"
using namespace MyProject;

bool MyTextureHandler::CreateTextureComponent(
	const wstringV _texturePath)
{
	std::wstring key = GetKeyAsFileName(_texturePath);

	auto texture = std::make_shared<MyTexture>(_texturePath);
	return AddResource(key, texture);
}
