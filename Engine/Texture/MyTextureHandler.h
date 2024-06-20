#pragma once
#include "ResourceHandler.h"
#include "MyTexture.h"

namespace MyProject
{
	class MyTextureHandler : public ResourceHandler<MyTexture, TEXTURE_KEY>
	{
	public:
		bool CreateTextureComponent(const wstringV _texturePath);
		void CreateTextureAsFolderPath(const wstringV _folderPath);
	};
}
