/*
author : 변한빛
description : 텍스쳐 정의를 하기 위해 만든 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Texture.h"
using namespace HBSoft;

Texture::Texture(const wstringV _filePath)
    : m_texturePath(_filePath)
{
#ifdef _DEBUG
    _ASSERT(CreateTexture());
#else
    CreateTexture();
#endif
    LoadTextureSize();
}

bool Texture::CreateTexture()
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(m_device.m_d3dDevice.Get(),
                                                   m_texturePath.c_str(),
                                                   m_texture.GetAddressOf(),  //&m_pTexture
                                                   m_srv.GetAddressOf());

    return SUCCEEDED(hr);
}

void Texture::LoadTextureSize()
{
    D3D11_RESOURCE_DIMENSION resourceType;
    m_texture->GetType(&resourceType);

    switch (resourceType)
    {
    case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
        Load1DTextureSize();
        break;

    case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
        Load2DTextureSize();
        break;

    case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
        Load3DTextureSize();
        break;
    }
}

void Texture::Load1DTextureDesc()
{
    static_cast<ID3D11Texture1D*>(m_texture.Get())->GetDesc(&m_textureDesc);
}

void Texture::Load2DTextureDesc()
{
    D3D11_TEXTURE2D_DESC desc;
    static_cast<ID3D11Texture2D*>(m_texture.Get())->GetDesc(&m_textureDesc);
}

void Texture::Load3DTextureSize()
{
    D3D11_TEXTURE3D_DESC desc;
    static_cast<ID3D11Texture3D*>(m_texture.Get())->GetDesc(&m_textureDesc);
}

POINT_F Texture::GetTextureSizeF() const
{
    return {static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)};
}

POINT_U Texture::GetTextureSizeU() const
{
    return {m_textureWidth, m_textureHeight};
}

vec2 Texture::GetTextureSizeVec2() const
{
    return {static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)};
}

void Texture::Render()
{
    m_device.m_context->PSSetShaderResources(0, 1, m_srv.GetAddressOf());
}
