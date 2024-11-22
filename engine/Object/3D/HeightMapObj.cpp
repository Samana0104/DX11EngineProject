/*
author : 변한빛
description : 높이 맵의 오브젝트 소스 파일

version: 1.0.7
date: 2024-11-22
*/

#include "pch.h"
#include "HeightMapObj.h"
using namespace HBSoft;

HeightMapObj::HeightMapObj()
{
    SetTextureKey(L"Map512Color.png");
    LoadMapDesc(L"Map512.hmp");
}

void HeightMapObj::LoadMapDesc(const TEXTURE_KEY texKey)
{
    D3D11_TEXTURE2D_DESC     textureDesc;
    D3D11_MAPPED_SUBRESOURCE mapped;
    ComPtr<ID3D11Resource>   textureRes;

    textureDesc = m_texture->GetDesc();
    textureRes  = m_texture->GetResource();

    m_heightTexture = HASSET->m_textures[texKey];

    if (SUCCEEDED(HDEVICE->m_context
                  ->Map(textureRes.Get(), D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &mapped)))
    {
        UCHAR* texels = (UCHAR*)mapped.pData;
        // RGBA
        for (UINT row = 0; row < textureDesc.Height; row++)
        {
            UINT rowStart = row * mapped.RowPitch;
            for (UINT col = 0; col < textureDesc.Width; col++)
            {
                // rgba이니까 4바이트인데 texel
                UINT colStart = col * 4;
                UINT r        = texels[rowStart + colStart + 0];
                UINT g        = texels[rowStart + colStart + 1];
                UINT b        = texels[rowStart + colStart + 2];
                UINT a        = texels[rowStart + colStart + 3];

                m_mapDesc.pixelHeight[row * textureDesc.Width + col] = (float)r;
            }
        }
        HDEVICE->m_context->Unmap(textureRes.Get(), D3D11CalcSubresource(0, 0, 1));
    }
}
