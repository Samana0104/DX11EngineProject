/*
author : ���Ѻ�
description : �Ϲ����� png bmp dds jpg���� ���� �ؽ��� ��� ����

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
