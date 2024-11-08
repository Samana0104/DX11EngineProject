/*
author : 변한빛
description : 다이렉트 디바이스 관련 정리한 소스파일

version: 1.0.1
date: 2024-11-05
*/

#include "pch.h"
#include "D3Device.h"
using namespace HBSoft;

D3Device::D3Device(const std::shared_ptr<Window>& window)
    : m_window(window)
{
    assert(CreateDevice());
}

glm::vec2 D3Device::GetViewportSize() const
{
    return {m_viewPort.Width, m_viewPort.Height};
}

bool D3Device::CreateIndexBuffer(std::vector<size_t>& indices, ComPtr<ID3D11Buffer>& idxBuffer)
{
    if (indices.size() <= 0)
        return true;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.ByteWidth = sizeof(size_t) * (UINT)indices.size();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;


    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
    sd.pSysMem = &indices.at(0);

    HRESULT hr = m_d3dDevice->CreateBuffer(&bd, &sd, idxBuffer.GetAddressOf());

    return SUCCEEDED(hr);
}

bool D3Device::CreateDevice()
{
    if (!CreateDeviceAndSwapChain())
        return false;

    if (!CreateRenderTargetView())
        return false;

    if (!CreateSamplerState())
        return false;

    if (!SetAlphaBlendingState())
        return false;

    CreateViewport();
    return true;
}

void D3Device::OnWm_size(UINT width, UINT height)
{
    /* 해상도 자동 변경 이벤트 */
    m_context->OMSetRenderTargets(0, nullptr, nullptr);
    m_context->Flush();

    m_context->Release();
    m_rtv->Release();
    m_alphaBlend->Release();
    // m_d2dRT->Release();
    // m_d2dFactory->Release();
    m_samplerState->Release();

    m_swapChainDesc.BufferDesc.Width  = width;
    m_swapChainDesc.BufferDesc.Height = height;

    HRESULT hr = m_swapChain->ResizeBuffers(m_swapChainDesc.BufferCount,
                                            m_swapChainDesc.BufferDesc.Width,
                                            m_swapChainDesc.BufferDesc.Height,
                                            m_swapChainDesc.BufferDesc.Format,
                                            m_swapChainDesc.Flags);

    CreateRenderTargetView();
    // CreateDirect2DRenderTarget();
    CreateSamplerState();
    SetAlphaBlendingState();
    CreateViewport();
}

bool D3Device::CreateDeviceAndSwapChain()
{
    HRESULT hr;
    HPoint  windowSize = m_window->GetSize();

    CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;

    m_swapChainDesc = {};
    {
        m_swapChainDesc.OutputWindow                       = m_window->GetHandle();
        m_swapChainDesc.BufferDesc.Width                   = (UINT)windowSize.x;
        m_swapChainDesc.BufferDesc.Height                  = (UINT)windowSize.y;
        m_swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;
        m_swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        m_swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
        m_swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        m_swapChainDesc.BufferCount                        = 1;
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

bool D3Device::CreateRenderTargetView()
{
    HRESULT                 hr;
    ComPtr<ID3D11Texture2D> backBuffer;

    hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));

    if (FAILED(hr))
        return false;

    hr = m_d3dDevice->CreateRenderTargetView(reinterpret_cast<ID3D11Resource*>(backBuffer.Get()),
                                             nullptr,
                                             m_rtv.GetAddressOf());

    m_context->OMSetRenderTargets(1, m_rtv.GetAddressOf(), nullptr);

    return SUCCEEDED(hr);
}

bool D3Device::CreateSamplerState()
{
    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;  // 선형 필터링 설정
    samplerDesc.AddressU           = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV           = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW           = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc     = D3D11_COMPARISON_NEVER;
    samplerDesc.MinLOD             = 0;
    samplerDesc.MaxLOD             = D3D11_FLOAT32_MAX;

    // 샘플러 상태 객체 생성
    HRESULT hr = m_d3dDevice->CreateSamplerState(&samplerDesc, m_samplerState.GetAddressOf());
    if (FAILED(hr))
        return false;

    // 샘플러 상태를 파이프라인에 바인딩
    m_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
    return true;
}

bool D3Device::SetAlphaBlendingState()
{
    HRESULT          hr;
    D3D11_BLEND_DESC bd = {};
    {
        bd.AlphaToCoverageEnable  = FALSE;  // discard;같은 결과.
        bd.IndependentBlendEnable = FALSE;
        // D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];
        //  백버퍼의 컬러값(DestBlend) 과  현재 출력 컬러(SrcBlend)값을 혼합연산한다.
        bd.RenderTarget[0].BlendEnable = TRUE;
        // RGA 컬러값 연산( 기본 알파블랭딩 공식) 알파범위( 0 ~ 1 )
        // 최종 컬러값 = 소스컬러*소스알파 	+  데스크컬러* (1.0 - 소스알파)
        //  정점위치 = 목적지위치*S + 현재위치* (1- S); S=0, S=0.5, S = 1
        //
        // 만약 소스컬러 = 1,0,0,1(빨강)   배경컬러 = 0,0,1,1(파랑)
        // 1)소스알파 = 1.0F ( 완전불투명)
        // RGB = R*ALPHA, G = G*Alpha, B = B*Alpha
        // 최종 컬러값 = 빨강*1.0F 	+  파랑* (1.0 - 1.0F)
        // ->최종 컬러값(소스색) = [1,0,0] 	+  [0,0,0]
        // 2)소스알파 = 0.0F ( 완전투명)
        // RGB = R*ALPHA, G = G*Alpha, B = B*Alpha
        // 최종 컬러값 = 빨강*0.0F 	+  파랑* (1.0 - 0.0F)
        // ->최종 컬러값(배경색) = [0,0,0] +  [0,0,1]
        bd.RenderTarget[0].SrcBlend  = D3D11_BLEND_SRC_ALPHA;
        bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        bd.RenderTarget[0].BlendOp   = D3D11_BLEND_OP_ADD;
        // A 알파값 연산
        // A = SRC Alpha*1 + DestAlpha*0;
        bd.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ONE;
        bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        bd.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;

        bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    }

    hr = m_d3dDevice->CreateBlendState(&bd, m_alphaBlend.GetAddressOf());
    m_context->OMSetBlendState(m_alphaBlend.Get(), 0, -1);

    return SUCCEEDED(hr);
}

void D3Device::CreateViewport()
{
    HPoint windowSize = m_window->GetSize();

    m_viewPort.TopLeftX = 0;
    m_viewPort.TopLeftY = 0;
    m_viewPort.Width    = windowSize.x;
    m_viewPort.Height   = windowSize.y;
    m_viewPort.MinDepth = 0;
    m_viewPort.MaxDepth = 1;

    m_context->RSSetViewports(1, &m_viewPort);
}
