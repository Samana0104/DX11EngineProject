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
    m_mapTexture = HASSET->m_textures[L"Map512Color.png"];

    CreateMapDesc(L"Map512.hmp", 0.06f, 0.003f, 0.06f);
    m_mesh = MeshFactory::CreateHeightMap(HDEVICE, m_mapDesc);

    m_vsShader = HASSET->m_shaders[L"VertexShader.hlsl"];
    m_psShader = HASSET->m_shaders[L"PixelShader.hlsl"];

    // m_transform.SetLocation({0.f, -100.f, 0.f});
}

void HeightMapObj::CreateMapDesc(const TEXTURE_KEY heightTexKey, float scaleXPerCell,
                                 float scaleYPerCell, float scaleZPerCell)
{
    D3D11_MAPPED_SUBRESOURCE mapped;
    D3D11_TEXTURE2D_DESC     textureDesc;
    ComPtr<ID3D11Resource>   textureRes;

    std::shared_ptr<Texture> heightTexture = HASSET->m_textures[heightTexKey];

    textureRes  = heightTexture->GetResource();
    textureDesc = heightTexture->GetDesc();

    if (SUCCEEDED(HDEVICE->m_context
                  ->Map(textureRes.Get(), D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &mapped)))
    {
        UINT   rowStart;
        UCHAR* texels = (UCHAR*)mapped.pData;


        m_mapDesc.pixelHeight.resize(textureDesc.Width * textureDesc.Height);

        for (UINT row = 0; row < textureDesc.Height; row++)
        {
            rowStart = row * mapped.RowPitch;
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

        m_mapDesc.numRows       = textureDesc.Width;
        m_mapDesc.numCols       = textureDesc.Height;
        m_mapDesc.scaleXPerCell = scaleXPerCell;
        m_mapDesc.scaleYPerCell = scaleYPerCell;
        m_mapDesc.scaleZPerCell = scaleZPerCell;
        m_mapDesc.numFaces      = textureDesc.Width * textureDesc.Height * 2;
    }
}

void HeightMapObj::Init() {}

void HeightMapObj::Release() {}

void HeightMapObj::Update(const float deltaTime)
{
    UpdateDefaultCB();
}

void HeightMapObj::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);

    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);

    // DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼
    HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[0]->indexBuffer.Get(),
                                         DXGI_FORMAT_R32_UINT,
                                         0);
    HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    HDEVICE->m_context->PSSetShaderResources(0, 1, m_mapTexture->GetSRV().GetAddressOf());

    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());
    HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[0]->indices.size(), 0, 0);
}
