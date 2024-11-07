/*
author : ���Ѻ�
description : �ؽ��� ���Ǹ� �ϱ� ���� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    class Texture
    {
    private:
        std::shared_ptr<D3Device>        m_device;
        ComPtr<ID3D11ShaderResourceView> m_srv;
        ComPtr<ID3D11Resource>           m_texture;
        D3D11_TEXTURE2D_DESC             m_textureDesc;

        std::wstring m_texturePath;

    private:
        bool CreateTexture();
        void LoadTextureDesc();

    public:
        Texture(std::shared_ptr<D3Device> device, const wstringV filePath);

        HPoint GetTextureSize() const;

        ComPtr<ID3D11ShaderResourceView>& GetSRV();
        ComPtr<ID3D11Resource>&           GetResource();
    };
}  // namespace HBSoft
