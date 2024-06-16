#include "pch.h"
#include "MyTextureHandler.h"
using namespace MyProject;

bool MyTextureHandler::CreateTextureComponent(
	const TEXTURE_KEY _key,
	const wstringV _texturePath)
{
	if (IsKeyContained(_key))
		return false;

	auto texture = std::make_shared<MyTexture>(_texturePath);
	return AddResource(_key, texture);
}
