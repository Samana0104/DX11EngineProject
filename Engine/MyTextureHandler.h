#pragma once
#include "ResourceHandler.h"
#include "MyTexture.h"

namespace MyProject
{
	class MyTextureHandler : public ResourceHandler<MyTexture, TEXTURE_KEY>
	{
	public:
		bool CreateTextureComponent(const TEXTURE_KEY _key, const wstringV _texturePath);
	};
}
