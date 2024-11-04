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
        ComPtr<ID3D11ShaderResourceView> m_srv;
        ComPtr<ID3D11Resource>           m_texture;
        D3D11_TEXTURE1D_DESC             m_textureDesc;

        std::wstring m_texturePath;

    protected:
        inline static D3Device& m_device = D3Device::GetInstance();

    private:
        bool CreateTexture();
        void LoadTextureSize();
        void Load1DTextureSize();
        void Load2DTextureSize();
        void Load3DTextureSize();

    public:
        Texture(const wstringV _filePath);

        POINT_F GetTextureSizeF() const;
        POINT_U GetTextureSizeU() const;
        vec2    GetTextureSizeVec2() const;

        virtual void Render();
    };
}  // namespace HBSoft
