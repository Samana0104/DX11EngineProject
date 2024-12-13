/*
author : ���Ѻ�
description : ���� ���� ������Ʈ �ҽ� ����

version: 1.0.8
date: 2024-12-12
*/

#include "pch.h"
#include "HeightMapObj.h"
using namespace HBSoft;

HeightMapObj::HeightMapObj()
{
    m_mapTexture = HASSET->m_textures[L"Map512Color.png"];

    CreateMapDesc(L"Map512.hmp", 2.f, 0.2f, 2.f);
    m_mesh = MeshFactory::CreateHeightMap(HDEVICE, m_mapDesc);

    m_vsShader = HASSET->m_shaders[L"VertexShader.hlsl"];
    m_psShader = HASSET->m_shaders[L"PixelShader.hlsl"];
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
                // rgba�̴ϱ� 4����Ʈ�ε� texel
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

float HeightMapObj::GetHeight(vec3 pos)
{
    float cellX = (float)(m_mapDesc.numCols - 1) * 0.5f + pos.x / m_mapDesc.scaleXPerCell;
    float cellZ = (float)(m_mapDesc.numRows - 1) * 0.5f - pos.z / m_mapDesc.scaleZPerCell;

    float floorCellX = glm::floor(cellX);
    float floorCellZ = glm::floor(cellZ);
    float height     = 0.f;
    float colHeight  = 0.f;
    float rowHeight  = 0.f;

    if (floorCellX < 0.f)
        floorCellX = 0.f;
    if (floorCellZ < 0.f)
        floorCellZ = 0.f;

    if (floorCellX > (float)m_mapDesc.numCols - 1.f)
        floorCellX = (float)m_mapDesc.numCols - 1.f;
    if (floorCellZ > (float)m_mapDesc.numRows - 1.f)
        floorCellZ = (float)m_mapDesc.numRows - 1.f;

    // ���� ���� �÷��� �����ϴ� 4�� ������ ���̰��� ã�´�.
    //  A   B      A   B
    //  *---*      *---*
    //  | \ | =>   | / | �̷��� ����ص� ���������?
    //  *---*      *---*
    //  C   D      C   D
    float A = m_mesh->m_vertices[(int)floorCellZ * m_mapDesc.numCols + (int)floorCellX].p.y;
    float B = m_mesh->m_vertices[(int)floorCellZ * m_mapDesc.numCols + (int)floorCellX + 1].p.y;
    float C = m_mesh->m_vertices[((int)floorCellZ + 1) * m_mapDesc.numCols + (int)floorCellX].p.y;
    float D = m_mesh->m_vertices[((int)floorCellZ + 1) * m_mapDesc.numCols + ((int)floorCellX + 1)].p.y;

    float dtCol = cellX - floorCellX;
    float dtRow = cellZ - floorCellZ;

    if (dtCol + dtRow < 1.f)
    {
        colHeight = B - A;
        rowHeight = C - A;

        height = A + glm::lerp(0.f, colHeight, dtCol) + glm::lerp(0.f, rowHeight, dtRow);
    }
    else
    {
        colHeight = C - D;
        rowHeight = B - D;

        height = D + glm::lerp(0.f, colHeight, 1.f - dtCol) + glm::lerp(0.f, rowHeight, 1.f - dtRow);
    }

    return height;
}

void HeightMapObj::Init() {}

void HeightMapObj::Release() {}

void HeightMapObj::Update(const float deltaTime)
{
    UpdateDefaultCB();
}

void HeightMapObj::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1���� ���� ũ��
    UINT pOffsets = 0;               // ���ۿ� ���� �ε���

    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);

    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);

    // DXGI_FORMAT_R32_UINT�� �ε��� ������ Ÿ���� UINT�� �׷�
    HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[0]->indexBuffer.Get(),
                                         DXGI_FORMAT_R32_UINT,
                                         0);
    HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    HDEVICE->m_context->PSSetShaderResources(0, 1, m_mapTexture->GetSRV().GetAddressOf());

    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());
    HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[0]->indices.size(), 0, 0);
}