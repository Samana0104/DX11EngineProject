#pragma once
#include "ResourceHandler.h"
#include "Texture.h"

namespace HBSoft
{
    class TextureHandler : public ResourceHandler<Texture, TEXTURE_KEY>
    {
    public:
        bool CreateTextureResource(const wstringV _filePath);
        void CreateTextureAsFolderPath(const wstringV _folderPath);
    };
}  // namespace HBSoft
