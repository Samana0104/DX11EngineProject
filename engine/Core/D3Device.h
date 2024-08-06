#pragma once
#include "MyWindow.h"

namespace MyProject
{
	using namespace Microsoft::WRL;

	enum class ViewType
	{
		CENTER=0,
		LEFT_TOP=1
	};

	class D3Device : public Singleton<D3Device>
	{
	public:
		ComPtr<ID3D11Device>			mD3dDevice;
		ComPtr<ID3D11DeviceContext>		mContext;
		ComPtr<ID3D11RenderTargetView>	mRTV;
		ComPtr<ID3D11BlendState>		mAlphaBlend;
		ComPtr<ID3D11SamplerState>		mSamplerState;
		ComPtr<IDXGISwapChain>			mSwapChain;
		ComPtr<ID2D1RenderTarget>		mD2dRT;
		ComPtr<ID2D1Factory>			mD2dFactory;

		D3D11_VIEWPORT			mViewPort;
		DXGI_SWAP_CHAIN_DESC	mSwapChainDesc;
	
		CALLBACK_ID mWMSizeID;

	private:
		friend class Singleton<D3Device>;
		D3Device() = default;

		void OnWMSize(UINT _width, UINT _height);

		bool CreateDeviceAndSwapChain();
		bool CreateRenderTargetView();
		bool CreateDirect2DRenderTarget();
		bool CreateSamplerState();
		void CreateViewport();
		bool SetAlphaBlendingState();

		void SetViewportSize(ViewType _viewType, glm::vec2 _size);

	public:
		~D3Device();

		void SetViewportSizeOnCenter(glm::vec2 _size);
		void SetViewportSizeOnLeftTop(glm::vec2 _size);
		
		glm::vec2 GetViewportSize() const;
		bool CreateDevice();
	};

}