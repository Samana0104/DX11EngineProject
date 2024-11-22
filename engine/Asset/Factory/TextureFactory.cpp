/*
author : 변한빛
description : 텍스쳐를 생성하는 소스파일

version: 1.0.5
date: 2024-11-22
*/

#include "pch.h"
#include "TextureFactory.h"
#include "Texture/GeneralTexture.h"
#include "Texture/HeightTexture.h"
using namespace HBSoft;

std::shared_ptr<Texture> TextureFactory::Create(std::shared_ptr<D3Device>& device, wstringV path)
{
    std::shared_ptr<Texture> texture;

    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);

    if (fileExt.compare(L"hmp") == 0)
        texture = std::make_shared<HeightTexture>(device, path);
    else
        texture = std::make_shared<GeneralTexture>(device, path);

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
    else if (ext.compare(L".hmp") == 0)
        return true;

    return false;
}
