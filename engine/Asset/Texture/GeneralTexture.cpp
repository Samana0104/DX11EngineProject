/*
author : 변한빛
description : 일반적인 png bmp dds jpg등을 위한 텍스쳐 소스 파일

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
        일반 텍스쳐
    */
    HRESULT hr = DirectX::CreateWICTextureFromFile(device->m_d3dDevice.Get(),
                                                   m_texturePath.c_str(),
                                                   m_texture.GetAddressOf(),
                                                   m_srv.GetAddressOf());
    /*
        dds 텍스쳐
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
