#pragma once
#include "MyWindow.h"

using namespace Microsoft::WRL;

namespace MyProject
{
	class D3Device : public Singleton<D3Device>
	{
	private:
		bool CreateDeviceAndSwapChain();
		bool CreateRenderTargetView();
		bool CreateDirect2DRenderTarget();

	public:
		ComPtr<ID3D11Device>			mD3dDevice;
		ComPtr<ID3D11DeviceContext>		mContext;
		ComPtr<IDXGISwapChain>			mSwapChain;
		ComPtr<ID3D11RenderTargetView>	mRTV;
		ComPtr<ID2D1RenderTarget>		mD2dRT;
		ComPtr<ID2D1Factory>			mD2dFactory;
	
	public:
		bool CreateDevice();
	};

#define INITIALIZE_DEVICE(WIN_INSTANCE, WIDTH, HEIGHT) CREATE_WINDOW(WIN_INSTANCE, WIDTH, HEIGHT) _ASSERT(D3Device::GetInstance().CreateDevice());
}