#include "D3Device.h"
using namespace MyProject;

bool D3Device::CreateDeviceAndSwapChain()
{
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC pSwapChainDesc;
	ZeroMemory(&pSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	pSwapChainDesc.BufferDesc.Width = MyWindow::GetInstance().GetWindowSize().x;
	pSwapChainDesc.BufferDesc.Height = MyWindow::GetInstance().GetWindowSize().y;
	pSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	pSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	pSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	pSwapChainDesc.SampleDesc.Count = 1;
	pSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	pSwapChainDesc.BufferCount = 1;
	pSwapChainDesc.OutputWindow = MyWindow::GetInstance().GetWindowHandle();
	pSwapChainDesc.Windowed = true;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		Flags,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&pSwapChainDesc,
		mSwapChain.GetAddressOf(),
		mD3dDevice.GetAddressOf(),
		nullptr,
		mContext.GetAddressOf());

	return !FAILED(hr);
}

bool D3Device::CreateRenderTargetView()
{
	HRESULT hr;

	//ID3D11RenderTargetView* g_pRTV = nullptr;
	ID3D11Texture2D* backBuffer;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));

	if (FAILED(hr))
		return false;

	ID3D11Resource* pResource = backBuffer;
	D3D11_RENDER_TARGET_VIEW_DESC* pDesc = nullptr;
	hr = mD3dDevice->CreateRenderTargetView(
		pResource,
		pDesc,
		mRTV.GetAddressOf());

	backBuffer->Release();
	
	return !FAILED(hr);
}

D3Device& MyProject::D3Device::GetInstance()
{
	static D3Device _device;
	return _device;
}

bool D3Device::CreateDevice()
{
	if (!CreateDeviceAndSwapChain())
		return false;
	
	if (!CreateRenderTargetView())
		return false;

	return true;
}

void  D3Device::DeleteDevice()
{
	mSwapChain->Release();
	mD3dDevice->Release();
	mContext->Release();
	mRTV->Release();
}
