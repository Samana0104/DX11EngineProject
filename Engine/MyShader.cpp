#include "pch.h"
#include "MyShader.h"
#include "MyMesh2D.h"
using namespace MyProject;

MyShader::MyShader()
{
	_ASSERT(LoadVertexShader());
	_ASSERT(LoadPixelShader());
	_ASSERT(CreateInputLayout());
}

bool MyShader::LoadVertexShader()
{
	// HLSL(High Level shader Language) 언어(컴파일 언어) : C언어와 유사함.
	// HLSL언어로 작성해서 컴파일을 하고 오브젝트를 사용한다.
	HRESULT hr;
	ID3DBlob* errormsg = nullptr; // 컴파일 중 오류 메세지
	hr = D3DCompileFromFile(
		L"VertexShader.hlsl",
		nullptr,
		nullptr,
		 "VSMain",
		 "vs_5_0", // dx11 정점쉐이더 컴파일러
		 0,
		 0,
		 VS_Bytecode.GetAddressOf(),
		 &errormsg
	);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, 
			(char*)errormsg->GetBufferPointer(), 
			"VertexShader error", MB_OK);
		return false;
	}

	if (errormsg)
		errormsg->Release();

	hr = mDevice.mD3dDevice->CreateVertexShader(
		VS_Bytecode->GetBufferPointer(),
		VS_Bytecode->GetBufferSize(), 
		nullptr, 
		mVertexShader.GetAddressOf());

	return !FAILED(hr);
}

bool MyShader::LoadPixelShader()
{
	/// 픽쉘쉐이더 로드 및 생성	
	HRESULT hr;
	ID3DBlob* errormsg = nullptr; // 컴파일 중 오류 메세지

	hr = D3DCompileFromFile(
		L"PixelShader.hlsl",
		nullptr,
		nullptr,
		"PSMain",
		"ps_5_0", // dx11 정점쉐이더 컴파일러
		0,
		0,
		PS_Bytecode.GetAddressOf(),
		&errormsg
	);

	if (FAILED(hr))
	{
		MessageBoxA(NULL,
			(char*)errormsg->GetBufferPointer(),
			"PixelShader error", MB_OK);
		return false;
	}

	if (errormsg)
		errormsg->Release();

	mDevice.mD3dDevice->CreatePixelShader(
		PS_Bytecode->GetBufferPointer(),
		PS_Bytecode->GetBufferSize(), 
		nullptr,
		mPixelShader.GetAddressOf());

	return !FAILED(hr);
}

bool MyShader::CreateInputLayout()
{
	const D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{"POS",0,	DXGI_FORMAT_R32G32_FLOAT,		0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,	0,8,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{"TEX",0,DXGI_FORMAT_R32G32_FLOAT,		    0,24,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	UINT NumElements = sizeof(layout) / sizeof(layout[0]);
	HRESULT hr = mDevice.mD3dDevice->CreateInputLayout(
		layout,
		NumElements,
		VS_Bytecode->GetBufferPointer(),
		VS_Bytecode->GetBufferSize(),
		mVertexLayout.GetAddressOf());

	return !FAILED(hr);
}

void MyShader::UpdateComponent()
{
}

void MyShader::RenderComponent()
{
	mDevice.mContext->IASetInputLayout(mVertexLayout.Get());
	mDevice.mContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDevice.mContext->VSSetShader(mVertexShader.Get(), nullptr, 0);	
	mDevice.mContext->PSSetShader(mPixelShader.Get(), nullptr, 0);	
}
