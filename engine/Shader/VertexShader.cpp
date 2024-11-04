/*
author : 변한빛
description : 버텍스 쉐이더를 정의하기 위한 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "VertexShader.h"
using namespace HBSoft;

VertexShader::VertexShader(const ShaderDesc& _desc)
    : Shader(_desc)
{
#ifdef _DEBUG
    _ASSERT(CreateShader());
#else
    CreateShader();
#endif
    SetUpConfiguration();
}

bool VertexShader::CreateVertexShader()
{
    HRESULT          hr;
    ComPtr<ID3DBlob> errorMsg;

    hr = D3DCompileFromFile(m_shaderDesc.m_shaderPath.c_str(),
                            nullptr,
                            nullptr,
                            m_shaderDesc.m_shaderEntry.c_str(),
                            "vs_5_0",  // dx11 정점쉐이더 컴파일러
                            0,
                            0,
                            m_shaderByteCode.GetAddressOf(),
                            errorMsg.GetAddressOf());

    if (FAILED(hr))
    {
        MessageBoxA(NULL, (char*)errorMsg->GetBufferPointer(), "VertexShader error", MB_OK);
        return false;
    }

    hr = m_device.m_d3dDevice->CreateVertexShader(m_shaderByteCode->GetBufferPointer(),
                                                  m_shaderByteCode->GetBufferSize(),
                                                  nullptr,
                                                  mVertexShader.GetAddressOf());

    return SUCCEEDED(hr);
}

bool VertexShader::CreateIALayout()
{
    const D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0,       DXGI_FORMAT_R32G32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {   "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  8, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {     "TEX", 0,       DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    UINT    NumElements = sizeof(layout) / sizeof(layout[0]);
    HRESULT hr          = m_device.m_d3dDevice->CreateInputLayout(layout,
                                                         NumElements,
                                                         m_shaderByteCode->GetBufferPointer(),
                                                         m_shaderByteCode->GetBufferSize(),
                                                         mVertexLayout.GetAddressOf());

    return SUCCEEDED(hr);
}

bool VertexShader::CreateShader()
{
    if (!CreateVertexShader())
        return false;

    if (!CreateIALayout())
        return false;

    return true;
}

void VertexShader::SetUpConfiguration() const
{
    m_device.m_context->IASetInputLayout(mVertexLayout.Get());
    m_device.m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_device.m_context->VSSetShader(mVertexShader.Get(), nullptr, 0);
}
