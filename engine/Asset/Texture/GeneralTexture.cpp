/*
author : ���Ѻ�
description : �Ϲ����� png bmp dds jpg���� ���� �ؽ��� �ҽ� ����

version: 1.0.1
date: 2024-11-22
*/

#include "pch.h"
#include "GeneralTexture.h"
using namespace HBSoft;

GeneralTexture::GeneralTexture(std::shared_ptr<D3Device>& device, const wstringV filePath)
    : Texture(filePath)
{
    assert(CreateTexture(device));
    LoadTextureDesc();
}

bool GeneralTexture::CreateTexture(std::shared_ptr<D3Device>& device)
{
    /*
        �Ϲ� �ؽ���
    */
    HRESULT hr = DirectX::CreateWICTextureFromFile(device->m_d3dDevice.Get(),
                                                   m_texturePath.c_str(),
                                                   m_texture.GetAddressOf(),
                                                   m_srv.GetAddressOf());
    /*
        dds �ؽ���
    */
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
