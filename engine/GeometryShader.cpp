/*
author : ���Ѻ�
description : ���� ���̴��� �⺻ ���Ǹ� �ϱ� ���� ���� �ҽ� ����

version: 1.0.0
date: 2024-12-17
*/

#include "pch.h"
#include "GeometryShader.h"
using namespace HBSoft;

GeometryShader::GeometryShader(std::shared_ptr<D3Device> device, const wstringV path,
                               const ShaderType& type)
    : Shader(path, type)
{
    assert(CreateShader(device));
}

void GeometryShader::SetUpToContext(std::shared_ptr<D3Device> device)
{
    device->m_context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
}

bool GeometryShader::CreateShader(std::shared_ptr<D3Device> device)
{
    if (!CreateGeometryShader(device))
        return false;

    if (!CreateConstantBuffer(device))
        return false;

    return true;
}

bool GeometryShader::CreateConstantBuffer(std::shared_ptr<D3Device> device)
{
    HRESULT hr;

    ID3D11ShaderReflection* pReflector = nullptr;

    hr = D3DReflect((void*)m_shaderByteCode->GetBufferPointer(),
                    m_shaderByteCode->GetBufferSize(),
                    IID_ID3D11ShaderReflection,
                    (void**)&pReflector);

    if (FAILED(hr))
        return false;

    // ���̴� ��ũ���� ��������
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

bool GeometryShader::CreateGeometryShader(std::shared_ptr<D3Device> device)
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
                            "gs_5_0",  // dx11 �������̴� �����Ϸ�
                            compileFlags,
                            0,
                            m_shaderByteCode.GetAddressOf(),
                            errorMsg.GetAddressOf());

    if (FAILED(hr))
    {
        MessageBoxA(NULL, (char*)errorMsg->GetBufferPointer(), "PixelShader error", MB_OK);
        return false;
    }

    hr = device->m_d3dDevice->CreateGeometryShader(m_shaderByteCode->GetBufferPointer(),
                                                   m_shaderByteCode->GetBufferSize(),
                                                   nullptr,
                                                   m_geometryShader.GetAddressOf());

    return SUCCEEDED(hr);
}