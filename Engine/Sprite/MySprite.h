#pragma once
#include "MyCoreAPI.h"
//#include "MyObject.h"


namespace MyProject
{
	class MyObject;

	enum class SpriteType : int
	{
		UV_RECT = 0,
		IMAGE = 1,
	};

	class MySprite
	{
	private:
		std::vector<RECT_F>		 mSpriteUVRects;
		std::vector<TEXTURE_KEY> mSpriteTextures;

		SpriteType  mSpriteType;
		TEXTURE_KEY	mSpriteMainKey;

		int	mSpriteCount;

	public:
		MySprite() = default;

		const RECT_F& GetUVRect(size_t _idx);
		const TEXTURE_KEY& GetTextureKey(size_t _idx) const;
		const TEXTURE_KEY& GetTextureMainKey() const;
		const SpriteType&  GetSpriteType() const;

		bool LoadSpriteScriptFile(wstringV _filePath);

		void Render(MyObject& _obj, size_t idx);

		size_t GetSize() const;
	};
}

