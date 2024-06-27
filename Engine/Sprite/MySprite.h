#pragma once
#include "MyCoreAPI.h"

namespace MyProject
{
	enum class SpriteType : int
	{
		UV_RECT = 0,
		IMAGE = 1,
	};

	class MySprite
	{
	private:
		SpriteType				 mSpriteType;
		std::vector<RECT_F>		 mSpriteUVRects;
		std::vector<TEXTURE_KEY> mSpriteTextures;
		TEXTURE_KEY				 mSpriteMain;

	public:
		MySprite() = default;

		const RECT_F& GetUVRect(size_t _idx);
		const TEXTURE_KEY& GetTextureKey(size_t _idx) const;
		const TEXTURE_KEY& GetTextureMainKey() const;

		bool LoadSpriteScriptFile(wstringV _filePath);

		size_t GetSize() const;
	};
}

