/*
author : 변한빛
description : 픽셀 쉐이더의 기본 정의를 하기 위해 만든 소스 파일

version: 1.0.3
date: 2024-11-09
*/

#include "pch.h"
#include "PixelShader.h"
using namespace HBSoft;

PixelShader::PixelShader(std::shared_ptr<D3Device>& device, const wstringV path, const ShaderType& type)
    : Shader(path, type)
{
    assert(CreateShader(device));
}

bool PixelShader::CreateShader(std::shared_ptr<D3Device>& device)
{
    HRESULT          hr;
    ComPtr<ID3DBlob> errorMsg;

    UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    compileFlags |= D3DCOMPILE_DEBUG;
#endif

    hr = D3DCompileFromFile(m_path.c_str(),
                            nullptr,
                            D3D_COMPILE_STANDARD_FILE_INCLUDE,
                            "main",
                            "ps_5_0",  // dx11 정점쉐이더 컴파일러
                            compileFlags,
                            0,
                            m_shaderByteCode.GetAddressOf(),
                            errorMsg.GetAddressOf());

    if (FAILED(hr))
    {
        MessageBoxA(NULL, (char*)errorMsg->GetBufferPointer(), "PixelShader error", MB_OK);
        return false;
    }

    hr = device->m_d3dDevice->CreatePixelShader(m_shaderByteCode->GetBufferPointer(),
                                                m_shaderByteCode->GetBufferSize(),
                                                nullptr,
                                                m_pixelShader.GetAddressOf());

    return SUCCEEDED(hr);
}

// void PixelShader::SetUpConfiguration() const
//{
//     HDEVICE->m_context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
// }
