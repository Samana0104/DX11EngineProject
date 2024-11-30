/*
author : 변한빛
description : height 텍스쳐를 만들기 위한 소스 파일

version: 1.0.1
date: 2024-11-22
*/
#include "pch.h"
#include "HeightTexture.h"
using namespace HBSoft;

HeightTexture::HeightTexture(std::shared_ptr<D3Device> device, const wstringV filePath)
    : Texture(filePath)
{
    assert(CreateTexture(device));
    LoadTextureDesc();
}

bool HeightTexture::CreateTexture(std::shared_ptr<D3Device> device)
{
    HRESULT hr = DirectX::CreateWICTextureFromFileEx(device->m_d3dDevice.Get(),
                                                     m_texturePath.c_str(),
                                                     0,
                                                     D3D11_USAGE_STAGING,
                                                     0,
                                                     D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ,
                                                     0,
                                                     DirectX::WIC_LOADER_DEFAULT,
                                                     m_texture.GetAddressOf(),
                                                     nullptr);
    return SUCCEEDED(hr);
}
