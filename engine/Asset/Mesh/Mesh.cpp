/*
author : 변한빛
description : 메쉬의 기본 리소스를 정의하기 위한 소스 파일

version: 1.0.0
date: 2024-11-08
*/

#include "pch.h"
#include "Mesh.h"
using namespace HBSoft;

bool Mesh::CreateMaterialBuffer(std::shared_ptr<D3Device> device)
{
    HRESULT                hr = S_OK;
    D3D11_BUFFER_DESC      bd;
    D3D11_SUBRESOURCE_DATA ms;

    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    ZeroMemory(&ms, sizeof(D3D11_SUBRESOURCE_DATA));
    bd.ByteWidth = sizeof(Material);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;


    for (size_t i = 0; i < m_subMeshes.size(); i++)
    {
        ms.pSysMem = (void*)&m_subMeshes[i]->material;

        if (m_subMeshes[i]->materialBuffer == nullptr)
            hr =
            device->m_d3dDevice->CreateBuffer(&bd, &ms, m_subMeshes[i]->materialBuffer.GetAddressOf());

        if (FAILED(hr))
            return false;
    }


    return true;
}

void Mesh::SetVertices(std::shared_ptr<D3Device> device, const std::vector<Vertex>& vertices)
{
    m_vertices = vertices;
    UpdateVertices(device);
}

void Mesh::SetVertex(std::shared_ptr<D3Device> device, const Vertex& vertex, const UINT idx)
{
    m_vertices[idx] = vertex;
    UpdateVertices(device);
}

void Mesh::UpdateVertices(std::shared_ptr<D3Device> device)
{
    device->m_context->UpdateSubresource(m_vertexBuffer.Get(), 0, NULL, &m_vertices.at(0), 0, 0);
}

void Mesh::UpdateMaterial(std::shared_ptr<D3Device> device, UINT submeshIdx)
{
    HRESULT                  hr;
    D3D11_MAPPED_SUBRESOURCE ms;

    if (m_subMeshes.size() <= submeshIdx)
        return;

    if (m_subMeshes[submeshIdx]->materialBuffer == nullptr)
        return;


    hr = device->m_context->Map(m_subMeshes[submeshIdx]->materialBuffer.Get(),
                                NULL,
                                D3D11_MAP_WRITE_DISCARD,
                                NULL,
                                &ms);
    memcpy(ms.pData, &m_subMeshes[submeshIdx]->material, sizeof(Material));
    device->m_context->Unmap(m_subMeshes[submeshIdx]->materialBuffer.Get(), NULL);
}
