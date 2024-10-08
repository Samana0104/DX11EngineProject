#include "pch.h"
#include "D3Device.h"
using namespace HBSoft;

D3Device::~D3Device()
{
    MyWindow::GetInstance().DeleteCallBack(mWMSizeID);
}

glm::vec2 D3Device::GetViewportSize() const
{
    return {mViewPort.Width, mViewPort.Height};
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
    mWMSizeID = MyWindow::GetInstance().RegisterCallBackWMSize(
    std::bind(&D3Device::OnWMSize, this, std::placeholders::_1, std::placeholders::_2));
    return true;
}

void D3Device::OnWMSize(UINT _width, UINT _height)
{
    /* �ػ� �ڵ� ���� �̺�Ʈ */
    mContext->OMSetRenderTargets(0, nullptr, nullptr);
    mContext->Flush();

    mContext->Release();
    mRTV->Release();
    mAlphaBlend->Release();
    mD2dRT->Release();
    mD2dFactory->Release();
    mSamplerState->Release();

    mSwapChainDesc.BufferDesc.Width  = _width;
    mSwapChainDesc.BufferDesc.Height = _height;

    HRESULT hr = mSwapChain->ResizeBuffers(mSwapChainDesc.BufferCount,
                                           mSwapChainDesc.BufferDesc.Width,
                                           mSwapChainDesc.BufferDesc.Height,
                                           mSwapChainDesc.BufferDesc.Format,
                                           mSwapChainDesc.Flags);

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

    mSwapChainDesc = {};
    {
        mSwapChainDesc.OutputWindow                     = MyWindow::GetInstance().GetWindowHandle();
        mSwapChainDesc.BufferDesc.Width                 = MyWindow::GetInstance().GetWindowSize().x;
        mSwapChainDesc.BufferDesc.Height                = MyWindow::GetInstance().GetWindowSize().y;
        mSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        mSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        mSwapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
        mSwapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        mSwapChainDesc.BufferCount                        = 1;
        mSwapChainDesc.Windowed                           = true;
        mSwapChainDesc.SampleDesc.Count                   = 1;
    }

    hr = D3D11CreateDeviceAndSwapChain(nullptr,
                                       D3D_DRIVER_TYPE_HARDWARE,
                                       nullptr,
                                       D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                                       &pFeatureLevels,
                                       1,
                                       D3D11_SDK_VERSION,
                                       &mSwapChainDesc,
                                       mSwapChain.GetAddressOf(),
                                       mD3dDevice.GetAddressOf(),
                                       nullptr,
                                       mContext.GetAddressOf());

    return SUCCEEDED(hr);
}

bool D3Device::CreateRenderTargetView()
{
    HRESULT                 hr;
    ComPtr<ID3D11Texture2D> backBuffer;

    hr = mSwapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));

    if (FAILED(hr))
        return false;

    hr = mD3dDevice->CreateRenderTargetView(reinterpret_cast<ID3D11Resource*>(backBuffer.Get()),
                                            nullptr,
                                            mRTV.GetAddressOf());

    mContext->OMSetRenderTargets(1, mRTV.GetAddressOf(), nullptr);

    return SUCCEEDED(hr);
}

bool D3Device::CreateDirect2DRenderTarget()
{
    HRESULT              hr;
    ComPtr<IDXGISurface> dxgiSurface;

    hr = mSwapChain->GetBuffer(0, IID_PPV_ARGS(dxgiSurface.GetAddressOf()));

    if (FAILED(hr))
        return false;

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mD2dFactory.GetAddressOf());

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

    hr = mD2dFactory->CreateDxgiSurfaceRenderTarget(dxgiSurface.Get(), &rtp, mD2dRT.GetAddressOf());

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
    HRESULT hr = mD3dDevice->CreateSamplerState(&samplerDesc, mSamplerState.GetAddressOf());
    if (FAILED(hr))
        return false;

    // ���÷� ���¸� ���������ο� ���ε�
    mContext->PSSetSamplers(0, 1, mSamplerState.GetAddressOf());
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

    hr = mD3dDevice->CreateBlendState(&bd, mAlphaBlend.GetAddressOf());
    mContext->OMSetBlendState(mAlphaBlend.Get(), 0, -1);

    return SUCCEEDED(hr);
}

void D3Device::CreateViewport()
{
    auto windowSize = MyWindow::GetInstance().GetWindowSizeF();
    {
        mViewPort.TopLeftX = 0;
        mViewPort.TopLeftY = 0;
        mViewPort.Width    = windowSize.x;
        mViewPort.Height   = windowSize.y;
        mViewPort.MinDepth = 0;
        mViewPort.MaxDepth = 1;
    }

    mContext->RSSetViewports(1, &mViewPort);
}

void D3Device::SetViewportSizeOnCenter(glm::vec2 _size)
{
    auto windowSize = MyWindow::GetInstance().GetWindowSizeVec2();

    mViewPort.TopLeftX = windowSize.x * 0.5f - _size.x * 0.5f;
    mViewPort.TopLeftY = windowSize.y * 0.5f - _size.y * 0.5f;
    mViewPort.Width    = _size.x;
    mViewPort.Height   = _size.y;
    mViewPort.MinDepth = 0;
    mViewPort.MaxDepth = 1;

    mContext->RSSetViewports(1, &mViewPort);
}

void D3Device::SetViewportSizeOnLeftTop(glm::vec2 _size)
{
    mViewPort.TopLeftX = 0;
    mViewPort.TopLeftY = 0;
    mViewPort.Width    = _size.x;
    mViewPort.Height   = _size.y;
    mViewPort.MinDepth = 0;
    mViewPort.MaxDepth = 1;

    mContext->RSSetViewports(1, &mViewPort);
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
