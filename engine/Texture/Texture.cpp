/*
author : ���Ѻ�
description : �ؽ��� ���Ǹ� �ϱ� ���� ���� �ҽ� ����

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Texture.h"
using namespace HBSoft;

Texture::Texture(std::shared_ptr<D3Device> device, const wstringV filePath)
    : m_texturePath(filePath)
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
    HRESULT hr = DirectX::CreateWICTextureFromFile(HDEVICE->m_d3dDevice.Get(),
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
        // 2D �ؽ��� �ƴϸ� �� ��
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
