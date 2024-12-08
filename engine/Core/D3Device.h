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
#include "Observer.h"

namespace HBSoft
{
    class D3Device : public Observer
    {
    public:
        ComPtr<ID3D11Device>            m_d3dDevice;
        ComPtr<ID3D11DeviceContext>     m_context;
        ComPtr<ID3D11RenderTargetView>  m_rtv;  // rtv = render target view
        ComPtr<ID2D1RenderTarget>       m_2dRtv;
        ComPtr<ID3D11BlendState>        m_alphaBlend;
        ComPtr<ID3D11SamplerState>      m_samplerState;
        ComPtr<IDXGISwapChain>          m_swapChain;
        ComPtr<ID3D11RasterizerState>   m_rsState;
        ComPtr<ID3D11RasterizerState>   m_rsWireState;
        ComPtr<ID3D11DepthStencilState> m_dsState;
        ComPtr<ID3D11DepthStencilView>  m_dsv;

        D3D11_VIEWPORT          m_viewPort;
        DXGI_SWAP_CHAIN_DESC    m_swapChainDesc;
        std::shared_ptr<Window> m_window;

    private:
        bool CreateDevice();
        bool CreateDeviceAndSwapChain();
        bool CreateRenderTarget();
        bool Create2DRenderTarget();
        bool CreateSamplerState();
        bool CreateRSState();
        bool CreateDepthStencilState();
        bool CreateDepthStencilView();
        void CreateViewport();
        bool CreateBlendingState();

        virtual void OnNotice(EventList event, void* entity) override;

    public:
        D3Device(const std::shared_ptr<Window> window);
        virtual ~D3Device();

        vec2 GetViewportSize() const;

        template <class T>
        bool CreateVertexBuffer(std::vector<T>& vertices, ComPtr<ID3D11Buffer>& vertexBuffer);
        bool CreateIndexBuffer(std::vector<UINT>& indices, ComPtr<ID3D11Buffer>& indexBuffer);
    };

    template <class T>
    bool D3Device::CreateVertexBuffer(std::vector<T>& vertices, ComPtr<ID3D11Buffer>& vertexBuffer)
    {
        if (vertices.size() == 0)
            return false;

        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
        bd.ByteWidth = sizeof(T) * (UINT)vertices.size();
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;


        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
        sd.pSysMem = &vertices.at(0);

        HRESULT hr = m_d3dDevice->CreateBuffer(&bd, &sd, vertexBuffer.GetAddressOf());

        return SUCCEEDED(hr);
    }

}  // namespace HBSoft