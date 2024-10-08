#pragma once
#include "ResourceHandler.h"
#include "Sprite.h"

namespace HBSoft
{
	class SpriteHandler : public ResourceHandler<Sprite, SPRITE_KEY>
	{
	public:
		bool CreateSpriteResource(const wstringV _filePath);
		void CreateSpriteAsFolderPath(const wstringV _folderPath);
	};
}

