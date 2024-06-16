#pragma once
#include "MyWindow.h"

namespace MyProject
{
	using namespace Microsoft::WRL;

	class D3Device : public Singleton<D3Device>
	{
	public:
		ComPtr<ID3D11Device>			mD3dDevice;
		ComPtr<ID3D11DeviceContext>		mContext;
		ComPtr<IDXGISwapChain>			mSwapChain;
		ComPtr<ID3D11RenderTargetView>	mRTV;
		ComPtr<ID2D1RenderTarget>		mD2dRT;
		ComPtr<ID2D1Factory>			mD2dFactory;

		D3D11_VIEWPORT	mViewPort;
	
	private:
		bool CreateDeviceAndSwapChain();
		bool CreateRenderTargetView();
		bool CreateDirect2DRenderTarget();
		void CreateViewport();

	public:
		bool CreateDevice();
	};

}