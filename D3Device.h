#pragma once
#include "MyWindow.h"
#include "Singleton.h"
#include <wrl.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

using namespace Microsoft::WRL;

namespace MyProject
{
	class D3Device : public Singleton<D3Device>
	{
	private:
		bool CreateDeviceAndSwapChain();
		bool CreateRenderTargetView();

	public:
		ComPtr<ID3D11Device>			mD3dDevice;
		ComPtr<ID3D11DeviceContext>		mContext;
		ComPtr<IDXGISwapChain>			mSwapChain;
		ComPtr<ID3D11RenderTargetView>	mRTV;
	
	public:
		~D3Device();

		bool CreateDevice();
	};

#define INITIALIZE_DEVICE(WIN_INSTANCE, WIDTH, HEIGHT) CREATE_WINDOW(WIN_INSTANCE, WIDTH, HEIGHT) _ASSERT(D3Device::GetInstance().CreateDevice());
}