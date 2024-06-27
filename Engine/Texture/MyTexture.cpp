#include "pch.h"
#include "MyTexture.h"
using namespace MyProject;

MyTexture::MyTexture(const wstringV _filePath) : 
	mTexturePath(_filePath)
{
#ifdef _DEBUG
	_ASSERT(CreateTexture());
#else
	CreateTexture();
#endif
	LoadTextureSize();
}

bool MyTexture::CreateTexture()
{
	HRESULT hr =
		DirectX::CreateWICTextureFromFile(
			mDevice.mD3dDevice.Get(),
			mTexturePath.c_str(),
			mTexture.GetAddressOf(),//&m_pTexture
			mSRV.GetAddressOf());

	return SUCCEEDED(hr);
}

void MyTexture::LoadTextureSize()
{	
	D3D11_RESOURCE_DIMENSION resourceType;
	mTexture->GetType(&resourceType);

	switch (resourceType)
	{
	case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
		Load1DTextureSize();
		break;

	case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
		Load2DTextureSize();
		break;

	case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
		Load3DTextureSize();
		break;
	}
}

void MyTexture::Load1DTextureSize()
{
	D3D11_TEXTURE1D_DESC desc;
	static_cast<ID3D11Texture1D*>(mTexture.Get())->GetDesc(&desc);

	mTextureWidth = desc.Width;
}

void MyTexture::Load2DTextureSize()
{
	D3D11_TEXTURE2D_DESC desc;
	static_cast<ID3D11Texture2D*>(mTexture.Get())->GetDesc(&desc);
	
	mTextureWidth  = desc.Width;
	mTextureHeight = desc.Height;
}

void MyTexture::Load3DTextureSize()
{
	D3D11_TEXTURE3D_DESC desc;
	static_cast<ID3D11Texture3D*>(mTexture.Get())->GetDesc(&desc);

	mTextureWidth	= desc.Width;
	mTextureHeight	= desc.Height;
	// desc.Depth ?? 언젠가 필요하면 추가
}

POINT_F MyTexture::GetTextureSizeF() const
{
	return { static_cast<float>(mTextureWidth), static_cast<float>(mTextureHeight) };
}

POINT_U MyTexture::GetTextureSizeU() const
{
	return { mTextureWidth, mTextureHeight };
}

vec2 MyTexture::GetTextureSizeVec2() const
{
	return { static_cast<float>(mTextureWidth), static_cast<float>(mTextureHeight) };
}

void MyTexture::Render()
{
	mDevice.mContext->PSSetShaderResources(0, 1, mSRV.GetAddressOf());
}
