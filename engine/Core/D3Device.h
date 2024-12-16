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
#define MAX_RENDER_TARGET 5

    enum MultiRT
    {
        MAIN   = 0,
        GUI    = 1,
        SHADOW = 2,
        SUB1   = 3,
        SUB2   = 4,
    };

    struct HRenderTarget
    {
        ComPtr<ID3D11Texture2D>        texRt;
        ComPtr<ID3D11Texture2D>        dsRt;
        ComPtr<ID3D11RenderTargetView> rtv;
        ComPtr<ID3D11DepthStencilView> dsv;

        ComPtr<ID3D11ShaderResourceView> rtSrv;
        // ComPtr<ID3D11ShaderResourceView> dsSrv; 필요하면 만듬

        D3D11_VIEWPORT viewPort;
    };

    struct HRenderState
    {
        ComPtr<ID3D11BlendState> alphaBS;

        ComPtr<ID3D11SamplerState> pointSampler;
        ComPtr<ID3D11SamplerState> linearSampler;
        ComPtr<ID3D11SamplerState> anisotropicSampler;

        ComPtr<ID3D11RasterizerState> solidBackCullRS;
        ComPtr<ID3D11RasterizerState> solidFrontCullRS;
        ComPtr<ID3D11RasterizerState> solidNoCullRS;
        ComPtr<ID3D11RasterizerState> wireBackCullRS;
        ComPtr<ID3D11RasterizerState> wireFrontCullRS;
        ComPtr<ID3D11RasterizerState> wireNoCullRS;

        ComPtr<ID3D11DepthStencilState> lessDSS;
        ComPtr<ID3D11DepthStencilState> greaterDSS;
        ComPtr<ID3D11DepthStencilState> noWriteDSS;
        ComPtr<ID3D11DepthStencilState> disableDSS;
    };

    class D3Device : public Observer
    {
    public:
        ComPtr<ID3D11Device>        m_d3dDevice;
        ComPtr<ID3D11DeviceContext> m_context;
        ComPtr<IDXGISwapChain>      m_swapChain;

        ComPtr<ID2D1RenderTarget> m_2dRtv;  // 2d surface rtv is made by gui texture buffer

        HRenderTarget m_multiRT[MAX_RENDER_TARGET];
        HRenderState  m_renderState;

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