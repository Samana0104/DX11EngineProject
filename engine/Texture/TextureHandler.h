/*
author : ���Ѻ�
description : ��� �ؽ��ĸ� �Ŵ�¡ �ϱ� ���� ���� ��� ����

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
