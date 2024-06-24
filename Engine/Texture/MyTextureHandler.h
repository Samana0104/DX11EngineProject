#pragma once
#include "ResourceHandler.h"
#include "MyTexture.h"

namespace MyProject
{
	class MyTextureHandler : public ResourceHandler<MyTexture, TEXTURE_KEY>
	{
	public:
		bool CreateTextureResource(const wstringV _filePath);
		void CreateTextureAsFolderPath(const wstringV _folderPath);
	};
}
