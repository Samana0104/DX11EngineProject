/*
author : 변한빛
description : 일반적인 png bmp dds jpg등을 위한 텍스쳐 헤더 파일

version: 1.0.1
date: 2024-11-22
*/

#pragma once

#include "Texture\Texture.h"

namespace HBSoft
{
    class GeneralTexture : public Texture
    {
    private:
        bool CreateTexture(std::shared_ptr<D3Device>& device);

    public:
        GeneralTexture(std::shared_ptr<D3Device>& device, const wstringV filePath);
    };
}  // namespace HBSoft
