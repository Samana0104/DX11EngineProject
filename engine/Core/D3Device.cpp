/*
author : 변한빛
description : 다이렉트 디바이스 관련 정리한 소스파일

version: 1.0.5
date: 2024-11-15
*/

#include "pch.h"
#include "D3Device.h"
using namespace HBSoft;

D3Device::D3Device(const std::shared_ptr<Window> window)
    : m_window(window)
{
    assert(CreateDevice());
    EventHandler::GetInstance().AddEvent(EventList::WINDOW_RESIZE, this);
}

D3Device::~D3Device()
{
    EventHandler::GetInstance().DeleteEvent(EventList::WINDOW_RESIZE, this);
}

bool D3Device::CreateIndexBuffer(std::vector<UINT>& indices, ComPtr<ID3D11Buffer>& indexBuffer)
{
    if (indices.size() <= 0)
        return true;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(UINT) * (UINT)indices.size();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;


    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = &indices.at(0);

    HRESULT hr = m_d3dDevice->CreateBuffer(&bd, &sd, indexBuffer.GetAddressOf());

    return SUCCEEDED(hr);
}

bool D3Device::CreateDevice()
{
    if (!CreateDeviceAndSwapChain())
        return false;

    if (!CreateRenderTarget())
        return false;

    if (!Create2DRenderTarget())
        return false;

    if (!CreateSamplerState())
        return false;

    if (!CreateDepthStencilState())
        return false;

    if (!CreateDepthStencilView())
        return false;

    if (!CreateRSState())
        return false;

    if (!CreateBlendingState())
        return false;

    CreateViewport();
    return true;
}

bool D3Device::CreateDeviceAndSwapChain()
{
    HRESULT hr;
    HPoint  windowSize = m_window->GetWindowSize();

    CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;

    ZeroMemory(&m_swapChainDesc, sizeof(m_swapChainDesc));
    {
        m_swapChainDesc.BufferDesc.Width                   = (UINT)windowSize.x;
        m_swapChainDesc.BufferDesc.Height                  = (UINT)windowSize.y;
        m_swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;
        m_swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        m_swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        m_swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        m_swapChainDesc.BufferCount                        = 1;
        m_swapChainDesc.OutputWindow                       = m_window->GetHandle();
        m_swapChainDesc.Windowed                           = true;
        m_swapChainDesc.SampleDesc.Count                   = 1;
    }

    hr = D3D11CreateDeviceAndSwapChain(nullptr,
                                       D3D_DRIVER_TYPE_HARDWARE,
                                       nullptr,
                                       D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                                       &pFeatureLevels,
                                       1,
                                       D3D11_SDK_VERSION,
                                       &m_swapChainDesc,
                                       m_swapChain.GetAddressOf(),
                                       m_d3dDevice.GetAddressOf(),
                                       nullptr,
                                       m_context.GetAddressOf());

    return SUCCEEDED(hr);
}

bool D3Device::CreateRenderTarget()
{
    HRESULT                 hr;
    ComPtr<ID3D11Texture2D> backBuffer;

    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(textureDesc));
    textureDesc.Width            = m_swapChainDesc.BufferDesc.Width;
    textureDesc.Height           = m_swapChainDesc.BufferDesc.Height;
    textureDesc.MipLevels        = 1;
    textureDesc.ArraySize        = 1;
    textureDesc.Format           = m_swapChainDesc.BufferDesc.Format;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage            = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

    hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));

    if (FAILED(hr))
        return false;

    hr = m_d3dDevice->CreateRenderTargetView(reinterpret_cast<ID3D11Texture2D*>(backBuffer.Get()),
                                             nullptr,
                                             m_multiRT[MultiRT::MAIN].rtv.GetAddressOf());
    if (FAILED(hr))
        return false;

    m_multiRT[MultiRT::MAIN].texRt = backBuffer;

    // 0번은 백버퍼 전용 렌더타겟임
    for (int i = 1; i < MAX_RENDER_TARGET; i++)
    {
        hr = m_d3dDevice->CreateTexture2D(&textureDesc, nullptr, m_multiRT[i].texRt.GetAddressOf());

        if (FAILED(hr))
            return false;

        hr = m_d3dDevice->CreateRenderTargetView(m_multiRT[i].texRt.Get(),
                                                 nullptr,
                                                 m_multiRT[i].rtv.GetAddressOf());
        if (FAILED(hr))
            return false;

        hr = m_d3dDevice->CreateShaderResourceView(m_multiRT[i].texRt.Get(),
                                                   nullptr,
                                                   m_multiRT[i].rtSrv.GetAddressOf());
        if (FAILED(hr))
            return false;
    }

    return SUCCEEDED(hr);
}

bool D3Device::Create2DRenderTarget()
{
    HRESULT              hr;
    ComPtr<IDXGISurface> dxgiSurface;
    ComPtr<ID2D1Factory> m_d2dFactory;

    hr = m_multiRT[MultiRT::GUI].texRt.As(&dxgiSurface);

    if (FAILED(hr))
        return false;

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, m_d2dFactory.GetAddressOf());

    if (FAILED(hr))
        return false;

    D2D1_RENDER_TARGET_PROPERTIES rtp;
    {
        rtp.type                  = D2D1_RENDER_TARGET_TYPE_DEFAULT;
        rtp.pixelFormat.format    = DXGI_FORMAT_UNKNOWN;
        rtp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        rtp.dpiX                  = 0;
        rtp.dpiY                  = 0;
        rtp.usage                 = D2D1_RENDER_TARGET_USAGE_NONE;
        rtp.minLevel              = D2D1_FEATURE_LEVEL_DEFAULT;
    }

    hr = m_d2dFactory->CreateDxgiSurfaceRenderTarget(dxgiSurface.Get(), &rtp, m_2dRtv.GetAddressOf());

    return SUCCEEDED(hr);
}

bool D3Device::CreateSamplerState()
{
    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    {
        samplerDesc.Filter         = D3D11_FILTER_MIN_MAG_MIP_POINT;  // 선형 필터링 설정
        samplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        samplerDesc.MaxLOD         = FLT_MAX;
        samplerDesc.MinLOD         = FLT_MIN;
    }

    // 샘플러 상태 객체 생성
    HRESULT hr =
    m_d3dDevice->CreateSamplerState(&samplerDesc, m_renderState.pointSampler.GetAddressOf());
    if (FAILED(hr))
        return false;

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

    hr = m_d3dDevice->CreateSamplerState(&samplerDesc, m_renderState.linearSampler.GetAddressOf());
    if (FAILED(hr))
        return false;

    samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;

    hr = m_d3dDevice->CreateSamplerState(&samplerDesc, m_renderState.anisotropicSampler.GetAddressOf());
    if (FAILED(hr))
        return false;

    return true;
}

bool D3Device::CreateRSState()
{
    HRESULT               hr;
    D3D11_RASTERIZER_DESC rd;

    ZeroMemory(&rd, sizeof(rd));
    rd.FillMode        = D3D11_FILL_SOLID;
    rd.CullMode        = D3D11_CULL_BACK;  // backface culling
    rd.DepthClipEnable = TRUE;
    hr = m_d3dDevice->CreateRasterizerState(&rd, m_renderState.solidBackCullRS.GetAddressOf());

    if (FAILED(hr))
        return false;

    rd.CullMode = D3D11_CULL_FRONT;
    hr          = m_d3dDevice->CreateRasterizerState(&rd, m_renderState.solidFrontCullRS.GetAddressOf());

    if (FAILED(hr))
        return false;

    rd.CullMode = D3D11_CULL_NONE;
    hr          = m_d3dDevice->CreateRasterizerState(&rd, m_renderState.solidNoCullRS.GetAddressOf());

    if (FAILED(hr))
        return false;

    rd.FillMode = D3D11_FILL_WIREFRAME;
    rd.CullMode = D3D11_CULL_BACK;
    hr          = m_d3dDevice->CreateRasterizerState(&rd, m_renderState.wireBackCullRS.GetAddressOf());

    if (FAILED(hr))
        return false;

    rd.CullMode = D3D11_CULL_FRONT;
    hr          = m_d3dDevice->CreateRasterizerState(&rd, m_renderState.wireFrontCullRS.GetAddressOf());

    if (FAILED(hr))
        return false;

    rd.CullMode = D3D11_CULL_NONE;
    hr          = m_d3dDevice->CreateRasterizerState(&rd, m_renderState.wireNoCullRS.GetAddressOf());

    return SUCCEEDED(hr);
}

bool D3Device::CreateDepthStencilState()
{
    HRESULT                  hr;
    D3D11_DEPTH_STENCIL_DESC dsDesc;

    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.DepthEnable                  = FALSE;
    dsDesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc                    = D3D11_COMPARISON_LESS_EQUAL;
    dsDesc.StencilEnable                = FALSE;
    dsDesc.StencilReadMask              = 0xff;
    dsDesc.StencilWriteMask             = 0xff;
    dsDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_INCR;
    dsDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;
    dsDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_KEEP;

    hr = m_d3dDevice->CreateDepthStencilState(&dsDesc, m_renderState.disableDSS.GetAddressOf());

    if (FAILED(hr))
        return false;

    dsDesc.DepthEnable = TRUE;
    hr = m_d3dDevice->CreateDepthStencilState(&dsDesc, m_renderState.lessDSS.GetAddressOf());

    if (FAILED(hr))
        return false;

    dsDesc.DepthFunc = D3D11_COMPARISON_GREATER;
    hr = m_d3dDevice->CreateDepthStencilState(&dsDesc, m_renderState.greaterDSS.GetAddressOf());

    if (FAILED(hr))
        return false;

    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    hr = m_d3dDevice->CreateDepthStencilState(&dsDesc, m_renderState.noWriteDSS.GetAddressOf());

    return SUCCEEDED(hr);
}

bool D3Device::CreateDepthStencilView()
{
    HRESULT                       hr;
    D3D11_TEXTURE2D_DESC          td;
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;

    ZeroMemory(&td, sizeof(td));

    td.Width            = m_swapChainDesc.BufferDesc.Width;
    td.Height           = m_swapChainDesc.BufferDesc.Height;
    td.MipLevels        = 1;
    td.ArraySize        = 1;
    td.Format           = DXGI_FORMAT_R24G8_TYPELESS;  // D,S
    td.SampleDesc.Count = 1;
    td.Usage            = D3D11_USAGE_DEFAULT;
    td.BindFlags        = D3D11_BIND_DEPTH_STENCIL;

    ZeroMemory(&dsvDesc, sizeof(dsvDesc));
    dsvDesc.Format        = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    for (int i = 0; i < MAX_RENDER_TARGET; i++)
    {
        hr = m_d3dDevice->CreateTexture2D(&td, nullptr, m_multiRT[i].dsRt.GetAddressOf());
        if (FAILED(hr))
            return false;

        hr = m_d3dDevice->CreateDepthStencilView(m_multiRT[i].dsRt.Get(),
                                                 &dsvDesc,
                                                 m_multiRT[i].dsv.GetAddressOf());
    }

    return SUCCEEDED(hr);
}

bool D3Device::CreateBlendingState()
{
    HRESULT          hr;
    D3D11_BLEND_DESC bd = {};
    {
        bd.AlphaToCoverageEnable  = FALSE;  // discard;같은 결과.
        bd.IndependentBlendEnable = FALSE;
        // D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];
        //  백버퍼의 컬러값(DestBlend) 과  현재 출력 컬러(SrcBlend)값을 혼합연산한다.
        bd.RenderTarget[0].BlendEnable = TRUE;
        bd.RenderTarget[0].SrcBlend    = D3D11_BLEND_SRC_ALPHA;
        bd.RenderTarget[0].DestBlend   = D3D11_BLEND_INV_SRC_ALPHA;
        bd.RenderTarget[0].BlendOp     = D3D11_BLEND_OP_ADD;
        // A 알파값 연산
        // A = SRC Alpha*1 + DestAlpha*0;
        bd.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ONE;
        bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        bd.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;

        bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    }

    hr = m_d3dDevice->CreateBlendState(&bd, m_renderState.alphaBS.GetAddressOf());

    return SUCCEEDED(hr);
}

void D3Device::OnNotice(EventList event, void* entity)
{
    HPoint windowSize = m_window->GetWindowSize();

    m_context->Flush();
    m_context->OMSetRenderTargets(0, nullptr, nullptr);
    m_2dRtv->Release();

    // 백버퍼 초기화는 다른자원에게 맡기기
    if (m_multiRT[MultiRT::MAIN].texRt != nullptr)
        m_multiRT[MultiRT::MAIN].texRt = nullptr;

    if (m_multiRT[MultiRT::MAIN].dsv != nullptr)
        m_multiRT[MultiRT::MAIN].dsv->Release();


    if (m_multiRT[MultiRT::MAIN].dsRt != nullptr)
        m_multiRT[MultiRT::MAIN].dsRt->Release();

    for (int i = 0; i < MAX_RENDER_TARGET; i++)
    {
        if (m_multiRT[i].rtSrv != nullptr)
            m_multiRT[i].rtSrv->Release();

        if (m_multiRT[i].rtv != nullptr)
            m_multiRT[i].rtv->Release();

        if (m_multiRT[i].dsv != nullptr)
            m_multiRT[i].dsv->Release();

        if (m_multiRT[i].texRt != nullptr)
            m_multiRT[i].texRt->Release();
    }

    m_swapChainDesc.BufferDesc.Width  = (UINT)windowSize.x;
    m_swapChainDesc.BufferDesc.Height = (UINT)windowSize.y;

    HRESULT hr = m_swapChain->ResizeBuffers(m_swapChainDesc.BufferCount,
                                            m_swapChainDesc.BufferDesc.Width,
                                            m_swapChainDesc.BufferDesc.Height,
                                            m_swapChainDesc.BufferDesc.Format,
                                            m_swapChainDesc.Flags);

    // if (FAILED(hr))
    //     return;

    CreateViewport();
    CreateRenderTarget();
    Create2DRenderTarget();
    CreateDepthStencilView();

    EventHandler::GetInstance().Notify(EventList::DEVICE_CHANGE, this);
}

void D3Device::CreateViewport()
{
    HPoint windowSize = m_window->GetWindowSize();

    for (int i = 0; i < MAX_RENDER_TARGET; i++)
    {
        m_multiRT[i].viewPort.TopLeftX = 0;
        m_multiRT[i].viewPort.TopLeftY = 0;
        m_multiRT[i].viewPort.Width    = windowSize.x;
        m_multiRT[i].viewPort.Height   = windowSize.y;
        m_multiRT[i].viewPort.MinDepth = 0;
        m_multiRT[i].viewPort.MaxDepth = 1;
    }
}
