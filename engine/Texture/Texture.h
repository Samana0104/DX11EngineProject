/*
author : 변한빛
description : 텍스쳐 정의를 하기 위해 만든 헤더 파일

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
