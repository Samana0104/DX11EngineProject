/*
author : 변한빛
description : 모든 텍스쳐를 매니징 하기 위해 만든 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

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
