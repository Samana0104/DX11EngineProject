#pragma once
#include "MyCoreAPI.h"

namespace MyProject
{
	class MyTexture 
	{
	private:
		ComPtr<ID3D11ShaderResourceView>	mSRV;
		ComPtr<ID3D11Resource>				mTexture;

		std::wstring	mTexturePath;
		UINT mTextureWidth;
		UINT mTextureHeight;

	protected:
		inline static D3Device& mDevice = D3Device::GetInstance();

	private:
		bool CreateTexture();
		void LoadTextureSize();
		void Load1DTextureSize();
		void Load2DTextureSize();
		void Load3DTextureSize();

	public:
		MyTexture(const wstringV _filePath);

		POINT_F GetTextureSizeF() const;
		POINT_U GetTextureSizeU() const;
		vec2	GetTextureSizeVec2() const;

		virtual void Render();
	};
}
