/*
author : 변한빛
description : 텍스쳐 정의를 하기 위해 만든 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Texture.h"
using namespace HBSoft;

Texture::Texture(std::shared_ptr<D3Device>& device, const wstringV filePath)
    : m_texturePath(filePath)
{
    assert(CreateTexture(device));
    LoadTextureDesc();
}

bool Texture::CreateTexture(std::shared_ptr<D3Device>& device)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(device->m_d3dDevice.Get(),
                                                   m_texturePath.c_str(),
                                                   m_texture.GetAddressOf(),  //&m_pTexture
                                                   m_srv.GetAddressOf());
    if (FAILED(hr))
    {
        hr = DirectX::CreateDDSTextureFromFile(device->m_d3dDevice.Get(),
                                               m_texturePath.c_str(),
                                               m_texture.GetAddressOf(),
                                               m_srv.GetAddressOf(),
                                               0);
    }
    return SUCCEEDED(hr);
}

void Texture::LoadTextureDesc()
{
    D3D11_RESOURCE_DIMENSION resourceType;
    m_texture->GetType(&resourceType);

    switch (resourceType)
    {
    case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
        static_cast<ID3D11Texture2D*>(m_texture.Get())->GetDesc(&m_textureDesc);
        break;
        // 2D 텍스쳐 아니면 desc 못 불러옴
    }
}

HPoint Texture::GetTextureSize() const
{
    return {static_cast<float>(m_textureDesc.Width), static_cast<float>(m_textureDesc.Height)};
}

ComPtr<ID3D11ShaderResourceView>& Texture::GetSRV()
{
    return m_srv;
}

ComPtr<ID3D11Resource>& HBSoft::Texture::GetResource()
{
    return m_texture;
}
