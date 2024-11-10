/*
author : 변한빛
description : 버텍스 쉐이더를 정의하기 위한 소스 파일

version: 1.0.3
date: 2024-11-09
*/

#include "pch.h"
#include "VertexShader.h"
using namespace HBSoft;

VertexShader::VertexShader(std::shared_ptr<D3Device>& device, const wstringV path,
                           const ShaderType& type)
    : Shader(path, type)
{
    assert(CreateShader(device));
}

bool VertexShader::CreateVertexShader(std::shared_ptr<D3Device>& device)
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
                            "vs_5_0",  // dx11 정점쉐이더 컴파일러
                            compileFlags,
                            0,
                            m_shaderByteCode.GetAddressOf(),
                            errorMsg.GetAddressOf());

    if (FAILED(hr))
    {
        MessageBoxA(NULL, (char*)errorMsg->GetBufferPointer(), "VertexShader error", MB_OK);
        return false;
    }

    hr = device->m_d3dDevice->CreateVertexShader(m_shaderByteCode->GetBufferPointer(),
                                                 m_shaderByteCode->GetBufferSize(),
                                                 nullptr,
                                                 m_vertexShader.GetAddressOf());

    return SUCCEEDED(hr);
}

bool VertexShader::CreateIALayout(std::shared_ptr<D3Device>& device)
{
    HRESULT hr;

    ID3D11ShaderReflection* pReflector = nullptr;

    hr = D3DReflect((void*)m_shaderByteCode->GetBufferPointer(),
                    m_shaderByteCode->GetBufferSize(),
                    IID_ID3D11ShaderReflection,
                    (void**)&pReflector);

    // 셰이더 디스크립션 가져오기
    D3D11_SHADER_DESC ShaderType;
    pReflector->GetDesc(&ShaderType);

    // Input Layout을 구성하기 위한 요소 정의
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;

    // 입력 요소 순회
    for (UINT i = 0; i < ShaderType.InputParameters; ++i)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        pReflector->GetInputParameterDesc(i, &paramDesc);

        // 요소 유형 설정 (POSITION, NORMAL 등)
        D3D11_INPUT_ELEMENT_DESC elementDesc = {};
        elementDesc.SemanticName             = paramDesc.SemanticName;
        elementDesc.SemanticIndex            = paramDesc.SemanticIndex;
        elementDesc.InputSlot                = 0;
        elementDesc.AlignedByteOffset        = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass           = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate     = 0;

        // 요소 형식 결정
        if (paramDesc.Mask == 1)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask <= 3)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask <= 7)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask <= 15)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        inputLayoutDesc.push_back(elementDesc);
    }

    ID3D11InputLayout* pInputLayout = nullptr;
    hr                              = device->m_d3dDevice->CreateInputLayout(inputLayoutDesc.data(),
                                                (UINT)inputLayoutDesc.size(),
                                                m_shaderByteCode->GetBufferPointer(),
                                                m_shaderByteCode->GetBufferSize(),
                                                m_vertexLayout.GetAddressOf());

    return SUCCEEDED(hr);
}

bool VertexShader::CreateShader(std::shared_ptr<D3Device>& device)
{
    if (!CreateVertexShader(device))
        return false;

    if (!CreateIALayout(device))
        return false;

    return true;
}

// void VertexShader::SetUpConfiguration() const
//{
//     HDEVICE->m_context->IASetInputLayout(mVertexLayout.Get());
//     HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//     HDEVICE->m_context->VSSetShader(mVertexShader.Get(), nullptr, 0);
// }
