/*
author : ���Ѻ�
description : �ؽ��� ���Ǹ� �ϱ� ���� ���� �ҽ� ����

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Texture.h"
using namespace HBSoft;

Texture::Texture(const wstringV filePath)
    : m_texturePath(filePath)
{}

void Texture::LoadTextureDesc()
{
    D3D11_RESOURCE_DIMENSION resourceType;
    m_texture->GetType(&resourceType);

    switch (resourceType)
    {
    case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
        static_cast<ID3D11Texture2D*>(m_texture.Get())->GetDesc(&m_textureDesc);
        break;
        // 2D �ؽ��� �ƴϸ� desc �� �ҷ���
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
