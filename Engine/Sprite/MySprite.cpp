#include "pch.h"
#include "MyObject.h"
#include "MySprite.h"
using namespace MyProject;

const RECT_F& MySprite::GetUVRect(size_t _idx)
{
	return mSpriteUVRects[_idx];
}

const TEXTURE_KEY& MySprite::GetTextureKey(size_t _idx) const
{
	if (mSpriteType == SpriteType::UV_RECT)
		return mSpriteMainKey;
	else 
		return mSpriteTextures[_idx];
}

const TEXTURE_KEY& MySprite::GetTextureMainKey() const
{
	return mSpriteMainKey;
}

const SpriteType& MySprite::GetSpriteType() const
{
	return mSpriteType;
}

bool MySprite::LoadScript(wstringV _filePath)
{
	FILE* fp_src = nullptr;

	TCHAR pBuffer[256] = { 0 };
	TCHAR textureName[256] = { 0 };
	TCHAR shaderName[256] = { 0 };
	
	int readFrame = 0;

	_wfopen_s(&fp_src, _filePath.data(), _T("rt"));

	if (fp_src == nullptr)
		return false;

// ---------------------------
	_fgetts(pBuffer, _countof(pBuffer), fp_src);
	_stscanf_s(pBuffer, L"%d %d %s %s",
		&mSpriteCount,
		&mSpriteType,
		textureName,
		(unsigned int)_countof(textureName),
		shaderName,
		(unsigned int)_countof(shaderName));
// ---------------------------

	mSpriteMainKey = textureName;
	mSpriteShaderKey = shaderName;
	
	switch (mSpriteType)
	{
	case SpriteType::UV_RECT:
		mSpriteUVRects.reserve(mSpriteCount);
		RECT_F rt;

		for (int iFrame = 0; iFrame < mSpriteCount; iFrame++)
		{
			_fgetts(pBuffer, _countof(pBuffer), fp_src);
			_stscanf_s(pBuffer, L"%d %f %f %f %f",
				&readFrame,
				&rt.left, 
				&rt.top,
				&rt.right,
				&rt.bottom);

			mSpriteUVRects.push_back(rt);
		}
		break;
	case SpriteType::IMAGE:
		mSpriteTextures.reserve(mSpriteCount);

		for (int iFrame = 0; iFrame < mSpriteCount; iFrame++)
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

void MySprite::Render(MyObject& _obj, size_t idx)
{
	MyResourceManager& mManager = MyResourceManager::GetInstance();

	mManager.mShader[mSpriteShaderKey]->SetUpConfiguration();

	switch (mSpriteType)
	{
	case SpriteType::UV_RECT:
		vec2 imageSize = mManager.mTexture[mSpriteMainKey]->GetTextureSizeVec2();
		mManager.mTexture[mSpriteMainKey]->Render();
		mManager.mMesh[_obj.GetMeshKey()]->SetUVVertexAsRect(mSpriteUVRects[idx], imageSize);
		break;

	case SpriteType::IMAGE:
		mManager.mTexture[mSpriteTextures[idx]]->Render();
		break;
	}
}

size_t MySprite::GetSize() const
{
	return mSpriteCount;
}


