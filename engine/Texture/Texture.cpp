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
    LoadTextureDesc();
}

bool Texture::CreateTexture()
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(m_device.m_d3dDevice.Get(),
                                                   m_texturePath.c_str(),
                                                   m_texture.GetAddressOf(),  //&m_pTexture
                                                   m_srv.GetAddressOf());

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
        // 2D 텍스쳐 아니면 다 컷
    }
}

HPoint Texture::GetTextureSize() const
{
    return {static_cast<float>(m_textureDesc.Width), static_cast<float>(m_textureDesc.Height)};
}

void Texture::Render()
{
    m_device.m_context->PSSetShaderResources(0, 1, m_srv.GetAddressOf());
}
