/*
author : 변한빛
description : 텍스쳐를 생성하는 소스파일

version: 1.0.0
date: 2024-11-17
*/

#include "pch.h"
#include "TextureFactory.h"
using namespace HBSoft;

std::shared_ptr<Texture> TextureFactory::Create(std::shared_ptr<D3Device>& device, wstringV path)
{
    auto texture = std::make_shared<Texture>(device, path);
    return texture;
}

bool TextureFactory::IsTextureFormat(const wstringV ext)
{
    if (ext.compare(L".png") == 0)
        return true;
    else if (ext.compare(L".jpg") == 0)
        return true;
    else if (ext.compare(L".bmp") == 0)
        return true;
    else if (ext.compare(L".dds") == 0)
        return true;

    return false;
}
