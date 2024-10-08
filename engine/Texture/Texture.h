#pragma once
#include "CoreAPI.h"

namespace HBSoft
{
    class Texture
    {
    private:
        ComPtr<ID3D11ShaderResourceView> m_srv;
        ComPtr<ID3D11Resource>           m_texture;

        std::wstring m_texturePath;

        UINT m_textureWidth;
        UINT m_textureHeight;

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
