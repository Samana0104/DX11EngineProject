/*
author : 변한빛
description : 높이 맵의 오브젝트 소스 파일

version: 1.0.8
date: 2024-12-12
*/

#include "pch.h"
#include "HeightMapObj.h"
using namespace HBSoft;

HeightMapObj::HeightMapObj()
{
    // m_x     = -3.0f;
    // m_y     = -0.93f;
    // m_z     = 2.7f;
    // m_scale = 3.0f;

    m_mapTexture = HASSET->m_textures[L"Map512Color.png"];
    m_cubeTex    = HASSET->m_textures[L"cubeTest.dds"];

    CreateMapDesc(L"Map512.hmp", 0.18f, 0.009f, 0.18f);
    m_mesh = MeshFactory::CreateHeightMap(HDEVICE, m_mapDesc);
    GenerateVertexNormal();

    m_easyRender.SetVSShader(L"BasicVS.hlsl");
    m_easyRender.SetPSShader(L"BasicEnvPS.hlsl");
    m_easyRender.SetSS(ERSamplerState::LINEAR);
    m_easyRender.SetTexture(m_mapTexture);

    m_transform.SetLocation({-3.f, -0.93f, 2.7f});
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

    // 높이맵은 항상 홀수로 만드시오
    assert(textureDesc.Width % 2 != 0 || textureDesc.Height % 2 != 0);

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

    // 계산된 셀의 플랜을 구성하는 4개 정점의 높이값을 찾는다.
    //  A   B      A   B
    //  *---*      *---*
    //  | \ | =>   | / | 이렇게 계산해도 상관없을듯?
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

    return height * m_transform.m_scale.y + m_transform.m_pos.y;
}

void HeightMapObj::GenerateVertexNormal()
{
    UINT faces = (UINT)m_mesh->m_subMeshes[0]->indices.size() / 3;
    m_vertexInfo.resize(m_mesh->m_vertices.size());

    for (UINT i = 0; i < faces; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            UINT idxInFace = m_mesh->m_subMeshes[0]->indices[i * 3 + j];
            m_vertexInfo[idxInFace].faceIndices.push_back(i);
        }
    }

    for (UINT i = 0; i < m_vertexInfo.size(); i++)
        ComputeVertexNormal(i);

    m_mesh->UpdateVertices(HDEVICE);
}

void HeightMapObj::ComputeVertexNormal(UINT vertex)
{
    for (UINT i = 0; i < m_vertexInfo[vertex].faceIndices.size(); i++)
    {
        UINT faceindex  = m_vertexInfo[vertex].faceIndices[i];
        UINT idxInFace1 = m_mesh->m_subMeshes[0]->indices[faceindex * 3];
        UINT idxInFace2 = m_mesh->m_subMeshes[0]->indices[faceindex * 3 + 1];
        UINT idxInFace3 = m_mesh->m_subMeshes[0]->indices[faceindex * 3 + 2];
        vec3 edge0      = m_mesh->m_vertices[idxInFace2].p - m_mesh->m_vertices[idxInFace1].p;
        vec3 edge1      = m_mesh->m_vertices[idxInFace3].p - m_mesh->m_vertices[idxInFace1].p;
        vec3 normal     = glm::normalize(glm::cross(edge0, edge1));

        m_vertexInfo[vertex].normal += normal;
    }

    m_mesh->m_vertices[vertex].n = glm::normalize(m_vertexInfo[vertex].normal);
}

void HeightMapObj::Init() {}

void HeightMapObj::Release() {}

void HeightMapObj::Update(const float deltaTime)
{
    /*ImGui::DragFloat("TerrainScale", &m_scale, 0.01f, 0.0f, 900.f);
    ImGui::DragFloat("TerrainX", &m_x, 0.01f, -100.0f, 100.f);
    ImGui::DragFloat("TerrainY", &m_y, 0.01f, -100.0f, 100.f);
    ImGui::DragFloat("TerrainZ", &m_z, 0.01f, -100.0f, 100.f);*/

    UpdateDefaultCB();
}

void HeightMapObj::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    m_easyRender.SetEntireState();
    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);

    // DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼
    HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[0]->indexBuffer.Get(),
                                         DXGI_FORMAT_R32_UINT,
                                         0);
    HDEVICE->m_context->PSSetShaderResources(0, 1, m_mapTexture->GetSRV().GetAddressOf());
    HDEVICE->m_context->PSSetShaderResources(1, 1, m_cubeTex->GetSRV().GetAddressOf());
    HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[0]->indices.size(), 0, 0);
}
