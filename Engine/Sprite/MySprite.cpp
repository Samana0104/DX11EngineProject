#include "pch.h"
#include "MySprite.h"
using namespace MyProject;

const RECT_F& MySprite::GetUVRect(size_t _idx)
{
	return mSpriteUVRects[_idx];
}

const TEXTURE_KEY& MySprite::GetTextureKey(size_t _idx) const
{
	return mSpriteTextures[_idx];
}

const TEXTURE_KEY& MySprite::GetTextureMainKey() const
{
	return mSpriteMain;
}

bool MySprite::LoadSpriteScriptFile(wstringV _filePath)
{
	FILE* fp_src = nullptr;

	TCHAR pBuffer[256] = { 0 };
	TCHAR textureName[256] = { 0 };
	
	int spriteFrame = 0;
	int readFrame = 0;

	_wfopen_s(&fp_src, _filePath.data(), _T("rt"));

	if (fp_src == nullptr)
		return false;

// ---------------------------
	_fgetts(pBuffer, _countof(pBuffer), fp_src);
	_stscanf_s(pBuffer, _T("%d %d %s"),
		&spriteFrame,
		&mSpriteType,
		textureName,
		(unsigned int)_countof(textureName));
// ---------------------------

	mSpriteMain = textureName;
	
	switch (mSpriteType)
	{
	case SpriteType::UV_RECT:
		mSpriteUVRects.reserve(spriteFrame);
		RECT_F rt;

		for (int iFrame = 0; iFrame < spriteFrame; iFrame++)
		{
			_fgetts(pBuffer, _countof(pBuffer), fp_src);
			_stscanf_s(pBuffer, _T("%f %f %f %f %f"),
				&readFrame,
				&rt.left, 
				&rt.top,
				&rt.right,
				&rt.bottom);

			mSpriteUVRects.push_back(rt);
		}
		break;
	case SpriteType::IMAGE:
		mSpriteTextures.reserve(spriteFrame);

		for (int iFrame = 0; iFrame < spriteFrame; iFrame++)
		{
			_fgetts(pBuffer, _countof(pBuffer), fp_src);
			_stscanf_s(pBuffer, _T("%d %s"),
				&readFrame,
				textureName, (unsigned int)_countof(textureName));
			mSpriteTextures.push_back(textureName);
		}
		break;
	}
	fclose(fp_src);

	return true;
}

size_t MySprite::GetSize() const
{
	switch (mSpriteType)
	{
	case SpriteType::UV_RECT:
		return mSpriteUVRects.size();

	case SpriteType::IMAGE:
		return mSpriteTextures.size();
	}

	return -1;
}


