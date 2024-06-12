#include "MyTexture.h"
using namespace MyProject;

MyTexture::MyTexture(const wstringV _textureName)
{
	_ASSERT(CreateTexure(_textureName));
}

MyTexture::~MyTexture()
{
	MyTexture::ReleaseComponent();
}

bool MyTexture::CreateTexure(const wstringV _textureName)
{
	HRESULT hr =
		DirectX::CreateWICTextureFromFile(
			mDevice.mD3dDevice.Get(),
			_textureName.data(),
			mTexture.GetAddressOf(),//&m_pTexture
			mSRV.GetAddressOf());

	return !FAILED(hr);
}

void MyTexture::UpdateComponent()
{
}

void MyTexture::RenderComponent()
{
	mDevice.mContext->PSSetShaderResources(0, 1, mSRV.GetAddressOf());
}

void MyTexture::ReleaseComponent()
{		
	mSRV->Release();
	mTexture->Release();
}
