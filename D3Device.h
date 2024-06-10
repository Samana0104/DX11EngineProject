#pragma once
#include "MyWindow.h"
#include <wrl.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

using namespace Microsoft::WRL;

namespace MyProject
{
	class D3Device
	{
	private:
		D3Device() = default;
		D3Device(const D3Device&) = delete;
		D3Device(D3Device&&) = delete;
		D3Device& operator=(const D3Device&) = delete;
		D3Device& operator=(D3Device&&) = delete;

		bool CreateDeviceAndSwapChain();
		bool CreateRenderTargetView();

	public:
		/* singleton */
		static D3Device& GetInstance();

		ComPtr<ID3D11Device>			mD3dDevice;
		ComPtr<ID3D11DeviceContext>		mContext;
		ComPtr<IDXGISwapChain>			mSwapChain;
		ComPtr<ID3D11RenderTargetView>	mRTV;
	
	public:
		bool CreateDevice();
		void DeleteDevice();
	};

#define INITIALIZE_DEVICE(WIN_INSTANCE, WIDTH, HEIGHT) CREATE_WINDOW(WIN_INSTANCE, WIDTH, HEIGHT) _ASSERT(D3Device::GetInstance().CreateDevice());
}