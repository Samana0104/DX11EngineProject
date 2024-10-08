#include "pch.h"
#include "PixelShader.h"
using namespace HBSoft;

PixelShader::PixelShader(const ShaderDesc& _desc)
    : Shader(_desc)
{
#ifdef _DEBUG
    _ASSERT(CreateShader());
#else
    CreateShader();
#endif
    SetUpConfiguration();
}

bool PixelShader::CreatePixelShader()
{
    HRESULT          hr;
    ComPtr<ID3DBlob> errorMsg;

    hr = D3DCompileFromFile(m_shaderDesc.m_shaderPath.c_str(),
                            nullptr,
                            nullptr,
                            m_shaderDesc.m_shaderEntry.c_str(),
                            "ps_5_0",  // dx11 정점쉐이더 컴파일러
                            0,
                            0,
                            m_shaderByteCode.GetAddressOf(),
                            errorMsg.GetAddressOf());

    if (FAILED(hr))
    {
        MessageBoxA(NULL, (char*)errorMsg->GetBufferPointer(), "PixelShader error", MB_OK);
        return false;
    }

    m_device.m_d3dDevice->CreatePixelShader(m_shaderByteCode->GetBufferPointer(),
                                          m_shaderByteCode->GetBufferSize(),
                                          nullptr,
                                          mPixelShader.GetAddressOf());

    return SUCCEEDED(hr);
}

bool PixelShader::CreateShader()
{
    if (!CreatePixelShader())
        return false;

    return true;
}

void PixelShader::SetUpConfiguration() const
{
    m_device.m_context->PSSetShader(mPixelShader.Get(), nullptr, 0);
}
