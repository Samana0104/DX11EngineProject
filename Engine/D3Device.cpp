#include "pch.h"
#include "D3Device.h"
using namespace MyProject;

bool D3Device::CreateDeviceAndSwapChain()
{
	CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	HRESULT hr;

	DXGI_SWAP_CHAIN_DESC pSwapChainDesc = { };
	{
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
	}

	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
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

	ComPtr<ID3D11Texture2D> backBuffer;
	hr = mSwapChain->GetBuffer(
		0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));

	if (FAILED(hr))
		return false;

	hr = mD3dDevice->CreateRenderTargetView(
		reinterpret_cast<ID3D11Resource*>(backBuffer.Get()), nullptr, mRTV.GetAddressOf());
	
	mContext->OMSetRenderTargets(1, mRTV.GetAddressOf(), nullptr);

	return !FAILED(hr);
}

bool D3Device::CreateDirect2DRenderTarget()
{
	HRESULT hr; 
	ComPtr<IDXGISurface> dxgiSurface;
	hr = mSwapChain->GetBuffer(0, __uuidof(IDXGISurface),
		reinterpret_cast<void**>(dxgiSurface.GetAddressOf()));

	if (FAILED(hr))
		return false;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mD2dFactory.GetAddressOf());

	if (FAILED(hr))
		return false;

	D2D1_RENDER_TARGET_PROPERTIES rtp;
	{
		rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
		rtp.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
		rtp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
		rtp.dpiX = 0;
		rtp.dpiY = 0;
		rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
		rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
	}

	hr = mD2dFactory->CreateDxgiSurfaceRenderTarget(dxgiSurface.Get(), &rtp, mD2dRT.GetAddressOf());

	return !FAILED(hr);
}

void D3Device::CreateViewport()
{
	auto windowSize = MyWindow::GetInstance().GetWindowSizeF();

	mViewPort.TopLeftX = 0;
	mViewPort.TopLeftY = 0;
	mViewPort.Width = windowSize.x;
	mViewPort.Height = windowSize.y;
	mViewPort.MinDepth = 0;
	mViewPort.MaxDepth = 1;

	mContext->RSSetViewports(1, &mViewPort);
}

bool D3Device::CreateDevice()
{
	if (!CreateDeviceAndSwapChain())
		return false;
	
	if (!CreateRenderTargetView())
		return false;

	if (!CreateDirect2DRenderTarget())
		return false;

	CreateViewport();
	return true;
}
