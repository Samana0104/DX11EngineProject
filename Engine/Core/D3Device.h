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
		ComPtr<ID3D11RenderTargetView>	mRTV;
		ComPtr<ID3D11BlendState>		mAlphaBlend;
		ComPtr<IDXGISwapChain>			mSwapChain;
		ComPtr<ID2D1RenderTarget>		mD2dRT;
		ComPtr<ID2D1Factory>			mD2dFactory;

		D3D11_VIEWPORT			mViewPort;
		DXGI_SWAP_CHAIN_DESC	mSwapChainDesc;
	
	private:
		void OnWMSize(UINT _width, UINT _height);

	private:
		friend class Singleton<D3Device>;
		D3Device() = default;

		bool CreateDeviceAndSwapChain();
		bool CreateRenderTargetView();
		bool CreateDirect2DRenderTarget();
		bool SetAlphaBlendingState();
		void CreateViewport();

	public:
		bool CreateDevice();
	};

}