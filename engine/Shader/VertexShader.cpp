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

    hr = D3DCompileFromFile(mShaderDesc.mShaderPath.c_str(),
                            nullptr,
                            nullptr,
                            mShaderDesc.mShaderEntry.c_str(),
                            "vs_5_0",  // dx11 �������̴� �����Ϸ�
                            0,
                            0,
                            mShaderByteCode.GetAddressOf(),
                            errorMsg.GetAddressOf());

    if (FAILED(hr))
    {
        MessageBoxA(NULL, (char*)errorMsg->GetBufferPointer(), "VertexShader error", MB_OK);
        return false;
    }

    hr = mDevice.mD3dDevice->CreateVertexShader(mShaderByteCode->GetBufferPointer(),
                                                mShaderByteCode->GetBufferSize(),
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
    HRESULT hr          = mDevice.mD3dDevice->CreateInputLayout(layout,
                                                       NumElements,
                                                       mShaderByteCode->GetBufferPointer(),
                                                       mShaderByteCode->GetBufferSize(),
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
    mDevice.mContext->IASetInputLayout(mVertexLayout.Get());
    mDevice.mContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    mDevice.mContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
}
