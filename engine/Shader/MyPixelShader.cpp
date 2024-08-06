#include "pch.h"
#include "MyPixelShader.h"
using namespace MyProject;

MyPixelShader::MyPixelShader(const ShaderDesc& _desc) :
	MyShader(_desc)
{
#ifdef _DEBUG
	_ASSERT(CreateShader());
#else
	CreateShader();
#endif
	SetUpConfiguration();
}

bool MyPixelShader::CreatePixelShader()
{
	HRESULT hr;
	ComPtr<ID3DBlob> errorMsg;

	hr = D3DCompileFromFile(
		mShaderDesc.mShaderPath.c_str(),
		nullptr,
		nullptr,
		mShaderDesc.mShaderEntry.c_str(),
		"ps_5_0", // dx11 정점쉐이더 컴파일러
		0,
		0,
		mShaderByteCode.GetAddressOf(),
		errorMsg.GetAddressOf()
	);

	if (FAILED(hr))
	{
		MessageBoxA(NULL,
			(char*)errorMsg->GetBufferPointer(),
			"PixelShader error", MB_OK);
		return false;
	}

	mDevice.mD3dDevice->CreatePixelShader(
		mShaderByteCode->GetBufferPointer(),
		mShaderByteCode->GetBufferSize(), 
		nullptr,
		mPixelShader.GetAddressOf());

	return SUCCEEDED(hr);
}


bool MyPixelShader::CreateShader()
{
	if (!CreatePixelShader())
		return false;

	return true;
}

void MyPixelShader::SetUpConfiguration() const
{
	mDevice.mContext->PSSetShader(mPixelShader.Get(), nullptr, 0);	
}
