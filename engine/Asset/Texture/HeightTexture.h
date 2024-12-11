/*
author : 변한빛
description : height 텍스쳐를 만들기 위한 헤더 파일

version: 1.0.1
date: 2024-11-22
*/
#pragma once

#include "Texture/Texture.h"

namespace HBSoft
{
    class HeightTexture : public Texture
    {
    private:
        bool CreateTexture(std::shared_ptr<D3Device> device);

    public:
        HeightTexture(std::shared_ptr<D3Device> device, const wstringV filePath);
    };
}  // namespace HBSoft
