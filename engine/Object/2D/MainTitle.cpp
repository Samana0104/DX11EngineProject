#include "pch.h"
#include "MainTitle.h"
using namespace HBSoft;

MainTitle::MainTitle()
{
    m_titleTexture = HASSET->m_textures[L"title.png"];
    m_boxMesh      = HASSET->m_meshes[L"BOX2D"];
    m_vsShader     = HASSET->m_shaders[L"2DVertex.hlsl"];
    m_psShader     = HASSET->m_shaders[L"PixelShader.hlsl"];
}

void MainTitle::Update(const float deltaTime) {}

void MainTitle::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    UpdateDefaultCB();
    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);

    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_boxMesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);

    // DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼
    HDEVICE->m_context->IASetIndexBuffer(m_boxMesh->m_subMeshes[0]->indexBuffer.Get(),
                                         DXGI_FORMAT_R32_UINT,
                                         0);
    HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    HDEVICE->m_context->PSSetShaderResources(0, 1, m_titleTexture->GetSRV().GetAddressOf());

    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), nullptr);
    HDEVICE->m_context->DrawIndexed((UINT)m_boxMesh->m_subMeshes[0]->indices.size(), 0, 0);
}

void MainTitle::Init() {}

void MainTitle::Release() {}
