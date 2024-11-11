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

ComPtr<ID3D11PixelShader> PixelShader::GetPixselShader()
{
    return m_pixelShader;
}

ComPtr<ID3D11VertexShader> PixelShader::GetVertexShader()
{
    return nullptr;
}

ComPtr<ID3D11InputLayout> PixelShader::GetIALayout()
{
    return nullptr;
}

bool PixelShader::CreateShader(std::shared_ptr<D3Device>& device)
{
    if (!CreatePixelShader(device))
        return false;

    if (!CreateConstantBuffer(device))
        return false;

    return true;
}

bool PixelShader::CreateConstantBuffer(std::shared_ptr<D3Device>& device)
{
    HRESULT hr;

    ID3D11ShaderReflection* pReflector = nullptr;

    hr = D3DReflect((void*)m_shaderByteCode->GetBufferPointer(),
                    m_shaderByteCode->GetBufferSize(),
                    IID_ID3D11ShaderReflection,
                    (void**)&pReflector);

    if (FAILED(hr))
        return false;

    // 셰이더 디스크립션 가져오기
    D3D11_SHADER_DESC shaderDesc;
    pReflector->GetDesc(&shaderDesc);

    m_constantBuffers.resize(shaderDesc.ConstantBuffers);

    for (UINT i = 0; i < shaderDesc.ConstantBuffers; ++i)
    {
        ID3D11ShaderReflectionConstantBuffer* pCB = pReflector->GetConstantBufferByIndex(i);
        D3D11_SHADER_BUFFER_DESC              cbDesc;
        pCB->GetDesc(&cbDesc);

        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.ByteWidth         = cbDesc.Size;
        bufferDesc.Usage             = D3D11_USAGE_DYNAMIC;
        bufferDesc.CPUAccessFlags    = D3D11_CPU_ACCESS_WRITE;

        ComPtr<ID3D11Buffer> constantBuffer = nullptr;
        hr = device->m_d3dDevice->CreateBuffer(&bufferDesc, nullptr, constantBuffer.GetAddressOf());

        if (FAILED(hr))
            return false;

        m_constantBuffers.push_back(constantBuffer);
    }

    return true;
}

bool PixelShader::CreatePixelShader(std::shared_ptr<D3Device>& device)
{
    HRESULT          hr;
    ComPtr<ID3DBlob> errorMsg;

    UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    compileFlags = compileFlags | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
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
