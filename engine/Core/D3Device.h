/*
author : 변한빛
description :
다이렉트 디바이스 관련 정리한 헤더파일
싱글톤으로 작성되어 있어 어디서든 접근 가능

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Window.h"

namespace HBSoft
{

    class D3Device : public Singleton<D3Device>
    {
    public:
        ComPtr<ID3D11Device>           m_d3dDevice;
        ComPtr<ID3D11DeviceContext>    m_context;
        ComPtr<ID3D11RenderTargetView> m_rtv;  // rtv = render target view
        ComPtr<ID3D11BlendState>       m_alphaBlend;
        ComPtr<ID3D11SamplerState>     m_samplerState;
        ComPtr<IDXGISwapChain>         m_swapChain;
        ComPtr<ID2D1RenderTarget>      m_d2dRT;
        ComPtr<ID2D1Factory>           m_d2dFactory;

        D3D11_VIEWPORT       m_viewPort;
        DXGI_SWAP_CHAIN_DESC m_swapChainDesc;

    private:
        friend class Singleton<D3Device>;
        D3Device() = default;

        void OnWm_size(UINT width, UINT height);

        bool CreateDeviceAndSwapChain();
        bool CreateRenderTargetView();
        bool CreateDirect2DRenderTarget();
        bool CreateSamplerState();
        void CreateViewport();
        bool SetAlphaBlendingState();

    public:
        ~D3Device() = default;

        void SetViewportSizeOnCenter(glm::vec2 size);
        void SetViewportSizeOnLeftTop(glm::vec2 size);

        glm::vec2 GetViewportSize() const;
        bool      CreateDevice();
    };

}  // namespace HBSoft