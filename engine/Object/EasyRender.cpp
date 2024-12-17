/*
author : 변한빛
description : 렌더링 추상화를 위한 소스 파일

version: 1.0.0
date: 2024-12-16
*/

#include "pch.h"
#include "EasyRender.h"
using namespace HBSoft;

EasyRender::EasyRender()
{
    m_rrs      = ERRasterRizerState::SOLID_BACK_CULL;
    m_dss      = ERDepthStencilState::LESS;
    m_bs       = ERBlendingState::Alpha;
    m_ss       = ERSamplerState::POINT;
    m_topology = ERTopology::TRIANGLE_LIST;
}

void EasyRender::InitShaderState()
{
    std::vector<ID3D11Buffer*> buffer;

    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);
    HDEVICE->m_context->HSSetShader(NULL, NULL, 0);
    HDEVICE->m_context->DSSetShader(NULL, NULL, 0);
    HDEVICE->m_context->GSSetShader(NULL, NULL, 0);

    for (UINT i = 0; i < m_vsCB.size(); i++)
        buffer.push_back(m_vsCB[i].Get());

    if (buffer.size() > 0)
        HDEVICE->m_context->VSSetConstantBuffers(0, (UINT)buffer.size(), &buffer.at(0));

    buffer.clear();

    for (UINT i = 0; i < m_psCB.size(); i++)
        buffer.push_back(m_psCB[i].Get());

    if (buffer.size() > 0)
        HDEVICE->m_context->PSSetConstantBuffers(0, (UINT)buffer.size(), &buffer.at(0));
}

void EasyRender::Begin(MultiRT renderTarget)
{
    float clearColor[] = {0.f, 0.f, 0.f, 0.0f};
    HDEVICE->m_context->ClearRenderTargetView(HDEVICE->m_multiRT[renderTarget].rtv.Get(), clearColor);
    HDEVICE->m_context->ClearDepthStencilView(HDEVICE->m_multiRT[renderTarget].dsv.Get(),
                                              D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
                                              1.0f,
                                              0);

    HDEVICE->m_context->RSSetViewports(1, &HDEVICE->m_multiRT[renderTarget].viewPort);
    HDEVICE->m_context->OMSetRenderTargets(1,
                                           HDEVICE->m_multiRT[renderTarget].rtv.GetAddressOf(),
                                           HDEVICE->m_multiRT[renderTarget].dsv.Get());
}

void EasyRender::End()
{
    HDEVICE->m_context->RSSetViewports(1, &HDEVICE->m_multiRT[MultiRT::MAIN].viewPort);
    HDEVICE->m_context->OMSetRenderTargets(1,
                                           HDEVICE->m_multiRT[MultiRT::MAIN].rtv.GetAddressOf(),
                                           HDEVICE->m_multiRT[MultiRT::MAIN].dsv.Get());
}

void EasyRender::SetEntireState()
{
    InitShaderState();
    SetRRSFromDevice();
    SetDSSFromDevice();
    SetBSFromDevice();
    SetSSFromDevice();
    SetTopologyFromDevice();

    if (m_isWireFrame)
        HDEVICE->m_context->RSSetState(HDEVICE->m_renderState.wireNoCullRS.Get());
}

void EasyRender::SetVSShader(const SHADER_KEY shaderKey)
{
    m_vsShader              = HASSET->m_shaders[shaderKey];
    auto&   constantBuffers = m_vsShader->GetConstantBuffers();
    HRESULT hr;

    D3D11_BUFFER_DESC bufferDesc;

    m_vsCB.clear();

    for (size_t i = 0; i < constantBuffers.size(); i++)
    {
        ComPtr<ID3D11Buffer> constantBuffer = nullptr;
        constantBuffers[i]->GetDesc(&bufferDesc);
        hr = HDEVICE->m_d3dDevice->CreateBuffer(&bufferDesc, nullptr, constantBuffer.GetAddressOf());

        if (FAILED(hr))
            assert(false);

        m_vsCB.push_back(constantBuffer);
    }
}

void EasyRender::SetPSShader(const SHADER_KEY shaderKey)
{
    m_psShader              = HASSET->m_shaders[shaderKey];
    auto&   constantBuffers = m_psShader->GetConstantBuffers();
    HRESULT hr;

    D3D11_BUFFER_DESC bufferDesc;

    m_psCB.clear();

    for (int i = 0; i < constantBuffers.size(); i++)
    {
        ComPtr<ID3D11Buffer> constantBuffer = nullptr;
        constantBuffers[i]->GetDesc(&bufferDesc);
        hr = HDEVICE->m_d3dDevice->CreateBuffer(&bufferDesc, nullptr, constantBuffer.GetAddressOf());

        if (FAILED(hr))
            assert(false);

        m_psCB.push_back(constantBuffer);
    }
}

void EasyRender::SetRRS(ERRasterRizerState rrs)
{
    m_rrs = rrs;
}

void EasyRender::SetDSS(ERDepthStencilState dss)
{
    m_dss = dss;
}

void EasyRender::SetBS(ERBlendingState bs)
{
    m_bs = bs;
}

void EasyRender::SetSS(ERSamplerState ss)
{
    m_ss = ss;
}

void EasyRender::SetTopology(ERTopology topology)
{
    m_topology = topology;
}

void EasyRender::SetMesh(std::shared_ptr<Mesh> mesh)
{
    m_mesh = mesh;
}

void EasyRender::SetTexture(std::shared_ptr<Texture> texture)
{
    m_texture = texture;
}

void EasyRender::Draw()
{
    SetEntireState();

    if (m_texture != nullptr)
        HDEVICE->m_context->PSSetShaderResources(0, 1, m_texture->GetSRV().GetAddressOf());

    if (m_mesh != nullptr)
    {
        UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
        UINT pOffsets = 0;               // 버퍼에 시작 인덱스

        HDEVICE->m_context->IASetVertexBuffers(0,
                                               1,
                                               m_mesh->m_vertexBuffer.GetAddressOf(),
                                               &pStrides,
                                               &pOffsets);

        for (size_t i = 0; i < m_mesh->m_subMeshes.size(); i++)
        {
            if (m_mesh->m_subMeshes[i]->hasTexture)
            {
                HDEVICE->m_context->PSSetShaderResources(
                0,
                1,
                HASSET->m_textures[m_mesh->m_subMeshes[i]->textureName]->GetSRV().GetAddressOf());
            }
            HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[i]->indexBuffer.Get(),
                                                 DXGI_FORMAT_R32_UINT,
                                                 0);
            HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[i]->indices.size(), 0, 0);
        }
    }
}

void EasyRender::SetRRSFromDevice()
{
    switch (m_rrs)
    {
    case ERRasterRizerState::SOLID_BACK_CULL:
        HDEVICE->m_context->RSSetState(HDEVICE->m_renderState.solidBackCullRS.Get());
        break;
    case ERRasterRizerState::SOLID_FRONT_CULL:
        HDEVICE->m_context->RSSetState(HDEVICE->m_renderState.solidFrontCullRS.Get());
        break;
    case ERRasterRizerState::SOLID_NO_CULL:
        HDEVICE->m_context->RSSetState(HDEVICE->m_renderState.solidNoCullRS.Get());
        break;
    case ERRasterRizerState::WIRE_BACK_CULL:
        HDEVICE->m_context->RSSetState(HDEVICE->m_renderState.wireBackCullRS.Get());
        break;
    case ERRasterRizerState::WIRE_FRONT_CULL:
        HDEVICE->m_context->RSSetState(HDEVICE->m_renderState.wireFrontCullRS.Get());
        break;
    case ERRasterRizerState::WIRE_NO_CULL:
        HDEVICE->m_context->RSSetState(HDEVICE->m_renderState.wireNoCullRS.Get());
        break;
    }
}

void EasyRender::SetDSSFromDevice()
{
    switch (m_dss)
    {
    case ERDepthStencilState::LESS:
        HDEVICE->m_context->OMSetDepthStencilState(HDEVICE->m_renderState.lessDSS.Get(), 0);
        break;

    case ERDepthStencilState::GREATER:
        HDEVICE->m_context->OMSetDepthStencilState(HDEVICE->m_renderState.greaterDSS.Get(), 0);
        break;

    case ERDepthStencilState::NO_WRITE:
        HDEVICE->m_context->OMSetDepthStencilState(HDEVICE->m_renderState.noWriteDSS.Get(), 0);
        break;

    case ERDepthStencilState::DISABLE:
        HDEVICE->m_context->OMSetDepthStencilState(HDEVICE->m_renderState.disableDSS.Get(), 0);
        break;
    }
}

void EasyRender::SetBSFromDevice()
{
    switch (m_bs)
    {
    case ERBlendingState::Alpha:
        HDEVICE->m_context->OMSetBlendState(HDEVICE->m_renderState.alphaBS.Get(), 0, -1);

    case ERBlendingState::Merge:
        HDEVICE->m_context->OMSetBlendState(HDEVICE->m_renderState.mergeBS.Get(), 0, -1);
        break;
    }
}

void EasyRender::SetSSFromDevice()
{
    switch (m_ss)
    {
    case ERSamplerState::POINT:
        HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_renderState.pointSampler.GetAddressOf());
        break;

    case ERSamplerState::LINEAR:
        HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_renderState.linearSampler.GetAddressOf());
        break;

    case ERSamplerState::ANISOTROPIC:
        HDEVICE->m_context->PSSetSamplers(0,
                                          1,
                                          HDEVICE->m_renderState.anisotropicSampler.GetAddressOf());
        break;
    }
}

void EasyRender::SetTopologyFromDevice()
{
    switch (m_topology)
    {
    case ERTopology::POINT_LIST:
        HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
        break;

    case ERTopology::LINE_LIST:
        HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
        break;

    case ERTopology::LINE_STRIP:
        HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
        break;

    case ERTopology::TRIANGLE_LIST:
        HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        break;

    case ERTopology::TRIANGLE_STRIP:
        HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        break;
    }
}

void EasyRender::UpdateVSCB(const void* data, const size_t dataSize, const UINT constantIdx)
{
    if (m_vsShader == nullptr)
        return;

    if (m_vsCB.size() <= 0)
        return;

    D3D11_MAPPED_SUBRESOURCE ms;
    HRESULT                  hr;

    hr = HDEVICE->m_context->Map(m_vsCB[constantIdx].Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
    memcpy(ms.pData, data, dataSize);
    HDEVICE->m_context->Unmap(m_vsCB[constantIdx].Get(), NULL);
}

void EasyRender::UpdatePSCB(const void* data, const size_t dataSize, const UINT constantIdx)
{
    if (m_vsShader == nullptr)
        return;

    if (m_psCB.size() <= 0)
        return;

    D3D11_MAPPED_SUBRESOURCE ms;
    HRESULT                  hr;

    hr = HDEVICE->m_context->Map(m_psCB[constantIdx].Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
    memcpy(ms.pData, data, dataSize);
    HDEVICE->m_context->Unmap(m_psCB[constantIdx].Get(), NULL);
}

void EasyRender::MergeRenderTarget(MultiRT dst, MultiRT src)
{
    // 메인은 srv가 없어요~
    if (src == MultiRT::MAIN)
        return;

    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    HASSET->m_shaders[L"MergeVertex.hlsl"]->SetUpToContext(HDEVICE);
    HASSET->m_shaders[L"MergePixel.hlsl"]->SetUpToContext(HDEVICE);
    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           HASSET->m_meshes[L"BOX2D"]->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);
    HDEVICE->m_context->IASetIndexBuffer(HASSET->m_meshes[L"BOX2D"]->m_subMeshes[0]->indexBuffer.Get(),
                                         DXGI_FORMAT_R32_UINT,
                                         0);
    HDEVICE->m_context->PSSetShaderResources(0, 1, HDEVICE->m_multiRT[src].rtSrv.GetAddressOf());
    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_renderState.pointSampler.GetAddressOf());

    HDEVICE->m_context->RSSetViewports(1, &HDEVICE->m_multiRT[dst].viewPort);
    HDEVICE->m_context->RSSetState(HDEVICE->m_renderState.solidBackCullRS.Get());

    HDEVICE->m_context->OMSetBlendState(HDEVICE->m_renderState.mergeBS.Get(), 0, -1);
    HDEVICE->m_context->OMSetRenderTargets(1,
                                           HDEVICE->m_multiRT[dst].rtv.GetAddressOf(),
                                           HDEVICE->m_multiRT[dst].dsv.Get());
    HDEVICE->m_context->OMSetDepthStencilState(HDEVICE->m_renderState.disableDSS.Get(), 0);
    HDEVICE->m_context->DrawIndexed((UINT)HASSET->m_meshes[L"BOX2D"]->m_subMeshes[0]->indices.size(),
                                    0,
                                    0);
}

void EasyRender::SaveScreenShot(MultiRT renderTarget, std::wstring fileName)
{
    DirectX::SaveWICTextureToFile(HDEVICE->m_context.Get(),
                                  HDEVICE->m_multiRT[renderTarget].texRt.Get(),
                                  GUID_ContainerFormatPng,
                                  (fileName + L".png").c_str());
}

void EasyRender::SetWireFrame(bool isWire)
{
    m_isWireFrame = isWire;
}
