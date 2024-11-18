#pragma once

#include "pch.h"
#include "Texture/Texture.h"

namespace HBSoft
{
    class TextureFactory
    {
    public:
        static std::shared_ptr<Texture> Create(std::shared_ptr<D3Device>& device, wstringV path);

        static bool IsTextureFormat(const wstringV ext);
    };
}  // namespace HBSoft
