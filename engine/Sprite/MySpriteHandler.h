#pragma once
#include "ResourceHandler.h"
#include "MySprite.h"

namespace MyProject
{
	class MySpriteHandler : public ResourceHandler<MySprite, SPRITE_KEY>
	{
	public:
		bool CreateSpriteResource(const wstringV _filePath);
		void CreateSpriteAsFolderPath(const wstringV _folderPath);
	};
}

