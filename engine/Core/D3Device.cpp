#include "pch.h"
#include "D3Device.h"
using namespace HBSoft;

D3Device::~D3Device()
{
    Window::GetInstance().DeleteCallBack(m_wm_sizeID);
}

glm::vec2 D3Device::GetViewportSize() const
{
    return {m_viewPort.Width, m_viewPort.Height};
}

bool D3Device::CreateDevice()
{
    if (!CreateDeviceAndSwapChain())
        return false;

    if (!CreateRenderTargetView())
        return false;

    if (!CreateDirect2DRenderTarget())
        return false;

    if (!CreateSamplerState())
        return false;

    if (!SetAlphaBlendingState())
        return false;

    CreateViewport();
    m_wm_sizeID = Window::GetInstance().RegisterCallBackWm_size(
    std::bind(&D3Device::OnWm_size, this, std::placeholders::_1, std::placeholders::_2));
    return true;
}

void D3Device::OnWm_size(UINT _width, UINT _height)
{
    /* �ػ� �ڵ� ���� �̺�Ʈ */
    m_context->OMSetRenderTargets(0, nullptr, nullptr);
    m_context->Flush();

    m_context->Release();
    m_rtv->Release();
    m_alphaBlend->Release();
    m_d2dRT->Release();
    m_d2dFactory->Release();
    m_samplerState->Release();

    m_swapChainDesc.BufferDesc.Width  = _width;
    m_swapChainDesc.BufferDesc.Height = _height;

    HRESULT hr = m_swapChain->ResizeBuffers(m_swapChainDesc.BufferCount,
                                            m_swapChainDesc.BufferDesc.Width,
                                            m_swapChainDesc.BufferDesc.Height,
                                            m_swapChainDesc.BufferDesc.Format,
                                            m_swapChainDesc.Flags);

    CreateRenderTargetView();
    CreateDirect2DRenderTarget();
    CreateSamplerState();
    SetAlphaBlendingState();
    CreateViewport();
}

bool D3Device::CreateDeviceAndSwapChain()
{
    HRESULT                 hr;
    CONST D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;

    m_swapChainDesc = {};
    {
        m_swapChainDesc.OutputWindow                       = Window::GetInstance().GetWindowHandle();
        m_swapChainDesc.BufferDesc.Width                   = Window::GetInstance().GetWindowSize().x;
        m_swapChainDesc.BufferDesc.Height                  = Window::GetInstance().GetWindowSize().y;
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

bool D3Device::CreateDirect2DRenderTarget()
{
    HRESULT              hr;
    ComPtr<IDXGISurface> dxgiSurface;

    hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(dxgiSurface.GetAddressOf()));

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

    hr = m_d2dFactory->CreateDxgiSurfaceRenderTarget(dxgiSurface.Get(), &rtp, m_d2dRT.GetAddressOf());

    return SUCCEEDED(hr);
}

bool D3Device::CreateSamplerState()
{
    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;  // ���� ���͸� ����
    samplerDesc.AddressU           = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV           = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW           = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc     = D3D11_COMPARISON_NEVER;
    samplerDesc.MinLOD             = 0;
    samplerDesc.MaxLOD             = D3D11_FLOAT32_MAX;

    // ���÷� ���� ��ü ����
    HRESULT hr = m_d3dDevice->CreateSamplerState(&samplerDesc, m_samplerState.GetAddressOf());
    if (FAILED(hr))
        return false;

    // ���÷� ���¸� ���������ο� ���ε�
    m_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
    return true;
}

bool D3Device::SetAlphaBlendingState()
{
    HRESULT          hr;
    D3D11_BLEND_DESC bd = {};
    {
        bd.AlphaToCoverageEnable  = FALSE;  // discard;���� ���.
        bd.IndependentBlendEnable = FALSE;
        // D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];
        //  ������� �÷���(DestBlend) ��  ���� ��� �÷�(SrcBlend)���� ȥ�տ����Ѵ�.
        bd.RenderTarget[0].BlendEnable = TRUE;
        // RGA �÷��� ����( �⺻ ���ĺ��� ����) ���Ĺ���( 0 ~ 1 )
        // ���� �÷��� = �ҽ��÷�*�ҽ����� 	+  ����ũ�÷�* (1.0 - �ҽ�����)
        //  ������ġ = ��������ġ*S + ������ġ* (1- S); S=0, S=0.5, S = 1
        //
        // ���� �ҽ��÷� = 1,0,0,1(����)   ����÷� = 0,0,1,1(�Ķ�)
        // 1)�ҽ����� = 1.0F ( ����������)
        // RGB = R*ALPHA, G = G*Alpha, B = B*Alpha
        // ���� �÷��� = ����*1.0F 	+  �Ķ�* (1.0 - 1.0F)
        // ->���� �÷���(�ҽ���) = [1,0,0] 	+  [0,0,0]
        // 2)�ҽ����� = 0.0F ( ��������)
        // RGB = R*ALPHA, G = G*Alpha, B = B*Alpha
        // ���� �÷��� = ����*0.0F 	+  �Ķ�* (1.0 - 0.0F)
        // ->���� �÷���(����) = [0,0,0] +  [0,0,1]
        bd.RenderTarget[0].SrcBlend  = D3D11_BLEND_SRC_ALPHA;
        bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        bd.RenderTarget[0].BlendOp   = D3D11_BLEND_OP_ADD;
        // A ���İ� ����
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
    auto WindowSize = Window::GetInstance().GetWindowSizeF();
    {
        m_viewPort.TopLeftX = 0;
        m_viewPort.TopLeftY = 0;
        m_viewPort.Width    = WindowSize.x;
        m_viewPort.Height   = WindowSize.y;
        m_viewPort.MinDepth = 0;
        m_viewPort.MaxDepth = 1;
    }

    m_context->RSSetViewports(1, &m_viewPort);
}

void D3Device::SetViewportSizeOnCenter(glm::vec2 _size)
{
    auto WindowSize = Window::GetInstance().GetWindowSizeVec2();

    m_viewPort.TopLeftX = WindowSize.x * 0.5f - _size.x * 0.5f;
    m_viewPort.TopLeftY = WindowSize.y * 0.5f - _size.y * 0.5f;
    m_viewPort.Width    = _size.x;
    m_viewPort.Height   = _size.y;
    m_viewPort.MinDepth = 0;
    m_viewPort.MaxDepth = 1;

    m_context->RSSetViewports(1, &m_viewPort);
}

void D3Device::SetViewportSizeOnLeftTop(glm::vec2 _size)
{
    m_viewPort.TopLeftX = 0;
    m_viewPort.TopLeftY = 0;
    m_viewPort.Width    = _size.x;
    m_viewPort.Height   = _size.y;
    m_viewPort.MinDepth = 0;
    m_viewPort.MaxDepth = 1;

    m_context->RSSetViewports(1, &m_viewPort);
}

void D3Device::SetViewportSize(ViewType _viewType, glm::vec2 _size)
{
    switch (_viewType)
    {
    case ViewType::CENTER:
        SetViewportSizeOnCenter(_size);
        break;
    case ViewType::LEFT_TOP:
        SetViewportSizeOnLeftTop(_size);
    }
}
