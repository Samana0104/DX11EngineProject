/*
author : ���Ѻ�
description : height �ؽ��ĸ� ����� ���� ��� ����

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
