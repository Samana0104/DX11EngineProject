#pragma once
#include "MgrTemplate.h"
#include "Texture.h"

namespace HBSoft
{
    class TextureHandler : public MgrTemplate<Texture, TEXTURE_KEY>
    {
    public:
        bool CreateTextureResource(const wstringV filePath);
        void CreateTextureAsFolderPath(const wstringV folderPath);
    };
}  // namespace HBSoft
