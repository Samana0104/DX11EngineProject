#include "pch.h"
#include "MyTexture.h"
using namespace MyProject;

MyTexture::MyTexture(const wstringV _texturePath)
	: mTexturePath(_texturePath)
{
	_ASSERT(CreateTexure());
}

bool MyTexture::CreateTexure()
{
	HRESULT hr =
		DirectX::CreateWICTextureFromFile(
			mDevice.mD3dDevice.Get(),
			mTexturePath.c_str(),
			mTexture.GetAddressOf(),//&m_pTexture
			mSRV.GetAddressOf());

	return !FAILED(hr);
}

void MyTexture::SetTextureResource() const
{
	mDevice.mContext->PSSetShaderResources(0, 1, mSRV.GetAddressOf());
}

void MyTexture::UpdateComponent()
{
}

void MyTexture::RenderComponent()
{
}
