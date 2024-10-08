#pragma once
#include "ResourceHandler.h"
#include "Texture.h"

namespace HBSoft
{
    class TextureHandler : public ResourceHandler<Texture, TEXTURE_KEY>
    {
    public:
        bool CreateTextureResource(const wstringV filePath);
        void CreateTextureAsFolderPath(const wstringV folderPath);
    };
}  // namespace HBSoft
